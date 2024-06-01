#include "ActivityCollectionChartConfig.h"
#include "ButtonGroupWidget.h"

#include <QSpacerItem>
#include <QHBoxLayout>

namespace Widgets
{

ActivityCollectionChartConfig::ActivityCollectionChartConfig(QWidget* parent) : QWidget(parent)
{
	auto spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding);

	// Activities widget
	_activities_w = new ButtonGroupWidget("activities", this);
	_activities_w->setExclusive(false);
	addActivityTypeButton(Providers::EActivityType::Run);
	addActivityTypeButton(Providers::EActivityType::Hike);
	addActivityTypeButton(Providers::EActivityType::Walk);
	addActivityTypeButton(Providers::EActivityType::Ride);

	// Attrbitues widget
	_attributes_w = new ButtonGroupWidget("attributes", this);
	_attributes_w->setExclusive(false);
	addAttributeButton(Providers::ActivitySummary::ESummableAttribute::Distance);
	addAttributeButton(Providers::ActivitySummary::ESummableAttribute::ElevationGain);
	addAttributeButton(Providers::ActivitySummary::ESummableAttribute::ElapsedTime);

	auto layout = new QHBoxLayout(this);
	layout->addWidget(_activities_w);
	layout->addSpacerItem(spacer);

	_stacked_w = new CheckStackedButton(this);
	layout->addWidget(_stacked_w);

	layout->addWidget(_attributes_w);

	setLayout(layout);

	connect(_activities_w, &ButtonGroupWidget::checkedButtonChanged, this, [this]()
		{
			Q_EMIT activityTypesChanged();
		});
	connect(_attributes_w, &ButtonGroupWidget::checkedButtonChanged, this, [this]()
		{
			Q_EMIT attributesChanged();
		});
	connect(_stacked_w, &QPushButton::toggled, this, [this]()
		{
			Q_EMIT isStackedChanged();
		});
}

ActivityCollectionChartConfig::~ActivityCollectionChartConfig()
{
}

std::vector<Providers::ActivitySummary::ESummableAttribute> ActivityCollectionChartConfig::getAttributes() const
{
	std::vector<Providers::ActivitySummary::ESummableAttribute> res;
	for (int attr_value : _attributes_w->getCheckedButtons())
		res.push_back(Providers::ActivitySummary::ESummableAttribute(attr_value));

	return res;
}

bool ActivityCollectionChartConfig::getIsStacked() const
{
	return _stacked_w->isChecked();
}

std::vector<Providers::EActivityType> ActivityCollectionChartConfig::getActivityTypes() const
{
	std::vector<Providers::EActivityType> res;
	for (int attr_value : _activities_w->getCheckedButtons())
		res.push_back(Providers::EActivityType(attr_value));

	return res;
}

/*
* Adds an attrbitue button, with the text and int value from the attribute
*/
void ActivityCollectionChartConfig::addAttributeButton(Providers::ActivitySummary::ESummableAttribute attribute)
{
	const auto& text = Providers::summableAttributeToString(attribute);
	int value = static_cast<int>(attribute);
	_attributes_w->addButton(text, value);
}

void ActivityCollectionChartConfig::addActivityTypeButton(Providers::EActivityType type)
{
	const auto& text = Providers::activityTypeToString(type);
	int value = static_cast<int>(type);
	_activities_w->addButton(text, value);
}

CheckStackedButton::CheckStackedButton(QWidget* parent) : QPushButton(parent)
{
	setText("stacked");

	setCheckable(true);
}

CheckStackedButton::~CheckStackedButton()
{
}

void CheckStackedButton::mousePressEvent(QMouseEvent* event)
{
	setChecked(!isChecked());
}

}
