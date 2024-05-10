#include "ActivityOverviewWidget.h"

#include <Activity.h>
#include "ui_activity_overview_widget.h"
#include "ActivityCollectionChart.h"
#include "ActivityFilterWidget.h"

#include <memory>

namespace Widgets
{

ActivityOverviewWidget::ActivityOverviewWidget(QWidget* parent) : QWidget(parent), ui(new Ui::ActivityOverviewWidget)
{
	ui->setupUi(this);

	// TODO: Get acts from data provider
	std::vector<Providers::ActivitySummary> acts;
	_overview_model = new ActivityOverviewModel(acts, this); // Set with parent -> will take care of destruction
}

}