#include "LocalFilesProvider.h"

namespace Providers::LocalFilesProvider
{

LocalFilesProvider::LocalFilesProvider() : DataProvider()
{
	qInfo("(LocalFilesProvider): Constructor");
}

bool LocalFilesProvider::initilize()
{
	return false;
}

DataProviderSetupWidget* LocalFilesProvider::createSetupWidget()
{
	return nullptr;
}

QString LocalFilesProvider::getType()
{
	return LOCAL_PROVIDER;
}

}
