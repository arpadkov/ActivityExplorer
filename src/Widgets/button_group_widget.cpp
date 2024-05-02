#include "ButtonGroupWidget.h"

#include <QPushButton>

namespace Widgets
{

ButtonGroupWidget::ButtonGroupWidget(const QString& title, QWidget* parent) : QGroupBox(parent)
{
	_bg = new QButtonGroup(this);

	//auto year_b = new QPushButton("year", this);
	//year_b->setCheckable(true);
	//year_b->setFlat(true);
	//year_b->setChecked(true);
	//_bg->addButton(year_b, 1);

	//auto month_b = new QPushButton("month", this);
	//month_b->setCheckable(true);
	//month_b->setFlat(true);
	//_bg->addButton(month_b, 2);

	//auto day_b = new QPushButton("day", this);
	//day_b->setCheckable(true);
	//day_b->setFlat(true);
	//_bg->addButton(day_b, 3);

	_layout = new QHBoxLayout(this);
	//layout->addWidget(year_b);
	//layout->addWidget(month_b);
	//layout->addWidget(day_b);

	setLayout(_layout);

	setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	setTitle(title);
}

ButtonGroupWidget::~ButtonGroupWidget()
{
}

void ButtonGroupWidget::addButton(const QString& text, int index)
{
	auto btn = new QPushButton(text, this);
	btn->setCheckable(true);
	btn->setFlat(true);
	_bg->addButton(btn, index);
	_layout->addWidget(btn);
}

void ButtonGroupWidget::setCheckedButton(int index)
{
	_bg->button(index)->setChecked(true);
}

void ButtonGroupWidget::setExclusive(bool exclusive)
{
	_bg->setExclusive(exclusive);
}

}