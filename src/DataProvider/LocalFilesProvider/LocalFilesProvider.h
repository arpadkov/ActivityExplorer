#pragma once

#include <DataProvider.h>

namespace Providers::LocalFilesProvider
{

class LocalFilesProvider : public DataProvider
{

public:
	LocalFilesProvider();

	bool initilize(const DataProviderInitializationHint& init_hint) override;
	DataProviderSetupWidget* createSetupWidget() override;
	QString getType() override;
};

} // namespace LocalFilesProvider