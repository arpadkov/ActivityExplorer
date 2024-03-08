#pragma once

#include <QObject>
#include <QString>

namespace DataProviderSetup
{
const QString STRAVA_CLIENT = "strava_client";
const QString LOCAL_PROVIDER = "local_provider";

class DataProvider : public QObject
{
Q_OBJECT

public:
	DataProvider();

	/* TODO: call this from DataProvider() constructor and allow+handle exceptions in initialize() */
	virtual void initilize() = 0;
	virtual QWidget* createSetupWidget() = 0;
	virtual QString getType() = 0;
};

void configureDataProvider();
std::shared_ptr<DataProvider> getDataProvider(QString type);


} // namespace DataProvider