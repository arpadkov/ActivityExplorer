#pragma once

#include <Activity.h>

#include <QDate>
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
	ActivityOverviewModel(const std::vector<Providers::ActivitySummary>& acts, QObject* parent = nullptr);
	~ActivityOverviewModel();

	void setGroupedBy(EActivityGroupedBy grouping);
	void setDateRange(const QDate& from, const QDate& to);

	std::vector<Providers::ActivitySummary::ESummableAttribute> getAttributes() const;
	bool getStacked() const;

	EActivityGroupedBy getGroupedBy() const;
	QStringList getCategories() const;
	std::vector<Providers::EActivityType> getActivityTypes() const;

	std::vector<float> getValuesForAttributeByCategory(
		Providers::ActivitySummary::ESummableAttribute attribute,
		Providers::EActivityType) const;

	std::vector<Providers::ActivitySummary> getFilteredActivities() const;

private:
	void recalculate();

	std::vector<Providers::ActivitySummary> _acts;
	std::vector<Providers::ActivitySummary> _filtered_acts;

	QDate _from_date;
	QDate _to_date;

	std::vector<Providers::EActivityType> _types;
	std::vector<Providers::ActivitySummary::ESummableAttribute> _attributes;
	EActivityGroupedBy _grouped_by = EActivityGroupedBy::Unknown;
	bool _stacked = true;

	std::map<QString, std::vector<Providers::ActivitySummary>> _acts_by_category;

Q_SIGNALS:
	void modelChanged();	// This is used to notify the outside, once everything is recalculated

};


}