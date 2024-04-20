#pragma once

#include "ActivityType.h"

#include <QString>
#include <QDateTime>

namespace Providers
{

class ActivitySummary
{
public:
	ActivitySummary();
	~ActivitySummary();

private:
	QString _id;
	QString _name;
	EActivityType _type;
	float _distance = 0;			// meter
	float _moving_time = 0;		// second
	float _elapsed_time = 0;	// second
	float _elev_gain = 0;			// meter
	QDateTime _start_date;
	float _average_speed = 0; // m/s
	float _max_speed = 0;			// m/s
	float calories = 0;				// kcal
};

}