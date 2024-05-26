#pragma once

#include <Activity.h>

#include <QChartView>
#include <QChart>
#include <QBarSet>

// Forwards
namespace Widgets
{
class ActivityOverviewModel;
}

class QBarCategoryAxis;

namespace Widgets
{

class ActivityCollectionChart : public QChartView
{
	Q_OBJECT

public:
	ActivityCollectionChart(QWidget* parent = nullptr);

	void updateChart(const ActivityOverviewModel& model);
protected:
	void mouseMoveEvent(QMouseEvent* event) override;

private:
	void addSummedBarSeries(
		Providers::ActivitySummary::ESummableAttribute attribute, const ActivityOverviewModel& model);
	void addStackedBarSeries(
		Providers::ActivitySummary::ESummableAttribute attribute, const ActivityOverviewModel& model);

	QChart* _chart;
	std::vector<QBarSet*> _sets;
	QBarCategoryAxis* _axis_x;
};

}