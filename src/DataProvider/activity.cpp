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

QString activityTypeToString(EActivityType type)
{
	switch (type)
	{
	case EActivityType::AlpineSki:
			return "Alpine ski";
  case EActivityType::BackcountrySki:
    return "Backcountry ski";
  case EActivityType::Badminton:
    return "Badminton";
  case EActivityType::Canoeing:
    return "Canoeing";
  case EActivityType::Crossfit:
    return "Crossfit";
  case EActivityType::EBikeRide:
    return "E-bike ride";
  case EActivityType::Elliptical:
    return "Elliptical";
  case EActivityType::EMountainBikeRide:
    return "E-mountain bike ride";
  case EActivityType::Golf:
    return "Golf";
  case EActivityType::GravelRide:
    return "Gravel ride";
  case EActivityType::Handcycle:
    return "Handcycle";
  case EActivityType::HighIntensityIntervalTraining:
    return "High-intensity interval training";
  case EActivityType::Hike:
    return "Hike";
  case EActivityType::IceSkate:
    return "Ice skate";
  case EActivityType::InlineSkate:
    return "Inline skate";
  case EActivityType::Kayaking:
    return "Kayaking";
  case EActivityType::Kitesurf:
    return "Kitesurf";
  case EActivityType::MountainBikeRide:
    return "Mountain bike ride";
  case EActivityType::NordicSki:
    return "Nordic ski";
  case EActivityType::Pickleball:
    return "Pickleball";
  case EActivityType::Pilates:
    return "Pilates";
  case EActivityType::Racquetball:
    return "Racquetball";
  case EActivityType::Ride:
    return "Ride";
  case EActivityType::RockClimbing:
    return "Rock climbing";
  case EActivityType::RollerSki:
    return "Roller ski";
  case EActivityType::Rowing:
    return "Rowing";
  case EActivityType::Run:
    return "Run";
  case EActivityType::Sail:
    return "Sail";
  case EActivityType::Skateboard:
    return "Skateboard";
  case EActivityType::Snowboard:
    return "Snowboard";
  case EActivityType::Snowshoe:
    return "Snowshoe";
  case EActivityType::Soccer:
    return "Soccer";
  case EActivityType::Squash:
    return "Squash";
  case EActivityType::StairStepper:
    return "Stair stepper";
  case EActivityType::StandUpPaddling:
    return "Stand-up paddling";
  case EActivityType::Surfing:
    return "Surfing";
  case EActivityType::Swim:
    return "Swim";
  case EActivityType::TableTennis:
    return "Table tennis";
  case EActivityType::Tennis:
    return "Tennis";
  case EActivityType::TrailRun:
    return "Trail run";
  case EActivityType::Velomobile:
    return "Velomobile";
  case EActivityType::VirtualRide:
    return "Virtual ride";
  case EActivityType::VirtualRow:
    return "Virtual row";
  case EActivityType::VirtualRun:
    return "Virtual run";
  case EActivityType::Walk:
    return "Walk";
  case EActivityType::WeightTraining:
    return "Weight training";
  case EActivityType::Wheelchair:
    return "Wheelchair";
  case EActivityType::Windsurf:
    return "Windsurf";
  case EActivityType::Workout:
    return "Workout";
  case EActivityType::Yoga:
    return "Yoga";
  default:
    return "Unknown";
  }
}

QString summableAttributeToString(ActivitySummary::ESummableAttribute attribute)
{
  switch (attribute)
  {
  case ActivitySummary::ESummableAttribute::Distance:
    return "Distance";
  case ActivitySummary::ESummableAttribute::MovingTime:
    return "Moving time";
  case ActivitySummary::ESummableAttribute::ElapsedTime:
    return "Elapsed time";
  case ActivitySummary::ESummableAttribute::ElevationGain:
    return "Elevation gain";
  case ActivitySummary::ESummableAttribute::Calories:
    return "Calories";
  default:
    return "Unknown attribute";
  }
}

}