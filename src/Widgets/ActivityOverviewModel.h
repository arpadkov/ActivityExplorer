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

enum class ECategoryStringFormat : int
{
	Unknown = 0,
	Full = 1,			// The full description with from to date
	WithAddition = 2, // Prepends the Month/Year 
	Simple = 3, // Only the Day/Month/Year
};

/*
* This class represents a category on the bar plot (e.g. a year, month or day)
*/
struct ActivityCategory
{
	ActivityCategory(const QDate& from_date_, const QDate& to_date_, EActivityGroupedBy grouped_by);

	QString toString(ECategoryStringFormat format) const;

	QDate from_date;
	QDate to_date;

	bool operator<(const ActivityCategory& other) const;
	bool operator==(const ActivityCategory& other) const;
	bool operator!=(const ActivityCategory& other) const;

private:
	EActivityGroupedBy _grouped_by;
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

	// Setters
	void setStacked(bool stacked);
	void setGroupedBy(EActivityGroupedBy grouping);
	void setDateRange(const QDate& from, const QDate& to);
	void setActivityTypes(const std::vector<Providers::EActivityType>& types);
	void setAttributes(const std::vector<Providers::ActivitySummary::ESummableAttribute>& attributes);

	// Simple get methods
	std::vector<Providers::ActivitySummary::ESummableAttribute> getAttributes() const;
	bool isStacked() const;
	std::vector<Providers::EActivityType> getActivityTypes() const;

	// Calculated get methods
	EActivityGroupedBy getGroupedBy() const;
	std::vector<ActivityCategory> getCategories() const;
	std::map<ActivityCategory, std::vector<Providers::ActivitySummary>> getActivitiesByCategory() const;

	std::vector<std::pair<ActivityCategory, float>> getValuesForAttributeByCategory(
		Providers::ActivitySummary::ESummableAttribute attribute,
		Providers::EActivityType type) const;

	std::vector<Providers::ActivitySummary> getFilteredActivities() const;

private:
	bool isValid() const;
	void recalculate();
	void recalculateCategories();
	std::optional<std::pair<int, int>> getFirstAndLastActivityIndexOfCategory(
		int start_at_act, const ActivityCategory& category) const;
	std::optional<int> getFirstActivityIndexOfCategory(
		int start_at_act, const ActivityCategory& category) const;
	std::optional<int> getLastActivityIndexOfCategory(
		int start_at_act, const ActivityCategory& category) const;

	// Settable member
	std::vector<Providers::ActivitySummary> _acts;
	QDate _from_date;
	QDate _to_date;
	std::vector<Providers::EActivityType> _types;
	std::vector<Providers::ActivitySummary::ESummableAttribute> _attributes;
	EActivityGroupedBy _grouped_by = EActivityGroupedBy::Unknown;
	bool _is_stacked = true;

	// Calculated members
	std::vector<Providers::ActivitySummary> _filtered_acts;
	std::vector<ActivityCategory> _categories;
	std::map<ActivityCategory, std::vector<Providers::ActivitySummary>> _acts_by_category;

Q_SIGNALS:
	void modelChanged();	// This is used to notify the outside, once everything is recalculated

};


}