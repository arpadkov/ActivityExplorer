#include "MainWindow.h"
#include <Map/mapviewwindow.h>
#include <DataProvider/DataProvider.h>

#include "./ui_main_window.h"

#include <QDebug>

const QString PRODUCT_NAME = "ActivityExplorer";
const QString COMPANY_NAME = "ArpadKov";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->test_button, &QPushButton::clicked, this, &MainWindow::testFunction);

    QObject::connect(ui->act_setup_data_provider, &QAction::triggered, this, []()
        {
            DataProviderSetup::configureDataProvider();
        });


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::testFunction()
{
    //auto map_window = new MapViewWindow(this);
    //map_window->show();

    //auto client = DataProvider::initializeDataProvider(DataProvider::LOCAL_PROVIDER);
}
