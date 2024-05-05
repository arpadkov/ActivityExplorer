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
	auto activities_w = new ButtonGroupWidget("activities", this);
	activities_w->setExclusive(false);
	activities_w->addButton("run", 1);
	activities_w->addButton("hike", 2);
	activities_w->addButton("walk", 3);
	activities_w->addButton("ride", 4);

	auto datas_w = new ButtonGroupWidget("attributes", this);
	datas_w->setExclusive(false);
	datas_w->addButton("distance", 1);
	datas_w->addButton("elevation", 2);
	datas_w->addButton("time", 3);

	auto layout = new QHBoxLayout(this);
	layout->addWidget(activities_w);
	layout->addSpacerItem(spacer);
	layout->addWidget(new CheckStackedButton(this));

	layout->addWidget(datas_w);

	setLayout(layout);
}

ActivityCollectionChartConfig::~ActivityCollectionChartConfig()
{
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
