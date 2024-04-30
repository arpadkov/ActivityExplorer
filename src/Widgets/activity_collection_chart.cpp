#include "ActivityCollectionChart.h"

#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QStackedBarSeries>
#include <QChart>
#include <QColor>
#include <QGraphicsLayout>

namespace Widgets
{

ActivityCollectionChart::ActivityCollectionChart(QWidget* parent) : QChartView(parent)
{

	QVector<int> runDistances = { 100, 120, 110, 105 };
	QVector<int> walkDistances = { 200, 220, 210, 215 };
	QVector<int> bikeRideDistances = { 300, 320, 310, 305 };

	// Create QBarSet for each activity type
	QBarSet* runSet = new QBarSet("Run");
	QBarSet* walkSet = new QBarSet("Walk");
	QBarSet* bikeRideSet = new QBarSet("Bike Ride");

	runSet->setBarSelected(0, true);

	// Add data to each QBarSet using a loop
	for (int distance : runDistances)
		runSet->append(distance);

	for (int distance : walkDistances)
		walkSet->append(distance);

	for (int distance : bikeRideDistances)
		bikeRideSet->append(distance);

	// Create a QBarSeries and add the QBarSets to it
	QStackedBarSeries* series = new QStackedBarSeries();
	series->append(runSet);
	series->append(walkSet);
	series->append(bikeRideSet);

	// Save sets
	_sets.push_back(runSet);
	_sets.push_back(walkSet);
	_sets.push_back(bikeRideSet);

	// Create a QChart and add the QBarSeries to it
	_chart = new QChart();
	_chart->addSeries(series);
	_chart->setTitle("Distance by Activity Type (2020-2023)");

	// Create a QBarCategoryAxis for the X axis and set the categories to the years
	QStringList categories = { "2020", "2021", "2022", "2023" };
	QBarCategoryAxis* axisX = new QBarCategoryAxis();
	axisX->append(categories);

	// Set the horizontal axis of the chart to the QBarCategoryAxis
	_chart->addAxis(axisX, Qt::AlignBottom);
	series->attachAxis(axisX);

	setChart(_chart);
	_chart->legend()->setVisible(true);
	_chart->legend()->setAlignment(Qt::AlignBottom);
	_chart->layout()->setContentsMargins(0, 0, 0, 0);

	const auto barSets = series->barSets();
	for (QBarSet* barSet : barSets)
		barSet->setSelectedColor(barSet->brush().color().darker());

	_chart->setAnimationOptions(QChart::AllAnimations);
	_chart->setTheme(QChart::ChartThemeBlueIcy);

	for (const auto& set : _sets)
	{
		qInfo() << "SET: " << set->label();
		qInfo() << "OTHER: " << set->count();
		//series->setP
	}

	QObject::connect(series, &QAbstractBarSeries::hovered, series, [&](bool hover_enter, int index, QBarSet* set)
		{
			//qInfo() << "HOVERED: " << index << " - " << status;

			if (hover_enter)
				set->selectBar(index);
			else
				set->deselectBar(index);

			//set->toggleSelection({ index });

		});
}

void ActivityCollectionChart::mouseMoveEvent(QMouseEvent* event)
{
	QPointF point = mapToScene(event->pos());


	//qInfo() << "MAPPED POINT: " << point;
	//qInfo() << "POINT: " << event->pos();


	QChartView::mouseMoveEvent(event);
}

}