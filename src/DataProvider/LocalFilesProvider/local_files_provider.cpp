#include "LocalFilesProvider.h"

namespace LocalFilesProvider
{

LocalFilesProvider::LocalFilesProvider() : DataProviderSetup::DataProvider()
{
	qInfo("(LocalFilesProvider): Constructor");
}

bool LocalFilesProvider::initilize()
{
	return false;
}

QWidget* LocalFilesProvider::createSetupWidget()
{
	return nullptr;
}

QString LocalFilesProvider::getType()
{
	return DataProviderSetup::LOCAL_PROVIDER;
}

}
