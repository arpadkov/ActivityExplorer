#pragma once

#include <QDate>
#include <QWidget>
#include <QCalendarWidget>
#include <QTextCharFormat>

namespace Widgets
{

enum class EGroupedBy : int
{
	Unknown = 0,
	Year = 1,
	Month = 2,
	Day = 3
};

class RangeCalendarWidget : public QCalendarWidget
{
	Q_OBJECT

public:
	RangeCalendarWidget(QWidget* parent);
	~RangeCalendarWidget();

private:
	QTextCharFormat _highlight_format = {};
	QDate _from_date;
	QDate _to_date;

public Q_SLOTS:
	void highlightDateFromRange(QDate date);
};


class ActivityFilterWidget : public QWidget
{
	Q_OBJECT

public:
	ActivityFilterWidget(QWidget* parent);
	~ActivityFilterWidget();

private:
	RangeCalendarWidget* _calendar_w;

};

}