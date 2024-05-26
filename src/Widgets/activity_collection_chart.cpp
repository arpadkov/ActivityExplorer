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
	//updateChart();
	_chart = new QChart();
	_chart->legend()->setAlignment(Qt::AlignBottom);
	_chart->setAnimationOptions(QChart::SeriesAnimations);
	_chart->setTheme(QChart::ChartThemeBlueIcy);
	setChart(_chart);


	//QVector<int> runDistances = { 100, 120, 110, 105 };
	//QVector<int> walkDistances = { 200, 220, 210, 215 };
	//QVector<int> bikeRideDistances = { 300, 320, 310, 305 };
	//QVector<int> runElevation = { 150, 1300, 560, 2000 };
	//QVector<int> walkElevation = { 150, 300, 100, 25 };
	//QVector<int> bikeRideElevation = { 120, 200, 60, 70 };
	//// Create QBarSet for each activity type
	//QBarSet* runSet = new QBarSet("Run");
	//QBarSet* runSetElev = new QBarSet("Run Elevation");
	//QBarSet* walkSet = new QBarSet("Walk");
	//QBarSet* walkSetElev = new QBarSet("Walk Elevation");
	//QBarSet* bikeRideSet = new QBarSet("Bike Ride");
	//QBarSet* bikeRideSetElev = new QBarSet("Bike Ride Elevation");
	//// Add data to each QBarSet using a loop
	//for (int distance : runDistances)
	//	runSet->append(distance);
	//for (int elev : runElevation)
	//	runSetElev->append(elev);
	//for (int distance : walkDistances)
	//	walkSet->append(distance);
	//for (int elev : walkElevation)
	//	walkSetElev->append(elev);
	//for (int distance : bikeRideDistances)
	//	bikeRideSet->append(distance);
	//for (int elev : bikeRideElevation)
	//	bikeRideSetElev->append(elev);
	//// Create a QBarSeries and add the QBarSets to it
	//QStackedBarSeries* series = new QStackedBarSeries();
	//series->append(runSet);
	//series->append(walkSet);
	//series->append(bikeRideSet);
	//QBarSeries* series_elev = new QBarSeries();
	//series_elev->append(runSetElev);
	////series_elev->append(walkSetElev);
	////series_elev->append(bikeRideSetElev);
	//// Create a QChart and add the QBarSeries to it
	//_chart = new QChart();
	//_chart->addSeries(series);
	//_chart->addSeries(series_elev);
	//_chart->setTitle("Distance by Activity Type (2020-2023)");
	//// Create a QBarCategoryAxis for the X axis and set the categories to the years
	//QStringList categories = { "2020", "2021", "2022", "2023" };
	//QBarCategoryAxis* axisX = new QBarCategoryAxis();
	//axisX->append(categories);
	//// Set the horizontal axis of the chart to the QBarCategoryAxis
	//_chart->addAxis(axisX, Qt::AlignBottom);
	//series->attachAxis(axisX);
	//series_elev->attachAxis(axisX);
	//// Vertical axis
	//QValueAxis* axisY_dist = new QValueAxis();
	//axisY_dist->setTitleText("Distance");
	//_chart->addAxis(axisY_dist, Qt::AlignLeft);
	//series->attachAxis(axisY_dist);
	//QValueAxis* axisY_elev = new QValueAxis();
	//axisY_elev->setTitleText("Elevation");
	//_chart->addAxis(axisY_elev, Qt::AlignLeft);
	//series_elev->attachAxis(axisY_elev);
	//setChart(_chart);
	//_chart->legend()->setVisible(true);
	//_chart->legend()->setAlignment(Qt::AlignBottom);
	//_chart->layout()->setContentsMargins(0, 0, 0, 0);
	//for (QBarSet* barSet : series->barSets())
	//	barSet->setSelectedColor(barSet->brush().color().darker());
	//for (QBarSet* barSet : series_elev->barSets())
	//	barSet->setSelectedColor(barSet->brush().color().darker());
	//_chart->setAnimationOptions(QChart::SeriesAnimations);
	//_chart->setTheme(QChart::ChartThemeBlueIcy);
	//QObject::connect(series, &QAbstractBarSeries::hovered, series, [&](bool hover_enter, int index, QBarSet* set)
	//	{
	//		if (hover_enter)
	//			set->selectBar(index);
	//		else
	//			set->deselectBar(index);
	//	});
	//QObject::connect(series_elev, &QAbstractBarSeries::hovered, series_elev, [&](bool hover_enter, int index, QBarSet* set)
	//	{
	//		if (hover_enter)
	//			set->selectBar(index);
	//		else
	//			set->deselectBar(index);
	//	});
}

void ActivityCollectionChart::updateChart(const ActivityOverviewModel& model)
{
	// Create a QBarCategoryAxis for the X axis and set the categories
	const auto& categories = model.getCategories();
	QStringList categories_str;
	for (const auto& cat : categories)
		categories_str.push_back(cat.toString(ECategoryStringFormat::WithAddition));
	_axis_x = new QBarCategoryAxis();
	_axis_x->append(categories_str);
	_chart->addAxis(_axis_x, Qt::AlignBottom);

	// Every QBarSeries/QStackedBarSeries represents one attribute
	// Stacked -> use one QBarSet for each attribute and each ActivityType

	// Not stacked -> sum up attribute values for all ActivityType-s and use one QBarSet for each attribute

	// If grouped by day -> always stacked -> click opens activity

	for (auto attribute : model.getAttributes())
	{
		model.isStacked() ? addStackedBarSeries(attribute, model) : addSummedBarSeries(attribute, model);
	}
}

void ActivityCollectionChart::mouseMoveEvent(QMouseEvent* event)
{
	QPointF point = mapToScene(event->pos());


	//qInfo() << "MAPPED POINT: " << point;
	//qInfo() << "POINT: " << event->pos();


	QChartView::mouseMoveEvent(event);
}

/*
* One BarSeries represents one attribute (e.g. Distance/ElevationGain)
* Summed: There is only one BarSet for each attribute, the values for each activity type are summed up
* One BarSet represents values of one category (summed up for all types)
*/
void ActivityCollectionChart::addSummedBarSeries(
	Providers::ActivitySummary::ESummableAttribute attribute, const ActivityOverviewModel& model)
{
	// Initialize values vector with 0-s for all categories
	std::vector<float> values;
	values = std::vector<float>(model.getCategories().size(), 0);
	for (auto activity_type : model.getActivityTypes())
	{
		// Sum up the values from each activity type
		const auto& values_by_category = model.getValuesForAttributeByCategory(attribute, activity_type);		
		// To each category add the value for the type
		for (int i = 0; i < values_by_category.size(); i++)
			values[i] += values_by_category[i].second;
	}

	QString attribute_str = Providers::summableAttributeToString(attribute);
	QBarSet* attribute_set = new QBarSet(attribute_str);
	for (const auto& value : values)
		attribute_set->append(value);

	QBarSeries* series = new QBarSeries();
	series->append(attribute_set);

	_chart->addSeries(series);
	series->attachAxis(_axis_x);
	series->setLabelsVisible(true);
	series->setLabelsPosition(QAbstractBarSeries::LabelsInsideBase);
	series->setLabelsAngle(-90);

	// Create vertical axis and attach
	QValueAxis* axisY = new QValueAxis();
	axisY->setTitleText(attribute_str);
	_chart->addAxis(axisY, Qt::AlignLeft);
	series->attachAxis(axisY);
}

/*
* One BarSeries represents one attribute (e.g. Distance/ElevationGain)
* Stacked: the BarSets of each activity type will be displayed on top of each other as different bars
* One BarSet represents values of one category and of one type
*/
void ActivityCollectionChart::addStackedBarSeries(
	Providers::ActivitySummary::ESummableAttribute attribute, const ActivityOverviewModel& model)
{
	// Create QBarSet for each activity type
	std::vector<QBarSet*> bar_sets;
	for (auto activity_type : model.getActivityTypes())
	{
		QString type_str = Providers::activityTypeToString(activity_type);
		QBarSet* type_set = new QBarSet(type_str);

		// Append list of values (list by category) for the attribute
		for (const auto& [cat, value] : model.getValuesForAttributeByCategory(attribute, activity_type))
			type_set->append(value);

		bar_sets.push_back(type_set);
	}

	// Create the StackedBarSeries from the sets
	QStackedBarSeries* series = new QStackedBarSeries();
	for (auto set : bar_sets)
		series->append(set);

	_chart->addSeries(series);
	series->attachAxis(_axis_x);
	series->setLabelsVisible(true);
	series->setLabelsPosition(QAbstractBarSeries::LabelsInsideBase);
	series->setLabelsAngle(-90);


	// Create vertical axis and attach
	QValueAxis* axisY = new QValueAxis();
	QString attribute_str = Providers::summableAttributeToString(attribute);
	axisY->setTitleText(attribute_str);
	_chart->addAxis(axisY, Qt::AlignLeft);
	series->attachAxis(axisY);


}

}