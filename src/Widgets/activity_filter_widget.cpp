#include "ActivityFilterWidget.h"
#include "ButtonGroupWidget.h"

#include <QPalette>
#include <QPushButton>

namespace Widgets
{

ActivityFilterWidget::ActivityFilterWidget(QWidget* parent) : QWidget(parent)
{
	_calendar_w = new RangeCalendarWidget(this);
	_calendar_w->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	auto calendar_button = new QPushButton(this);

	auto spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding);

	// Grouped by widget
	auto grouped_by_w = new ButtonGroupWidget("group by", this);
	grouped_by_w->addButton("year", static_cast<int>(EGroupedBy::Year));
	grouped_by_w->addButton("month", static_cast<int>(EGroupedBy::Month));
	grouped_by_w->addButton("day", static_cast<int>(EGroupedBy::Day));
	grouped_by_w->setCheckedButton(static_cast<int>(EGroupedBy::Year));


	auto layout = new QHBoxLayout(this);
	layout->addWidget(_calendar_w);
	layout->addWidget(calendar_button);
	layout->addSpacerItem(spacer);
	layout->addWidget(grouped_by_w, Qt::AlignTop);



	

	setLayout(layout);

	connect(calendar_button, &QPushButton::clicked, this, [&]()
		{			
				_calendar_w->setHidden(!_calendar_w->isHidden());
		});
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

	setSelectionMode(QCalendarWidget::NoSelection);

	//setSelectedDate({});
	//qInfo() << "SELECTED DATE: " << selectedDate();

	connect(this, &QCalendarWidget::clicked, this, &RangeCalendarWidget::highlightDateFromRange);
}

RangeCalendarWidget::~RangeCalendarWidget()
{
}

void RangeCalendarWidget::highlightDateFromRange(QDate date)
{
	qInfo() << "SELECTED DATE: " << selectedDate();


	setDateTextFormat(date, _highlight_format);
}

}
