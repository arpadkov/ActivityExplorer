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

QString getDataProviderLocation();

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

class DataProviderConfiguration
{
public:
	DataProviderConfiguration();
	DataProviderConfiguration(const QString& configured_provider_);
	~DataProviderConfiguration();

	bool writeConfig();
	QString getConfiguredProviderType() const;

private:
	QString _configured_provider;
};

void configureDataProvider();
std::shared_ptr<DataProvider> getDataProvider(QString type);


} // namespace DataProvider