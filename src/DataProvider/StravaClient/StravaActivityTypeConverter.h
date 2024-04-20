#pragma once

#include <optional>

// Forwards
class QString;

namespace Providers
{
enum class EActivityType : int;
}


namespace Providers::StravaClient
{

std::optional<EActivityType> stringtoActivityType(const QString& type_str);

}