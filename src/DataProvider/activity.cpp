#include "Activity.h"

namespace Providers
{

ActivitySummary::ActivitySummary()
{
}

ActivitySummary::~ActivitySummary()
{
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