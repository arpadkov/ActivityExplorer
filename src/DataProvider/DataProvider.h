#pragma once

#include "Activity.h"
#include <StravaClient/StravaCredentials.h>

#include <QObject>
#include <QString>

// Forwards
class ErrorDetail;

namespace Providers
{
class DataProviderSetupWidget;
struct ActivitySummary;
}

namespace Providers
{
const QString STRAVA_CLIENT = "strava_client";
const QString LOCAL_PROVIDER = "local_provider";

QString getDataProviderLocation();

using DataProviderInitializationHint = std::variant<std::monostate, StravaClient::StravaCredential>;

class DataProvider : public QObject
{
Q_OBJECT

public:
	DataProvider();

	bool initilizeProvider();
	virtual std::vector<ActivitySummary> getActivitySummaries() final;

	virtual bool initilize(const DataProviderInitializationHint& init_hint = {}) = 0;
	virtual DataProviderSetupWidget* createSetupWidget() = 0;
	virtual QString getType() = 0;

Q_SIGNALS:
	void activitySummariesChanged();

protected:
	std::vector<ActivitySummary> _act_summaries;
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