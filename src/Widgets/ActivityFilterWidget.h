#pragma once

#include <QDate>
#include <QWidget>
#include <QCalendarWidget>
#include <QTextCharFormat>

// Forwards
namespace Widgets
{
enum class EActivityGroupedBy : int;
}

namespace Widgets
{

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