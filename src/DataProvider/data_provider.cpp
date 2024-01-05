#include "DlgSetupDataProvider.h"
#include "DataProvider.h"


namespace DataProvider
{



DataProvider::DataProvider()
{
}

void setupDataProvider()
{
	SetupDataProviderDialog* setup_dlg = new SetupDataProviderDialog();
	setup_dlg->show();
}


} // namespace DataProvider