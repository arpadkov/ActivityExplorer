#pragma once

#include <QDate>
#include <QWidget>
#include <QCalendarWidget>
#include <QTextCharFormat>

// Forwards
namespace Widgets
{
enum class EActivityGroupedBy : int;
class ButtonGroupWidget;
}


namespace Widgets
{

class RangeCalendarWidget : public QCalendarWidget
{
	Q_OBJECT

public:
	RangeCalendarWidget(QWidget* parent);
	~RangeCalendarWidget();

	std::pair<QDate, QDate> getDateRange() const;

private:
	void highlightDateRange(const QDate& from, const QDate& to);
	void clearSelection();

	QTextCharFormat _highlight_format = {};
	QTextCharFormat _normal_format = {};
	QDate _from_date;
	QDate _to_date;
	QDate _prev_selected_date;

public Q_SLOTS:
	void onDateClicked(QDate date);

Q_SIGNALS:
	void dateSelectionChanged();
};


class ActivityFilterWidget : public QWidget
{
	Q_OBJECT

public:
	ActivityFilterWidget(QWidget* parent);
	~ActivityFilterWidget();

	EActivityGroupedBy getGroupedBy() const;
	std::pair<QDate, QDate> getDateRange() const;

Q_SIGNALS:
	void groupedByChanged();
	void dateRangeChanged();

private:
	RangeCalendarWidget* _calendar_w;
	ButtonGroupWidget* _grouped_by_w;

};

}