#pragma once

#include <Activity.h>

#include <QWidget>
#include <QPushButton>

// Forwards
namespace Widgets
{
class ButtonGroupWidget;
class CheckStackedButton;
}

namespace Widgets
{

class ActivityCollectionChartConfig : public QWidget
{
	Q_OBJECT

public:
	ActivityCollectionChartConfig(QWidget* parent);
	~ActivityCollectionChartConfig();

	std::vector<Providers::ActivitySummary::ESummableAttribute> getAttributes() const;
	bool getIsStacked() const;
	std::vector<Providers::EActivityType> getActivityTypes() const;

Q_SIGNALS:
	void isStackedChanged();
	void activityTypesChanged();
	void attributesChanged();

private:
	void addAttributeButton(Providers::ActivitySummary::ESummableAttribute attribute);
	void addActivityTypeButton(Providers::EActivityType type);

	ButtonGroupWidget* _activities_w;
	ButtonGroupWidget* _attributes_w;
	CheckStackedButton* _stacked_w;
};

class CheckStackedButton : public QPushButton
{
	Q_OBJECT

public:
	CheckStackedButton(QWidget* parent);
	~CheckStackedButton();

protected:
	void mousePressEvent(QMouseEvent* event) override;
};

}