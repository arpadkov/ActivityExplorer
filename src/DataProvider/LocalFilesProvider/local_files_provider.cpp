#include "LocalFilesProvider.h"

namespace Providers::LocalFilesProvider
{

LocalFilesProvider::LocalFilesProvider() : DataProvider()
{
	qInfo("(LocalFilesProvider): Constructor");
}

void LocalFilesProvider::initilize()
{
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
