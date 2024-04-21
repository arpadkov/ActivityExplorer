#pragma once

#include <optional>

// Forwards
class NetworkReply;
class ErrorDetail;

namespace Providers
{
struct ActivitySummary;
}


namespace Providers::StravaClient
{

std::optional<ActivitySummary> activitySummaryFromStravaReply(const NetworkReply& reply, ErrorDetail& error);

}