#pragma once

#include "StravaCredentials.h"

#include <DataProvider/DataProvider.h>

#include <QString>

// Forwards
class QNetworkReply;
class QWidget;

namespace Providers::StravaClient
{
class StravaCredential;
}

namespace Providers::StravaClient
{

const QString AUTH_URL = "https://www.strava.com/oauth/token";

const QString CLIENT_ID = "client_id";
const QString CLIENT_SECRET = "client_secret";
const QString ACCESS_TOKEN = "access_token";
const QString REFRESH_TOKEN = "refresh_token";
const QString AUTH_CODE = "code";

const QString GRANT_TYPE = "grant_type";
const QString AUTH_CODE_TYPE = "authorization_code";

class StravaClient : public DataProvider
{

public:
	StravaClient();

	bool initilize() override;
	DataProviderSetupWidget* createSetupWidget() override;
	QString getType() override;

private:
	bool setAccessToken(const StravaCredential& credentials);

	QString _access_token;		// Stored only for the session
};

} // namespace Providers::StravaClient

