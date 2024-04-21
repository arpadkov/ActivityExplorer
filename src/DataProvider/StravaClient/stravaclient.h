#pragma once

#include <DataProvider.h>

// Forwards
class NetworkReply;
class NetworkRequest;
class QWidget;
class ErrorDetail;

namespace Providers::StravaClient
{
class StravaCredential;
}

namespace Providers::StravaClient
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

QString getStravaClientLocation();

class StravaClient : public DataProvider
{

public:
	StravaClient();
	~StravaClient();

	bool initilize(const DataProviderInitializationHint& init_hint) override;
	DataProviderSetupWidget* createSetupWidget() override;
	QString getType() override;

	std::vector<ActivitySummary> getAllActivities(ErrorDetail& error) override;

private:
	bool setAccessToken(const StravaCredential& credentials);
	void authorizeRequest(NetworkRequest& request) const;
	bool refreshActivitySummaryCache();
	std::shared_ptr<NetworkReply> getActivitySummariesFromStrava(int page, int act_per_page, ErrorDetail& error);
	int getEstimatedActivityCount();
	bool setLoggedInAthlete();

	QString _access_token;		// Stored only for the session
	QString _athlete_id;
	std::vector<ActivitySummary> _act_summaries;
};

} // namespace Providers::StravaClient

