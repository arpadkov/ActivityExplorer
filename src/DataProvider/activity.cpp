#include "Activity.h"

namespace Providers
{

ActivitySummary::ActivitySummary()
{
}

ActivitySummary::~ActivitySummary()
{
}

float ActivitySummary::getSummableAttribute(ESummableAttribute attribute) const
{
	switch (attribute)
	{
	case ESummableAttribute::Distance:
		return distance;
	case ESummableAttribute::MovingTime:
		return moving_time;
	case ESummableAttribute::ElapsedTime:
		return elapsed_time;
	case ESummableAttribute::ElevationGain:
		return elev_gain;
	case ESummableAttribute::Calories:
		return calories;
	}

	return 0;
}

bool operator==(const ActivitySummary& lhs, const ActivitySummary& rhs)
{
	return lhs.id == rhs.id && lhs.name == rhs.name;
}

bool operator!=(const ActivitySummary& lhs, const ActivitySummary& rhs)
{
	return !(lhs == rhs);
}

}