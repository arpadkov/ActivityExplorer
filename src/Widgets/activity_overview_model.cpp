#include "ActivityOverviewModel.h"
#include "ActivityOverviewModel.h"
#include "ActivityOverviewModel.h"
#include "ActivityOverviewModel.h"
#include "ActivityOverviewModel.h"
#include "ActivityOverviewModel.h"

#include <ActivityType.h>

namespace Widgets
{

ActivityOverviewModel::ActivityOverviewModel(const std::vector<Providers::ActivitySummary>& acts, QObject* parent) :
	QObject(parent), _acts(acts)
{
	if (_acts.empty())
	{
		qWarning() << "(ActivityOverviewModel) Activities list is empty";
		return;
	}

	_from_date = acts.front().start_date.date();
	_to_date = QDate::currentDate();

	recalculate();
}

ActivityOverviewModel::~ActivityOverviewModel()
{
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

std::vector<Providers::ActivitySummary::ESummableAttribute> ActivityOverviewModel::getAttributes() const
{
	return _attributes;
}

bool ActivityOverviewModel::getStacked() const
{
	return _stacked;
}

EActivityGroupedBy ActivityOverviewModel::getGroupedBy() const
{
	return _grouped_by;
}

QStringList ActivityOverviewModel::getCategories() const
{
	QStringList result;

	if (_filtered_acts.empty())
		return {};


	QDate date = _from_date;
	switch (_grouped_by)
	{
	case EActivityGroupedBy::Day:
	{
		// Iterate over days, until the last is reached
		while (date <= _to_date)
		{
			result.push_back(date.toString("MMMM-dd"));
			date = date.addDays(1);
		}
		return result;
	}
	case EActivityGroupedBy::Month:
	{
		// Iterate over months, until the last is reached
		while (date <= _to_date)
		{
			result.push_back(date.toString("yyyy-MMMM"));
			date = date.addMonths(1);
		}
		return result;
	}
	case EActivityGroupedBy::Year:
	{
		// Iterate over years, until the last is reached
		while (date <= _to_date)
		{
			result.push_back(date.toString("yyyy"));
			date = date.addYears(1);
		}
		return result;
	}
	default:
		qWarning() << "The activity model had invalid grouping";
		return {};
	}
}

std::vector<Providers::EActivityType> ActivityOverviewModel::getActivityTypes() const
{
	return _types;
}

/*
* Gets the vector of values for a specific attribute, in the same order as the categories.
* The values are summed up in each category
*/
std::vector<float> ActivityOverviewModel::getValuesForAttributeByCategory(
	Providers::ActivitySummary::ESummableAttribute attribute,
	Providers::EActivityType) const
{
	std::vector<float> result;

	for (const auto& act : _filtered_acts)
	{

	}
}


std::vector<Providers::ActivitySummary> ActivityOverviewModel::getFilteredActivities() const
{
	return _filtered_acts;
}

void ActivityOverviewModel::recalculate()
{
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

	// Create map of activities by category


	Q_EMIT modelChanged();
}

}
