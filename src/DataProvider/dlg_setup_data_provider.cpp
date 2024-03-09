#include "DlgSetupDataProvider.h"

#include "DataProvider.h"

#include "ui_setup_data_provider.h"

namespace Providers
{

SetupDataProviderDialog::SetupDataProviderDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::SetupDataProviderDialog)
{
    ui->setupUi(this);

    ui->data_provider_combobox->addItems({ Providers::STRAVA_CLIENT, Providers::LOCAL_PROVIDER });

    QObject::connect(ui->data_provider_combobox, &QComboBox::currentIndexChanged, this, &SetupDataProviderDialog::onProviderChanged);

    onProviderChanged();
}

SetupDataProviderDialog::~SetupDataProviderDialog()
{
}

void SetupDataProviderDialog::addSetupWidget(DataProviderSetupWidget* setup_w)
{
    _setup_w = setup_w;
    ui->verticalLayout->addWidget(_setup_w);
}

void SetupDataProviderDialog::accept()
{
    qInfo() << "ACCEPTED";
    QDialog::accept();
}

void SetupDataProviderDialog::onProviderChanged()
{
    auto provider = Providers::getDataProvider(ui->data_provider_combobox->currentText());

    addSetupWidget(provider->createSetupWidget());
}

}