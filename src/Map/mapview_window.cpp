#include <QQuickView>

#include "MapviewWindow.h"
#include "ui_mapview_window.h"

MapViewWindow::MapViewWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MapViewWindow)
{
    ui->setupUi(this);

    QQuickView* map_view = new QQuickView();
    QWidget* container = QWidget::createWindowContainer(map_view, this);

    map_view->setSource(QUrl("QmlForms/Map/MapView.qml"));
    ui->_vertical_layout->addWidget(container);
}

MapViewWindow::~MapViewWindow()
{
    delete ui;
}
