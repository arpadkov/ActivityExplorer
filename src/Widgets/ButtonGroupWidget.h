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

	std::vector<int> getCheckedButtons() const;

Q_SIGNALS:
	void checkedButtonChanged();

private:
	QButtonGroup* _bg;
	QHBoxLayout* _layout;
};

}