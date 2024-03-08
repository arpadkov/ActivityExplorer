#include "DlgSetupDataProvider.h"
#include "DataProvider.h"

#include <DataProvider/StravaClient/StravaClient.h>
#include <DataProvider/LocalFilesProvider/LocalFilesProvider.h>


namespace DataProviderSetup
{

DataProvider::DataProvider()
{
}

/*
* Opens a dialog, where the type of the DataProvider can be selected, and configured
*/
void configureDataProvider()
{
	SetupDataProviderDialog* setup_dlg = new SetupDataProviderDialog();
	setup_dlg->show();

	//auto client = StravaClient::StravaClient();
	//auto setup_w = client.createSetupWidget();

	//setup_dlg->addSetupWidget(setup_w);
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


} // namespace DataProvider