#pragma once

#include <QGroupBox>
#include <QButtongroup>
#include <QHBoxLayout>

namespace Widgets
{

class ButtonGroupWidget : public QGroupBox

{
	Q_OBJECT

public:
	ButtonGroupWidget(const QString& title, QWidget* parent);
	~ButtonGroupWidget();

	void addButton(const QString& text, int index);
	void setCheckedButton(int index);
	void setExclusive(bool exclusive);

private:
	QButtonGroup* _bg;
	QHBoxLayout* _layout;
};

}