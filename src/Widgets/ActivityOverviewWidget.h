#pragma once

#include <ActivityOverviewModel.h>

#include <QWidget>

// Forwards
namespace Ui
{
class ActivityOverviewWidget;
}

namespace Providers
{
class DataProvider;
}

namespace Widgets
{



class ActivityOverviewWidget : public QWidget
{
	Q_OBJECT

public:
	ActivityOverviewWidget(std::shared_ptr<Providers::DataProvider> provider, QWidget* parent = nullptr);
	~ActivityOverviewWidget();

private:
	Ui::ActivityOverviewWidget* ui;
	std::shared_ptr<Providers::DataProvider> _provider;
	std::shared_ptr<ActivityOverviewModel> _overview_model;
};

}