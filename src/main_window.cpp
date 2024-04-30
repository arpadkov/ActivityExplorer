#include "MainWindow.h"
#include <Map/mapviewwindow.h>
#include <DataProvider.h>
#include <Activity.h>
#include <ErrorDetail.h>

#include "ui_main_window.h"
#include <ActivityOverviewWidget.h>

#include <QDebug>
#include <QElapsedTimer>

const QString PRODUCT_NAME = "ActivityExplorer";
const QString COMPANY_NAME = "ArpadKov";

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	QObject::connect(
		ui->test_button, &QPushButton::clicked, this, &MainWindow::testFunction);

	// Menu actions
	QObject::connect(ui->act_setup_data_provider, &QAction::triggered, this, []()
		{
			Providers::configureDataProvider();
		});

	// Confugre main tab widget
	auto act_overview_w = new Widgets::ActivityOverviewWidget(this);
	ui->tab_widget->addTab(act_overview_w, "Activities");

}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::testFunction()
{
	_provider = Providers::getDataProvider(Providers::STRAVA_CLIENT);
	bool initilazed = false;
	if (_provider)
		initilazed = _provider->initilizeProvider();

	if (!initilazed) 
	{
		qWarning() << "NOT INITILIZED";
		return;
	}


	ErrorDetail error;
	auto acts = _provider->getActivitySummaries();
	int act_num = 1;
	for (const auto& act : acts)
	{
		//qInfo() << "ACTIVITY : " << act_num << " - " << act.start_date.toString("yyyy-MM-dd");
		act_num++;
	}

	qInfo() << "HAS ACTIVITIES: " << acts.size();


	//auto map_window = new MapViewWindow(this);
	//map_window->show();

	//auto client =
	// DataProvider::initializeDataProvider(DataProvider::LOCAL_PROVIDER);
}
