#include "LocalFilesProvider.h"

#include <Activity.h>

namespace Providers::LocalFilesProvider
{

LocalFilesProvider::LocalFilesProvider() : DataProvider()
{
	qInfo("(LocalFilesProvider): Constructor");
}

bool LocalFilesProvider::initilize(const DataProviderInitializationHint& init_hint)
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
