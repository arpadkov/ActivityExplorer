#pragma once

#include "ActivityType.h"

#include <QString>
#include <QDateTime>

// Forwards
class NetworkReply;

namespace Providers
{

struct ActivitySummary
{
	ActivitySummary();
	~ActivitySummary();

	QString id;
	QString name;
	EActivityType type;
	float distance = 0;         // meter
	float moving_time = 0;      // second
	float elapsed_time = 0;     // second
	float elev_gain = 0;        // meter
	QDateTime start_date;
	float average_speed = 0;    // m/s
	float max_speed = 0;        // m/s
	float calories = 0;         // kcal
};

bool operator==(const ActivitySummary& lhs, const ActivitySummary& rhs);
bool operator!=(const ActivitySummary& lhs, const ActivitySummary& rhs);

Q_DECLARE_METATYPE(ActivitySummary)

}