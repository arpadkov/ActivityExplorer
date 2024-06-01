#include "ActivityFilterWidget.h"
#include "ActivityOverviewModel.h"
#include "ButtonGroupWidget.h"

#include <QPalette>
#include <QPushButton>

namespace Widgets
{

ActivityFilterWidget::ActivityFilterWidget(QWidget* parent) :
	QWidget(parent)
{
	_calendar_w = new RangeCalendarWidget(this);
	_calendar_w->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	auto calendar_button = new QPushButton(this);

	auto spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding);

	// Grouped by widget
	_grouped_by_w = new ButtonGroupWidget("group by", this);
	_grouped_by_w->addButton("year", static_cast<int>(EActivityGroupedBy::Year));
	_grouped_by_w->addButton("month", static_cast<int>(EActivityGroupedBy::Month));
	_grouped_by_w->addButton("day", static_cast<int>(EActivityGroupedBy::Day));
	_grouped_by_w->setCheckedButton(static_cast<int>(EActivityGroupedBy::Year));


	auto layout = new QHBoxLayout(this);
	layout->addWidget(_calendar_w);
	layout->addWidget(calendar_button);
	layout->addSpacerItem(spacer);
	layout->addWidget(_grouped_by_w, Qt::AlignTop);

	setLayout(layout);

	connect(calendar_button, &QPushButton::clicked, this, [&]()
		{
			_calendar_w->setHidden(!_calendar_w->isHidden());
		});

	connect(_grouped_by_w, &ButtonGroupWidget::checkedButtonChanged, this, [this]()
		{
			Q_EMIT groupedByChanged();
		});

	connect(_calendar_w, &RangeCalendarWidget::dateSelectionChanged, this, [this]()
		{
			Q_EMIT dateRangeChanged();
		});
}

ActivityFilterWidget::~ActivityFilterWidget()
{
}

EActivityGroupedBy ActivityFilterWidget::getGroupedBy() const
{
	const auto& checked_ids = _grouped_by_w->getCheckedButtons();
	if (checked_ids.size() != 1)
		qWarning() << "ActivityFilterWidget: grouped_by widget had more than one buttons checked";

	return EActivityGroupedBy(checked_ids.front());

}

std::pair<QDate, QDate> ActivityFilterWidget::getDateRange() const
{
	return _calendar_w->getDateRange();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////          RangedCalendarWidget      /////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


RangeCalendarWidget::RangeCalendarWidget(QWidget* parent) : QCalendarWidget(parent)
{
	_highlight_format.setBackground(palette().brush(QPalette::Highlight));
	_highlight_format.setForeground(palette().brush(QPalette::HighlightedText));

	_normal_format.setBackground(palette().brush(QPalette::Base));
	_normal_format.setForeground(palette().brush(QPalette::Text));

	_to_date = QDate::currentDate();
	_prev_selected_date = _to_date;
	setMaximumDate(_to_date);
	setMinimumDate(QDate(1990, 1, 1));


	//QDate set_date = minimumDate();
	//while (set_date != maximumDate())
	//{
	//	setDateTextFormat(set_date, _normal_format);

	//	set_date = set_date.addDays(1);
	//}

	setSelectionMode(QCalendarWidget::SingleSelection);

	//setSelectedDate({});
	//qInfo() << "SELECTED DATE: " << selectedDate();

	connect(this, &QCalendarWidget::clicked, this, &RangeCalendarWidget::onDateClicked);
}

RangeCalendarWidget::~RangeCalendarWidget()
{
}

std::pair<QDate, QDate> RangeCalendarWidget::getDateRange() const
{
	return { _from_date, _to_date };
}

void RangeCalendarWidget::highlightDateRange(const QDate& from, const QDate& to)
{
	if (!from.isValid() || !to.isValid())
		return;

	qInfo() << "HIGHLIGHT RANGE: " << from << " - " << to;

	QDate d = from;
	while (d <= to)
	{
		setDateTextFormat(d, _highlight_format);
		d = d.addDays(1);
	}
}

void RangeCalendarWidget::clearSelection()
{
	QDate d = minimumDate();
	while (d <= maximumDate())
	{
		setDateTextFormat(d, _normal_format);
		d = d.addDays(1);
	}
}

void RangeCalendarWidget::onDateClicked(QDate date)
{
	qInfo() << "SELECTED DATE " << _prev_selected_date;
	// At least one date is invalid -> set both correctly
	if (!_from_date.isValid() || !_to_date.isValid())
	{
		qInfo() << "ONE DATE INVALID";
		if (date == _prev_selected_date)
			return;

		if (date < _prev_selected_date)
		{
			qInfo() << "SMALLER THAN SELECTED";

			_from_date = date;
			_to_date = _prev_selected_date;
		}
		else
		{
			qInfo() << "GREATER THAN SELECTED";

			_from_date = _prev_selected_date;
			_to_date = date;
		}
	}

	// Click inside daterange -> set both invalid (save & highlight selected)
	else if (date > _from_date && date < _to_date)
	{
		qInfo() << "INSIDE RANGE";

		_to_date = QDate();
		_from_date = QDate();
		_prev_selected_date = date;
		clearSelection();
		setDateTextFormat(date, _highlight_format);
	}

	// Click below valid daterange -> extend selection
	else if (date < _from_date)
	{
		qInfo() << "BALOW RANGE";

		_from_date = date;
	}

	// Click above valid daterange -> extend selection
	else if (date > _to_date)
	{
		qInfo() << "ABOVE RANGE";

		_to_date = date;
	}

	else
	{
		qWarning() << "RangeCalendarWidget can not handle date selection";
		return;
	}

	if (_from_date.isValid() && _to_date.isValid())
	{
		highlightDateRange(_from_date, _to_date);
		Q_EMIT dateSelectionChanged();
	}
}

}
