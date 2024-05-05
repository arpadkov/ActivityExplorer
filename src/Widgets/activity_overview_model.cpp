#include "ActivityOverviewModel.h"

#include <ActivityType.h>

namespace Widgets
{

ActivityOverviewModel::ActivityOverviewModel(QObject* parent) : QObject(parent)
{
	// TODO
	_filtered_acts = {};
}

ActivityOverviewModel::~ActivityOverviewModel()
{
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

	switch (_grouped_by)
	{
	case EActivityGroupedBy::Day:
	{
		// Get the days in that month
	}
	case EActivityGroupedBy::Month:
	{
		for (int i = 1; i <= 12; i++)
			result.push_back(QDate(2000, i, 1).toString("MMMM"));
	}
	case EActivityGroupedBy::Year:
	default:
		qWarning() << "The activity model had invalid grouping";
		return {};
	}
}


std::vector<Providers::ActivitySummary> ActivityOverviewModel::getFilteredActivities() const
{
	return _filtered_acts;
}

}
