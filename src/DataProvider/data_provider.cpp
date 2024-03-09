#include "DlgSetupDataProvider.h"
#include "DataProvider.h"

#include <DataProvider/StravaClient/StravaClient.h>
#include <DataProvider/LocalFilesProvider/LocalFilesProvider.h>


namespace Providers
{

DataProvider::DataProvider()
{
}

bool DataProvider::initilizeProvider()
{
	try
	{
		return initilize();
	}
	catch (std::exception ex)
	{
		qInfo() << "(DataProvider) Could not initialize provider: " << ex.what();
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


} // namespace Providers