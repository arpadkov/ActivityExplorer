#include "ActivityFilterWidget.h"

#include <QVBoxLayout>
#include <QPalette>

namespace Widgets
{

ActivityFilterWidget::ActivityFilterWidget(QWidget* parent) : QWidget(parent)
{
	auto calendar_w = new RangeCalendarWidget(this);
	calendar_w->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	auto spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding);

	auto layout = new QHBoxLayout(this);
	layout->addWidget(calendar_w);
	layout->addSpacerItem(spacer);

	setLayout(layout);
}

ActivityFilterWidget::~ActivityFilterWidget()
{
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////          RangedCalendarWidget      /////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


RangeCalendarWidget::RangeCalendarWidget(QWidget* parent) : QCalendarWidget(parent)
{
	_highlight_format.setBackground(palette().brush(QPalette::Highlight));
	_highlight_format.setForeground(palette().brush(QPalette::HighlightedText));

	connect(this, &QCalendarWidget::clicked, this, &RangeCalendarWidget::highlightDateFromRange);
}

RangeCalendarWidget::~RangeCalendarWidget()
{
}

void RangeCalendarWidget::highlightDateFromRange(QDate date)
{
	setDateTextFormat(date, _highlight_format);
}


}
