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

	_overview_model = std::make_shared<ActivityOverviewModel>(acts, this);
	
	connect(_overview_model.get(), &ActivityOverviewModel::modelChanged, ui->act_collection_chart,
		[this]()
		{
			ui->act_collection_chart->updateChart(_overview_model);
		});

	connect(ui->act_filter_w, &ActivityFilterWidget::groupedByChanged, this, [this]()
		{
			_overview_model->setGroupedBy(ui->act_filter_w->getGroupedBy());
		});
	connect(ui->act_filter_w, &ActivityFilterWidget::dateRangeChanged, this, [this]()
		{
			const auto& date_range = ui->act_filter_w->getDateRange();
			_overview_model->setDateRange(date_range.first, date_range.second);
		});

	connect(ui->chart_config_w, &ActivityCollectionChartConfig::isStackedChanged, this, [this]()
		{
			_overview_model->setStacked(ui->chart_config_w->getIsStacked());
		});
	connect(ui->chart_config_w, &ActivityCollectionChartConfig::activityTypesChanged, this, [this]()
		{
			_overview_model->setActivityTypes(ui->chart_config_w->getActivityTypes());
		});
	connect(ui->chart_config_w, &ActivityCollectionChartConfig::attributesChanged, this, [this]()
		{
			_overview_model->setAttributes(ui->chart_config_w->getAttributes());
		});

	_overview_model->setStacked(false);
	_overview_model->setGroupedBy(EActivityGroupedBy::Year);
	_overview_model->setDateRange(QDate(2024, 1, 1), QDate(2024, 5, 30));
	_overview_model->setActivityTypes({ Providers::EActivityType::Run, Providers::EActivityType::Hike});
	_overview_model->setAttributes({ Providers::ActivitySummary::ESummableAttribute::Distance,
		Providers::ActivitySummary::ESummableAttribute::ElevationGain });
}

ActivityOverviewWidget::~ActivityOverviewWidget()
{
}

}