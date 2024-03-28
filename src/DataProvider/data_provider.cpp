#include "DataProvider.h"
#include "DlgSetupDataProvider.h"

#include <StravaClient/StravaClient.h>
#include <LocalFilesProvider/LocalFilesProvider.h>
#include <ErrorDialog.h>

#include <QDir>
#include <QStandardPaths>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

namespace Providers
{

const QString DATA_PROVIDER_CONFIG_FILE = "data_provider_config.json";

QString getDataProviderLocation()
{
	return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
}

DataProvider::DataProvider()
{
}

bool DataProvider::initilizeProvider()
{
	try
	{
		return initilize();
	}
	catch (const ErrorDetail& err)
	{
		qInfo() << "(DataProvider) Could not initialize provider: " << err.getMessage();
		ErrorDialog::showFrom(err);
		return false;
	}

	catch (std::exception ex)
	{
		qInfo() << "(DataProvider) Could not initialize provider: " << ex.what();
		ErrorDialog::showFrom(ErrorDetail(ex));
		return false;
	}
}

/*
* Opens a dialog, where the type of the DataProvider can be selected, and configured
*/
void configureDataProvider()
{
	SetupDataProviderDialog* setup_dlg = new SetupDataProviderDialog();
	setup_dlg->show();
}

/*
* Returns an uninitilized specific DataProvider. 
*/
std::shared_ptr<DataProvider> getDataProvider(QString type)
{
	if (type == STRAVA_CLIENT)
		return std::make_shared<StravaClient::StravaClient>();

	if (type == LOCAL_PROVIDER)
		return std::make_shared<LocalFilesProvider::LocalFilesProvider>();

	qInfo() << "(DataProvider) Provider of type does not exist: " << type;
	return nullptr;
}

DataProviderConfiguration::DataProviderConfiguration()
{
}

DataProviderConfiguration::DataProviderConfiguration(const QString& configured_provider_) : _configured_provider(configured_provider_)
{
}

DataProviderConfiguration::~DataProviderConfiguration()
{
}

bool DataProviderConfiguration::writeConfig()
{
	if (_configured_provider.isEmpty())
	{
		qInfo() << "(DataProviderConfiguration) Trying to write empty config";
		return false;
	}

	QFile file(getDataProviderLocation() + QDir::separator() + DATA_PROVIDER_CONFIG_FILE);
	if (!file.open(QIODevice::WriteOnly))
		return false;

	QJsonObject json_object;
	json_object["configured_provider"] = _configured_provider;

	QJsonDocument json_doc(json_object);

	file.write(json_doc.toJson());
	file.close();

	qInfo() << "(DataProviderConfiguration) Provider config written to:  " << file.fileName();

	return true;
}

QString DataProviderConfiguration::getConfiguredProviderType() const
{
	return _configured_provider;
}



} // namespace Providers