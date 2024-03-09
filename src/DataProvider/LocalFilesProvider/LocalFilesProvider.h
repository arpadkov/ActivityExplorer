#pragma once

#include <DataProvider/DataProvider.h>

#include <QObject>
#include <QString>

namespace Providers::LocalFilesProvider
{

class LocalFilesProvider : public DataProvider
{

public:
	LocalFilesProvider();

	bool initilize() override;
	DataProviderSetupWidget* createSetupWidget() override;
	QString getType() override;
};

} // namespace LocalFilesProvider