#pragma once

#include <QWidget>
#include <QPushButton>

namespace Widgets
{

class ActivityCollectionChartConfig : public QWidget
{
	Q_OBJECT

public:
	ActivityCollectionChartConfig(QWidget* parent);
	~ActivityCollectionChartConfig();

};

class CheckStackedButton : public QPushButton
{
	Q_OBJECT

public:
	CheckStackedButton(QWidget* parent);
	~CheckStackedButton();

protected:
	void mousePressEvent(QMouseEvent* event) override;
};

}