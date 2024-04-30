#pragma once

#include "ActivityType.h"

#include <QDateTime>

// Forwards
namespace Providers
{
class ActivitySummary;
}


namespace Providers
{

enum class EActivityGroupedBy : uint
{
	Unknown = 0,
	Year = 1,
	Month = 2,
	Day = 3
};

struct ActivityFilter
{
	QDateTime from_date;
	QDateTime to_date;

	std::vector<EActivityType> types;
	EActivityGroupedBy grouped_by;

	std::vector<ActivitySummary> getFilteredActivities(const std::vector<ActivitySummary>& input_summaries) const;
};


}