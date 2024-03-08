#include "LocalFilesProvider.h"

namespace LocalFilesProvider
{

LocalFilesProvider::LocalFilesProvider() : DataProviderSetup::DataProvider()
{
	qInfo("(LocalFilesProvider): Constructor");
}

void LocalFilesProvider::initilize()
{
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
