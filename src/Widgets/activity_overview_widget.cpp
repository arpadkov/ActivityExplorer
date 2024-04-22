#include "ActivityOverviewWidget.h"

#include "ui_activity_overview_widget.h"

namespace Widgets
{

ActivityOverviewWidget::ActivityOverviewWidget(QWidget* parent) : QWidget(parent), ui(new Ui::ActivityOverviewWidget)
{
	ui->setupUi(this);
}

}