#include "ButtonGroupWidget.h"

#include <QPushButton>

namespace Widgets
{

ButtonGroupWidget::ButtonGroupWidget(const QString& title, QWidget* parent) : QGroupBox(parent)
{
	_bg = new QButtonGroup(this);
	_layout = new QHBoxLayout(this);

	setLayout(_layout);

	setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	setTitle(title);

	QObject::connect(_bg, &QButtonGroup::buttonClicked, this, [this]()
		{
			Q_EMIT checkedButtonChanged();
		});
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
	Q_EMIT checkedButtonChanged();
}

void ButtonGroupWidget::setExclusive(bool exclusive)
{
	_bg->setExclusive(exclusive);
}

std::vector<int> ButtonGroupWidget::getCheckedButtons() const
{
	std::vector<int> checked_buttons;
	for (auto button : _bg->buttons())
	{
		if (button->isChecked())
			checked_buttons.push_back(_bg->id(button));
	}
	return checked_buttons;
}

}