#pragma once

#include <QDate>
#include <QWidget>
#include <QCalendarWidget>
#include <QTextCharFormat>

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

public Q_SLOTS:
	void highlightDateFromRange(QDate date);
};


class ActivityFilterWidget : public QWidget
{
	Q_OBJECT

public:
	ActivityFilterWidget(QWidget* parent);
	~ActivityFilterWidget();

};

}