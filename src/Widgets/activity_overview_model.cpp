#include "ActivityOverviewModel.h"
#include "ActivityOverviewModel.h"


#include <ActivityType.h>

#include <QElapsedTimer>

/* This will pront detailed logs about ActivityOverviewModel::recalculate()
* That function can get complicated
*/
static bool DEBUG_RECALCULATE = false;

namespace Widgets
{

namespace
{
void optionalRecalcLog(const QString& message)
{
	if (DEBUG_RECALCULATE)
		qDebug() << message;
}
}

ActivityCategory::ActivityCategory(const QDate& from_date_, const QDate& to_date_, EActivityGroupedBy grouped_by) :
	from_date(from_date_), to_date(to_date_), _grouped_by(grouped_by)
{
}

QString ActivityCategory::toString(ECategoryStringFormat format) const
{
	QString full_date_format = "yyyy-MM-dd";

	switch (format)
	{
	case ECategoryStringFormat::Full:
		return QString("%1 - %2").arg(from_date.toString(full_date_format), to_date.toString(full_date_format));
	case ECategoryStringFormat::WithAddition:
	{
		switch (_grouped_by)
		{
		case EActivityGroupedBy::Day:
			return from_date.toString("MM-dd");
		case EActivityGroupedBy::Month:
			return from_date.toString("yyyy-MM");
		case EActivityGroupedBy::Year:
			return from_date.toString("yyyy");
		default:
			return {};
		}
	}
	case ECategoryStringFormat::Simple:
	{
		switch (_grouped_by)
		{
		case EActivityGroupedBy::Day:
			return from_date.toString("dd");
		case EActivityGroupedBy::Month:
			return from_date.toString("MM");
		case EActivityGroupedBy::Year:
			return from_date.toString("yyyy");
		default:
			return {};
		}
	}
	default:
		return {};
	}


}

bool ActivityCategory::operator<(const ActivityCategory& other) const
{
	return from_date < other.from_date;
}

bool ActivityCategory::operator==(const ActivityCategory& other) const
{
	return from_date == other.from_date && to_date == other.to_date;
}

bool ActivityCategory::operator!=(const ActivityCategory& other) const
{
	return !(*this == other);
}

ActivityOverviewModel::ActivityOverviewModel(const std::vector<Providers::ActivitySummary>& acts, QObject* parent) :
	QObject(parent), _acts(acts)
{
	if (_acts.empty())
	{
		qWarning() << "(ActivityOverviewModel) Activities list is empty";
		return;
	}

	recalculate();
}

ActivityOverviewModel::~ActivityOverviewModel()
{
}

void ActivityOverviewModel::setStacked(bool stacked)
{
	_is_stacked = stacked;
	recalculate();
}

void ActivityOverviewModel::setGroupedBy(EActivityGroupedBy grouping)
{
	_grouped_by = grouping;
	recalculate();
}

void ActivityOverviewModel::setDateRange(const QDate& from, const QDate& to)
{
	_from_date = from;
	_to_date = to;
	recalculate();
}

void ActivityOverviewModel::setActivityTypes(const std::vector<Providers::EActivityType>& types)
{
	_types = types;
	recalculate();
}

void ActivityOverviewModel::setAttributes(const std::vector<Providers::ActivitySummary::ESummableAttribute>& attributes)
{
	_attributes = attributes;
	recalculate();
}

std::vector<Providers::ActivitySummary::ESummableAttribute> ActivityOverviewModel::getAttributes() const
{
	return _attributes;
}

bool ActivityOverviewModel::isStacked() const
{
	return _is_stacked;
}

std::vector<Providers::EActivityType> ActivityOverviewModel::getActivityTypes() const
{
	return _types;
}

EActivityGroupedBy ActivityOverviewModel::getGroupedBy() const
{
	if (!isValid())
	{
		qDebug() << "(ActivityOverviewModel): Trying to get grouped_by on invalid model";
		return {};
	}

	return _grouped_by;
}

std::vector<ActivityCategory> ActivityOverviewModel::getCategories() const
{
	if (!isValid())
	{
		qDebug() << "(ActivityOverviewModel): Trying to get categories on invalid model";
		return {};
	}

	return _categories;
}

std::map<ActivityCategory, std::vector<Providers::ActivitySummary>> ActivityOverviewModel::getActivitiesByCategory()
const
{
	if (!isValid())
	{
		qDebug() << "(ActivityOverviewModel): Trying to get activities on invalid model";
		return {};
	}

	return _acts_by_category;
}

/*
* Gets the vector of values for a specific attribute, in the same order as the categories, for an act type
* The values are summed up in each category
*/
std::vector<std::pair<ActivityCategory, float>> ActivityOverviewModel::getValuesForAttributeByCategory(
	Providers::ActivitySummary::ESummableAttribute attribute,
	Providers::EActivityType type) const
{
	if (!isValid())
	{
		qDebug() << "(ActivityOverviewModel): Trying to get activities on invalid model";
		return {};
	}

	std::vector<std::pair<ActivityCategory, float>> result;

	for (const auto& cat : _categories)
	{
		auto acts_in_cat = _acts_by_category.find(cat);
		if (acts_in_cat == _acts_by_category.end())
		{
			qWarning() << "ActivityOverviewModel: did not find category, although it should exist";
			continue;
		}

		float values_sum = 0;
		for (const auto& act : acts_in_cat->second)
		{
			if (act.type == type)
				values_sum += act.getSummableAttribute(attribute);
		}

		result.push_back({ cat, values_sum });
	}

	return result;
}


std::vector<Providers::ActivitySummary> ActivityOverviewModel::getFilteredActivities() const
{
	return _filtered_acts;
}

bool ActivityOverviewModel::isValid() const
{
	return !_acts.empty() &&
		_from_date.isValid() &&
		_to_date.isValid() &&
		_grouped_by != EActivityGroupedBy::Unknown &&
		!_attributes.empty() &&
		!_types.empty();
}

void ActivityOverviewModel::recalculate()
{
	if (!isValid())
		return;

	_filtered_acts.clear();

	// Filter activities by date
	for (const auto& act : _acts)
	{
		if (act.start_date.date() >= _from_date && act.start_date.date() <= _to_date)
			_filtered_acts.push_back(act);
	}

	// Sort activities by date
	auto earlier = [](Providers::ActivitySummary lhs, Providers::ActivitySummary rhs) -> bool
		{
			return lhs.start_date < rhs.start_date;
		};
	std::sort(_filtered_acts.begin(), _filtered_acts.end(), earlier);

	// Save the categories internally
	recalculateCategories();

	// Create map of activities by category
	_acts_by_category.clear();
	std::vector<Providers::ActivitySummary>::iterator first_act_it = _filtered_acts.begin();
	std::vector<Providers::ActivitySummary>::iterator last_act_it = _filtered_acts.begin();
	bool category_empty = true;

	int first_act = 0;
	int last_act = 0;

	optionalRecalcLog("============ Recalculate ============");
	QElapsedTimer timer;
	timer.start();

	for (const auto& category : _categories)
	{
		optionalRecalcLog(QString("Category: %1").arg(category.toString(ECategoryStringFormat::Full)));

		std::vector<Providers::ActivitySummary> category_acts;
		auto cat_indexes = getFirstAndLastActivityIndexOfCategory(first_act, category);
		if (cat_indexes)
		{
			first_act = cat_indexes->first;
			last_act = cat_indexes->second;

			category_acts = std::vector<Providers::ActivitySummary>(
				_filtered_acts.begin() + first_act, _filtered_acts.begin() + last_act + 1);
		}
		else
			optionalRecalcLog("Category was empty");

		_acts_by_category.insert({ category, category_acts });
	}

	auto elapsed_time = timer.elapsed();
	qDebug() << "ActivityOverviewModel recalculate took: " << elapsed_time << " ms";

	Q_EMIT modelChanged();
}

/*
* Saves the recalculated categories internally
*/
void ActivityOverviewModel::recalculateCategories()
{
	if (_filtered_acts.empty())
		return;

	_categories.clear();

	QDate date = _from_date;
	switch (_grouped_by)
	{
	case EActivityGroupedBy::Day:
	{
		// Iterate over days, until the last is reached
		while (date <= _to_date)
		{
			_categories.push_back(ActivityCategory(date, date, _grouped_by));
			date = date.addDays(1);
		}
		return;
	}
	case EActivityGroupedBy::Month:
	{
		// Iterate over months, until the last is reached
		while (date <= _to_date)
		{
			// Create categor with first and last day of the month
			QDate category_begin(date.year(), date.month(), 1);
			QDate category_end(date.year(), date.month(), date.daysInMonth());
			_categories.push_back(ActivityCategory(category_begin, category_end, _grouped_by));
			date = date.addMonths(1);
		}
		return;
	}
	case EActivityGroupedBy::Year:
	{
		// Iterate over years, until the last is reached
		while (date <= _to_date)
		{
			// Create categor with first and last day of the year
			QDate category_begin(date.year(), 1, 1);
			QDate category_end(date.year(), 12, 31);
			_categories.push_back(ActivityCategory(category_begin, category_end, _grouped_by));
			date = date.addYears(1);
		}
		return;
	}
	default:
		qWarning() << "The activity model had invalid grouping";
		return;
	}
}

/*
* Gets the First and last index of the activities (from _filtered_acts) belonging to the category.
* If the category is empty, returns null
*/
std::optional<std::pair<int, int>> ActivityOverviewModel::getFirstAndLastActivityIndexOfCategory(
	int start_at_act, const ActivityCategory& category) const
{
	auto first_act = getFirstActivityIndexOfCategory(start_at_act, category);
	if (!first_act)
		return {};

	if (auto last_act = getLastActivityIndexOfCategory(*first_act, category))
		return std::pair<int, int>(*first_act, *last_act);

	return {};
}

std::optional<int> ActivityOverviewModel::getFirstActivityIndexOfCategory(
	int start_at_act, const ActivityCategory& category) const
{
	optionalRecalcLog(QString(" Looking for first act in %2 - %3").
		arg(category.from_date.toString("yyyy-MM-dd"), category.to_date.toString("yyyy-MM-dd")));

	for (int index = start_at_act; index < _filtered_acts.size(); index++)
	{
		const auto& act_date = _filtered_acts.at(index).start_date.date();

		optionalRecalcLog(QString("  Act date: %1").
			arg(act_date.toString("yyyy-MM-dd")));

		// If the act_date is greater than the category from_date, the category is empty
		if (act_date > category.to_date)
		{
			optionalRecalcLog(QString("   The act date was greater then category end date"));
			return {};
		}

		if (act_date >= category.from_date && act_date <= category.to_date)
		{
			optionalRecalcLog(QString("   Set first act: %1").
				arg(act_date.toString("yyyy-MM-dd")));
			return index;
		}
	}

	optionalRecalcLog(QString("   Found no act for category begin"));
	return {};
}

std::optional<int> ActivityOverviewModel::getLastActivityIndexOfCategory(
	int start_at_act, const ActivityCategory& category) const
{
	optionalRecalcLog(QString(" Looking for last act in %2 - %3").
		arg(category.from_date.toString("yyyy-MM-dd"), category.to_date.toString("yyyy-MM-dd")));

	for (int index = start_at_act; index < _filtered_acts.size(); index++)
	{
		const auto& act_date = _filtered_acts.at(index).start_date.date();

		optionalRecalcLog(QString("  Act date: %1").
			arg(act_date.toString("yyyy-MM-dd")));

		// If the act is outside the category range, than the previus is the last act of the category
		if (act_date > category.to_date)
		{
			optionalRecalcLog(QString("   Set last act (based on previous): %1").
				arg(_filtered_acts.at(index - 1).start_date.date().toString("yyyy-MM-dd")));
			return index - 1;
		}

		// If act is the last, than it is the last in the category
		if (index == _filtered_acts.size() - 1)
		{
			optionalRecalcLog(QString("   Set last act (based on it was last in the list): %1").
				arg(act_date.toString()));
			return index;
		}
	}

	optionalRecalcLog(QString("   Found no act for category end"));
	return {};
}

}
