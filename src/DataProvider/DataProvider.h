#pragma once

#include <QObject>
#include <QString>

// Forwards
namespace Providers
{
class DataProviderSetupWidget;
}

namespace Providers
{
const QString STRAVA_CLIENT = "strava_client";
const QString LOCAL_PROVIDER = "local_provider";

class DataProvider : public QObject
{
Q_OBJECT

public:
	DataProvider();

	bool initilizeProvider();

	/* TODO: call this from DataProvider() constructor and allow+handle exceptions in initialize() */
	virtual bool initilize() = 0;
	virtual DataProviderSetupWidget* createSetupWidget() = 0;
	virtual QString getType() = 0;
};

void configureDataProvider();
std::shared_ptr<DataProvider> getDataProvider(QString type);


} // namespace DataProvider