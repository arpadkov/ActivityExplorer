#include "StravaActivityConverter.h"

#include <Activity.h>
#include <ActivityType.h>
#include <ErrorDetail.h>
#include <NetworkReply.h>

#include <QDebug>
#include <QString>
#include <map>

namespace
{

std::map<QString, Providers::EActivityType> types_map = {
  {"AlpineSki", Providers::EActivityType::AlpineSki},
  {"BackcountrySki", Providers::EActivityType::BackcountrySki},
  {"Badminton", Providers::EActivityType::Badminton},
  {"Canoeing", Providers::EActivityType::Canoeing},
  {"Crossfit", Providers::EActivityType::Crossfit},
  {"EBikeRide", Providers::EActivityType::EBikeRide},
  {"Elliptical", Providers::EActivityType::Elliptical},
  {"EMountainBikeRide", Providers::EActivityType::EMountainBikeRide},
  {"Golf", Providers::EActivityType::Golf},
  {"GravelRide", Providers::EActivityType::GravelRide},
  {"Handcycle", Providers::EActivityType::Handcycle},
  {"HighIntensityIntervalTraining", Providers::EActivityType::HighIntensityIntervalTraining},
  {"Hike", Providers::EActivityType::Hike},
  {"IceSkate", Providers::EActivityType::IceSkate},
  {"InlineSkate", Providers::EActivityType::InlineSkate},
  {"Kayaking", Providers::EActivityType::Kayaking},
  {"Kitesurf", Providers::EActivityType::Kitesurf},
  {"MountainBikeRide", Providers::EActivityType::MountainBikeRide},
  {"NordicSki", Providers::EActivityType::NordicSki},
  {"Pickleball", Providers::EActivityType::Pickleball},
  {"Pilates", Providers::EActivityType::Pilates},
  {"Racquetball", Providers::EActivityType::Racquetball},
  {"Ride", Providers::EActivityType::Ride},
  {"RockClimbing", Providers::EActivityType::RockClimbing},
  {"RollerSki", Providers::EActivityType::RollerSki},
  {"Rowing", Providers::EActivityType::Rowing},
  {"Run", Providers::EActivityType::Run},
  {"Sail", Providers::EActivityType::Sail},
  {"Skateboard", Providers::EActivityType::Skateboard},
  {"Snowboard", Providers::EActivityType::Snowboard},
  {"Snowshoe", Providers::EActivityType::Snowshoe},
  {"Soccer", Providers::EActivityType::Soccer},
  {"Squash", Providers::EActivityType::Squash},
  {"StairStepper", Providers::EActivityType::StairStepper},
  {"StandUpPaddling", Providers::EActivityType::StandUpPaddling},
  {"Surfing", Providers::EActivityType::Surfing},
  {"Swim", Providers::EActivityType::Swim},
  {"TableTennis", Providers::EActivityType::TableTennis},
  {"Tennis", Providers::EActivityType::Tennis},
  {"TrailRun", Providers::EActivityType::TrailRun},
  {"Velomobile", Providers::EActivityType::Velomobile},
  {"VirtualRide", Providers::EActivityType::VirtualRide},
  {"VirtualRow", Providers::EActivityType::VirtualRow},
  {"VirtualRun", Providers::EActivityType::VirtualRun},
  {"Walk", Providers::EActivityType::Walk},
  {"WeightTraining", Providers::EActivityType::WeightTraining},
  {"Wheelchair", Providers::EActivityType::Wheelchair},
  {"Windsurf", Providers::EActivityType::Windsurf},
  {"Workout", Providers::EActivityType::Workout},
  {"Yoga", Providers::EActivityType::Yoga}
};

}

std::optional<Providers::EActivityType> stringtoActivityType(const QString& type_str)
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

namespace Providers::StravaClient
{


std::optional<ActivitySummary> activitySummaryFromStravaReply(const NetworkReply& reply, ErrorDetail& error)
{
  ActivitySummary act_summary;

  act_summary.id = QString::number(reply.getIntValue("id").value_or(0));
  act_summary.name = reply.getStringValue("name").value_or("");

  // Get activity type from string
  std::optional<EActivityType> typeOpt = stringtoActivityType(reply.getStringValue("type").value_or(""));
  if (typeOpt.has_value())
  {
    act_summary.type = typeOpt.value();
  }
  else
  {
    // Handle error or provide a default value
    // For now, let's default to an unknown type
    act_summary.type = EActivityType::Unknown;
  }

  act_summary.distance = reply.getFloatValue("distance").value_or(0);
  act_summary.moving_time = reply.getFloatValue("moving_time").value_or(0);
  act_summary.elapsed_time = reply.getFloatValue("elapsed_time").value_or(0);
  act_summary.elev_gain = reply.getFloatValue("elev_gain").value_or(0);
  act_summary.start_date = QDateTime::fromString(reply.getStringValue("start_date").value_or(""), Qt::ISODate);
  act_summary.average_speed = reply.getFloatValue("average_speed").value_or(0);
  act_summary.max_speed = reply.getFloatValue("max_speed").value_or(0);
  act_summary.calories = reply.getFloatValue("calories").value_or(0);

  return act_summary;
}


}