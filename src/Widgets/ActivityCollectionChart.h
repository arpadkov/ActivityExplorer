#pragma once

#include <QChartView>
#include <QChart>
#include <QBarSet>

namespace Widgets
{

class ActivityCollectionChart : public QChartView
{
	Q_OBJECT

public:
	ActivityCollectionChart(QWidget* parent = nullptr);

protected:
	void mouseMoveEvent(QMouseEvent* event) override;

private:
	QChart* _chart;
	std::vector<QBarSet*> _sets;
};

}