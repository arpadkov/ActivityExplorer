#include "DlgSetupDataProvider.h"

#include "DataProvider.h"

#include "./ui_setup_data_provider.h"


SetupDataProviderDialog::SetupDataProviderDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::SetupDataProviderDialog)
{
    ui->setupUi(this);

    ui->data_provider_combobox->addItems({ DataProviderSetup::STRAVA_CLIENT, DataProviderSetup::LOCAL_PROVIDER });

    QObject::connect(ui->data_provider_combobox, &QComboBox::currentIndexChanged, this, &SetupDataProviderDialog::onProviderChanged);

    onProviderChanged();
}

SetupDataProviderDialog::~SetupDataProviderDialog()
{
}

void SetupDataProviderDialog::addSetupWidget(QWidget* setup_w)
{
    _setup_w = setup_w;
    ui->verticalLayout->addWidget(_setup_w);
}

void SetupDataProviderDialog::onProviderChanged()
{
    auto provider = DataProviderSetup::getDataProvider(ui->data_provider_combobox->currentText());

    addSetupWidget(provider->createSetupWidget());
}

