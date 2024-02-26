#pragma once

#include <DataProvider/DataProvider.h>
#include <HttpClient/HttpClient.h>

#include <QString>

// Forwards
class QNetworkReply;
class QWidget;

namespace StravaClient
{

const QString AUTH_URL = "https://www.strava.com/oauth/token";
const QString STRAVA_CLIENT_FOLDER = "StravaClient";
const QString USER_DATA_FILE = "user_data.json";

const QString CLIENT_ID = "client_id";
const QString CLIENT_SECRET = "client_secret";
const QString ACCESS_TOKEN = "access_token";
const QString REFRESH_TOKEN = "refresh_token";
const QString AUTH_CODE = "code";

const QString GRANT_TYPE = "grant_type";
const QString AUTH_CODE_TYPE = "authorization_code";

class StravaClient : public DataProviderSetup::DataProvider
{

public:
	StravaClient();

	bool initilize() override;
	QWidget* createSetupWidget() override;
	QString getType() override;

private:
	bool readUserData();
	bool getAccessToken();

	QString _client_id;			// Stored locally and entered manuall
	QString _client_secret;		// Stored locally and entered manuall
	QString _access_token;		// Stored only for the session
	QString _refresh_token;		// Stored locally and entered manuall
};

} // namespace StravaClient

