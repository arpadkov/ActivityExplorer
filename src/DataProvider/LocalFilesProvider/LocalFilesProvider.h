#pragma once

#include <DataProvider/DataProvider.h>

#include <QObject>
#include <QString>

namespace LocalFilesProvider
{

class LocalFilesProvider : public DataProviderSetup::DataProvider
{

public:
	LocalFilesProvider();

	void initilize() override;
	QWidget* createSetupWidget() override;
	QString getType() override;
};

} // namespace LocalFilesProvider