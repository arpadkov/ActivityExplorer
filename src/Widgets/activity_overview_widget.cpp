#include "ActivityOverviewWidget.h"

#include <Activity.h>
#include "ui_activity_overview_widget.h"
#include "ActivityCollectionChart.h"
#include "ActivityFilterWidget.h"
#include <DataProvider.h>

#include <memory>

namespace Widgets
{

ActivityOverviewWidget::ActivityOverviewWidget(std::shared_ptr<Providers::DataProvider> provider, QWidget* parent) :
	QWidget(parent), ui(new Ui::ActivityOverviewWidget), _provider(provider)
{
	ui->setupUi(this);

	auto acts = _provider->getActivitySummaries();

	_overview_model = new ActivityOverviewModel(acts, this); // Set with parent -> will take care of destruction
	QObject::connect(_overview_model, &ActivityOverviewModel::modelChanged,	ui->act_collection_chart,
		[this]()
		{
			ui->act_collection_chart->updateChart(*_overview_model);
		});

	_overview_model->setStacked(false);
	_overview_model->setGroupedBy(EActivityGroupedBy::Month);
	_overview_model->setDateRange(QDate(2024, 1, 1), QDate(2024, 5, 30));
	_overview_model->setActivityTypes({ Providers::EActivityType::Run, Providers::EActivityType::Hike});
	_overview_model->setAttributes({ Providers::ActivitySummary::ESummableAttribute::Distance,
		Providers::ActivitySummary::ESummableAttribute::ElevationGain });
}

}