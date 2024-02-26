#pragma once

#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
    class SetupDataProviderDialog;
}
QT_END_NAMESPACE

class SetupDataProviderDialog : public QDialog
{
    Q_OBJECT

public:
    SetupDataProviderDialog(QWidget* parent = nullptr);
    ~SetupDataProviderDialog();

    void addSetupWidget(QWidget* setup_w);

private slots:
    void onProviderChanged();

private:
    Ui::SetupDataProviderDialog* ui;

    QWidget* _setup_w;

};