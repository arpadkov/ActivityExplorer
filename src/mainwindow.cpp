#include "mainwindow.h"
#include <Map/mapviewwindow.h>
#include <DataProvider/StravaClient/stravaclient.h>

#include "./ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qInfo() << "CONSTRUCTOR";

    QObject::connect(ui->_map_button, &QPushButton::clicked, this, &MainWindow::openMap);

    auto client = new StravaClient::StravaClient();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openMap()
{
    auto map_window = new MapViewWindow(this);
    map_window->show();
}
