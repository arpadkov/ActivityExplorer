#include "StravaActivityTypeConverter.h"

#include <ActivityType.h>

#include <QDebug>
#include <QString>
#include <map>

namespace Providers::StravaClient
{

std::map<QString, EActivityType> types_map = {
  {"AlpineSki", EActivityType::AlpineSki},
  {"BackcountrySki", EActivityType::BackcountrySki},
  {"Badminton", EActivityType::Badminton},
  {"Canoeing", EActivityType::Canoeing},
  {"Crossfit", EActivityType::Crossfit},
  {"EBikeRide", EActivityType::EBikeRide},
  {"Elliptical", EActivityType::Elliptical},
  {"EMountainBikeRide", EActivityType::EMountainBikeRide},
  {"Golf", EActivityType::Golf},
  {"GravelRide", EActivityType::GravelRide},
  {"Handcycle", EActivityType::Handcycle},
  {"HighIntensityIntervalTraining", EActivityType::HighIntensityIntervalTraining},
  {"Hike", EActivityType::Hike},
  {"IceSkate", EActivityType::IceSkate},
  {"InlineSkate", EActivityType::InlineSkate},
  {"Kayaking", EActivityType::Kayaking},
  {"Kitesurf", EActivityType::Kitesurf},
  {"MountainBikeRide", EActivityType::MountainBikeRide},
  {"NordicSki", EActivityType::NordicSki},
  {"Pickleball", EActivityType::Pickleball},
  {"Pilates", EActivityType::Pilates},
  {"Racquetball", EActivityType::Racquetball},
  {"Ride", EActivityType::Ride},
  {"RockClimbing", EActivityType::RockClimbing},
  {"RollerSki", EActivityType::RollerSki},
  {"Rowing", EActivityType::Rowing},
  {"Run", EActivityType::Run},
  {"Sail", EActivityType::Sail},
  {"Skateboard", EActivityType::Skateboard},
  {"Snowboard", EActivityType::Snowboard},
  {"Snowshoe", EActivityType::Snowshoe},
  {"Soccer", EActivityType::Soccer},
  {"Squash", EActivityType::Squash},
  {"StairStepper", EActivityType::StairStepper},
  {"StandUpPaddling", EActivityType::StandUpPaddling},
  {"Surfing", EActivityType::Surfing},
  {"Swim", EActivityType::Swim},
  {"TableTennis", EActivityType::TableTennis},
  {"Tennis", EActivityType::Tennis},
  {"TrailRun", EActivityType::TrailRun},
  {"Velomobile", EActivityType::Velomobile},
  {"VirtualRide", EActivityType::VirtualRide},
  {"VirtualRow", EActivityType::VirtualRow},
  {"VirtualRun", EActivityType::VirtualRun},
  {"Walk", EActivityType::Walk},
  {"WeightTraining", EActivityType::WeightTraining},
  {"Wheelchair", EActivityType::Wheelchair},
  {"Windsurf", EActivityType::Windsurf},
  {"Workout", EActivityType::Workout},
  {"Yoga", EActivityType::Yoga}
};

std::optional<EActivityType> stringtoActivityType(const QString& type_str)
{
  auto it = types_map.find(type_str);
  if (it != types_map.end())
    return it->second;
  else
  {
    qWarning() << "(ActivityTypeConverter): Type not found: " << type_str;
    return std::nullopt;
  }
}


}