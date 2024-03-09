#include "DlgSetupDataProvider.h"

#include "DataProvider.h"

#include "ui_setup_data_provider.h"

namespace Providers
{

namespace
{
int dataProviderTypeToIndex(const QString& provider_type)
{
    if (provider_type == Providers::STRAVA_CLIENT)
        return 0;
    else if (provider_type == Providers::LOCAL_PROVIDER)
        return 1;
}
}

SetupDataProviderDialog::SetupDataProviderDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::SetupDataProviderDialog)
{
    ui->setupUi(this);

    ui->data_provider_combobox->addItems({ Providers::STRAVA_CLIENT, Providers::LOCAL_PROVIDER });

    QObject::connect(ui->data_provider_combobox, &QComboBox::currentIndexChanged, this, &SetupDataProviderDialog::onProviderChanged);

    DataProviderConfiguration config;    
    const QString& provider_type = config.getConfiguredProviderType();
    ui->data_provider_combobox->setCurrentIndex(provider_type.isEmpty() ? 0 : dataProviderTypeToIndex(provider_type));
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

void SetupDataProviderDialog::cleanSetupWidget()
{
    if (_setup_w)
    {
        // TODO this does not remove the widget
        ui->verticalLayout->removeWidget(_setup_w);
    }
}

void SetupDataProviderDialog::accept()
{
    qInfo() << "ACCEPTED";
    if (!_setup_w)
    {
        QDialog::accept();
        return;
    }

    _setup_w->onAccepted();

    if (_setup_w->isConfigured())
    {
        DataProviderConfiguration config(ui->data_provider_combobox->currentText());
        config.writeConfig();
    }

    QDialog::accept();
}

void SetupDataProviderDialog::onProviderChanged()
{
    cleanSetupWidget();

    auto provider = Providers::getDataProvider(ui->data_provider_combobox->currentText());

    addSetupWidget(provider->createSetupWidget());
}

}