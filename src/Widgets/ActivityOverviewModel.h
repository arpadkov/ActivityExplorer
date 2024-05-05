#pragma once

#include <Activity.h>

#include <QDateTime>
#include <QObject>

// Forwards
namespace Providers
{
class ActivitySummary;
enum class EActivityType : int;
}

namespace Widgets
{

enum class EActivityGroupedBy : int
{
	Unknown = 0,
	Year = 1,
	Month = 2,
	Day = 3
};

/*
*	This class is responsible to deliver the data for the ActivityCollectionChart.
* Gets updated from the config widgets, and calcluates all the neccessary activities by the required grouping
*/
class ActivityOverviewModel : public QObject
{
	Q_OBJECT

public:
	ActivityOverviewModel(QObject* parent = nullptr);
	~ActivityOverviewModel();

	std::vector<Providers::ActivitySummary::ESummableAttribute> getAttributes() const;
	bool getStacked() const;
	EActivityGroupedBy getGroupedBy() const;
	QStringList getCategories() const;

	std::vector<Providers::ActivitySummary> getFilteredActivities() const;

private:
	std::vector<Providers::ActivitySummary> _filtered_acts;

	QDateTime _from_date;
	QDateTime _to_date;

	std::vector<Providers::EActivityType> _types;
	std::vector<Providers::ActivitySummary::ESummableAttribute> _attributes;
	EActivityGroupedBy _grouped_by;
	bool _stacked = true;
};


}