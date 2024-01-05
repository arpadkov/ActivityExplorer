#include "DlgSetupDataProvider.h"

#include "./ui_setup_data_provider.h"


SetupDataProviderDialog::SetupDataProviderDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::SetupDataProviderDialog)
{
    ui->setupUi(this);
}

SetupDataProviderDialog::~SetupDataProviderDialog()
{
}

