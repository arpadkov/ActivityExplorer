#include "MainWindow.h"
#include <Map/mapviewwindow.h>
#include <DataProvider/DataProvider.h>
//#include <DataProvider/StravaClient/StravaClient.h>

#include "./ui_main_window.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QObject::connect(ui->test_button, &QPushButton::clicked, this, []()
    //    {
    //        auto client = new StravaClient::StravaClient();
    //        return;
    //    });

    QObject::connect(ui->act_setup_data_provider, &QAction::triggered, this, []()
        {
            DataProvider::setupDataProvider();
        });
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
