#pragma once

#include <ActivityOverviewModel.h>

#include <QWidget>

// Forwards
namespace Ui
{
class ActivityOverviewWidget;
}

namespace Widgets
{



class ActivityOverviewWidget : public QWidget
{
	Q_OBJECT

public:
	ActivityOverviewWidget(QWidget* parent = nullptr);

private:
	Ui::ActivityOverviewWidget* ui;
	ActivityOverviewModel _overview_model;
};

}