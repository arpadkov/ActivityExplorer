#pragma once

#include <QtWidgets/QDialog>

// Forwards
namespace Ui
{
class SetupDataProviderDialog;
}

namespace Providers
{
class DataProviderSetupWidget;
}

namespace Providers
{

class SetupDataProviderDialog : public QDialog
{
    Q_OBJECT

public:
    SetupDataProviderDialog(QWidget* parent = nullptr);
    ~SetupDataProviderDialog();

    void addSetupWidget(DataProviderSetupWidget* setup_w);

private slots:
    void onProviderChanged();
    void accept();

private:
    Ui::SetupDataProviderDialog* ui;

    DataProviderSetupWidget* _setup_w;
};


class DataProviderSetupWidget : public QWidget
{
    Q_OBJECT

public:
    DataProviderSetupWidget(QWidget* parent = nullptr) {};
    ~DataProviderSetupWidget() {};

public Q_SLOTS:
    virtual void onAccepted() = 0;
};

}