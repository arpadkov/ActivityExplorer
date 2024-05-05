#include "ActivityCollectionChart.h"

#include "ActivityOverviewModel.h"

#include <QAbstractBarSeries>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QDate>
#include <QValueAxis>
#include <QStackedBarSeries>
#include <QChart>
#include <QColor>
#include <QGraphicsLayout>

namespace Widgets
{

namespace
{

}

ActivityCollectionChart::ActivityCollectionChart(QWidget* parent) : QChartView(parent)
{

	QVector<int> runDistances = { 100, 120, 110, 105 };
	QVector<int> walkDistances = { 200, 220, 210, 215 };
	QVector<int> bikeRideDistances = { 300, 320, 310, 305 };

	QVector<int> runElevation = { 150, 1300, 560, 2000 };
	QVector<int> walkElevation = { 150, 300, 100, 25 };
	QVector<int> bikeRideElevation = { 120, 200, 60, 70 };

	// Create QBarSet for each activity type
	QBarSet* runSet = new QBarSet("Run");
	QBarSet* runSetElev = new QBarSet("Run Elevation");
	QBarSet* walkSet = new QBarSet("Walk");

	QBarSet* walkSetElev = new QBarSet("Walk Elevation");
	QBarSet* bikeRideSet = new QBarSet("Bike Ride");
	QBarSet* bikeRideSetElev = new QBarSet("Bike Ride Elevation");

	// Add data to each QBarSet using a loop
	for (int distance : runDistances)
		runSet->append(distance);
	for (int elev : runElevation)
		runSetElev->append(elev);

	for (int distance : walkDistances)
		walkSet->append(distance);
	for (int elev : walkElevation)
		walkSetElev->append(elev);

	for (int distance : bikeRideDistances)
		bikeRideSet->append(distance);
	for (int elev : bikeRideElevation)
		bikeRideSetElev->append(elev);

	// Create a QBarSeries and add the QBarSets to it
	QStackedBarSeries* series = new QStackedBarSeries();
	series->append(runSet);
	series->append(walkSet);
	series->append(bikeRideSet);

	QBarSeries* series_elev = new QBarSeries();
	series_elev->append(runSetElev);
	//series_elev->append(walkSetElev);
	//series_elev->append(bikeRideSetElev);

	// Create a QChart and add the QBarSeries to it
	_chart = new QChart();
	_chart->addSeries(series);
	_chart->addSeries(series_elev);
	_chart->setTitle("Distance by Activity Type (2020-2023)");

	// Create a QBarCategoryAxis for the X axis and set the categories to the years
	QStringList categories = { "2020", "2021", "2022", "2023" };
	QBarCategoryAxis* axisX = new QBarCategoryAxis();
	axisX->append(categories);

	// Set the horizontal axis of the chart to the QBarCategoryAxis
	_chart->addAxis(axisX, Qt::AlignBottom);
	series->attachAxis(axisX);
	series_elev->attachAxis(axisX);

	// Vertical axis
	QValueAxis* axisY_dist = new QValueAxis();
	axisY_dist->setTitleText("Distance");
	_chart->addAxis(axisY_dist, Qt::AlignLeft);
	series->attachAxis(axisY_dist);

	QValueAxis* axisY_elev = new QValueAxis();
	axisY_elev->setTitleText("Elevation");
	_chart->addAxis(axisY_elev, Qt::AlignLeft);
	series_elev->attachAxis(axisY_elev);

	setChart(_chart);
	_chart->legend()->setVisible(true);
	_chart->legend()->setAlignment(Qt::AlignBottom);
	_chart->layout()->setContentsMargins(0, 0, 0, 0);

	for (QBarSet* barSet : series->barSets())
		barSet->setSelectedColor(barSet->brush().color().darker());
	for (QBarSet* barSet : series_elev->barSets())
		barSet->setSelectedColor(barSet->brush().color().darker());

	_chart->setAnimationOptions(QChart::SeriesAnimations);
	_chart->setTheme(QChart::ChartThemeBlueIcy);

	QObject::connect(series, &QAbstractBarSeries::hovered, series, [&](bool hover_enter, int index, QBarSet* set)
		{
			if (hover_enter)
				set->selectBar(index);
			else
				set->deselectBar(index);
		});

	QObject::connect(series_elev, &QAbstractBarSeries::hovered, series_elev, [&](bool hover_enter, int index, QBarSet* set)
		{
			if (hover_enter)
				set->selectBar(index);
			else
				set->deselectBar(index);
		});
}

void ActivityCollectionChart::updateChart(const ActivityOverviewModel& model)
{
	// Every QBarSeries/QStackedBarSeries represents one attribute
	// Stacked -> use one QBarSet for each attribute and each ActivityType
	
	// Not stacked -> sum up attribute values for all ActivityType-s and use one QBarSet for each attribute
	
	// If grouped by day -> always stacked -> click opens activity
	
	for (auto attribute : model.getAttributes())
	{
		model.getStacked() ? addStackedBarSeries(attribute, model) : addSummedBarSeries(attribute, model);
	}
}

void ActivityCollectionChart::mouseMoveEvent(QMouseEvent* event)
{
	QPointF point = mapToScene(event->pos());


	//qInfo() << "MAPPED POINT: " << point;
	//qInfo() << "POINT: " << event->pos();


	QChartView::mouseMoveEvent(event);
}

void ActivityCollectionChart::addSummedBarSeries(
	Providers::ActivitySummary::ESummableAttribute attribute, const ActivityOverviewModel& model)
{
	// Create bar sets
}

/*
* One BarSeries represents one attribute (e.g. Distance/ElevationGain)
* Stacked: the BarSets of each activity type will be displayed on top of each other as different bars
*/
void ActivityCollectionChart::addStackedBarSeries(
	Providers::ActivitySummary::ESummableAttribute attribute, const ActivityOverviewModel& model)
{
	// TODO create categories (years/months)




	QVector<float> values;
	for (const auto& act : model.getFilteredActivities())
	{
		values.push_back(act.getSummableAttribute(attribute));
	}

	QBarSet* set = new QBarSet("");

}

}