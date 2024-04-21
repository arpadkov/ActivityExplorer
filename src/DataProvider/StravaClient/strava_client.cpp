#include "StravaClient.h"
#include "StravaActivityConverter.h"
#include "StravaSetupWidget.h"
#include "StravaCredentials.h"

#include <Activity.h>
#include <HttpClient.h>
#include <NetworkRequest.h>

#include <QDir>
#include <QJsonDocument>


namespace Providers::StravaClient
{
const QString ACTIVITY_CACHE_FOLDER_NAME = "ActivityCache";

const QString ACTIVITIES_URL =
"https://www.strava.com/api/v3/athlete/activities";
const QString LOGGED_IN_ATHLETE_URL = "https://www.strava.com/api/v3/athlete";
QString ACTIVITY_STATS_URL = "https://www.strava.com/api/v3/athletes/%1/stats";

QString getStravaClientLocation()
{
	return Providers::getDataProviderLocation() + QDir::separator() + STRAVA_CLIENT_FOLDER;
}

namespace
{
QDir getStravaCacheLocation()
{
	const QString& file_location = getStravaClientLocation() + QDir::separator() + ACTIVITY_CACHE_FOLDER_NAME;
	return QDir(file_location);
}

bool deleteStravaCache()
{
	auto dir = getStravaCacheLocation();

	if (!dir.exists())
	{
		qDebug() << "Strava cache directory does not exist. " << dir.absolutePath();
		return false;
	}

	// Remove all files within the directory
	QStringList files = dir.entryList(QDir::Files);
	for (const QString& file : files)
	{
		if (!dir.remove(file))
		{
			qDebug() << "Failed to remove file:" << file;
			return false;
		}
	}

	return true;
}

bool writeActivityToFileFromReply(const NetworkReply& reply)
{
	const QJsonDocument& data = reply.getData();

	// Check if folder exists, create if not
	auto dir = getStravaCacheLocation();
	if (!dir.exists())
	{
		if (!dir.mkdir("."))
		{
			qDebug() << "Failed to create Strava Activity cache folder";
			return false;
		}
	}

	auto act_id = reply.getIntValue("id");
	auto act_date = reply.getStringValue("start_date");

	if (!act_id || !act_date)
	{
		qDebug() << "Could not get activity id and date";
		return false;
	}

	auto act_date_str = QDateTime::fromString(*act_date, Qt::ISODate).toString("yyyy-MM-dd");
	QString filename = QString("activity_%1_%2").arg(act_date_str, QString::number(*act_id));

	QString full_filename = dir.absolutePath() + QDir::separator() + filename + ".json";
	QFile file(full_filename);

	if (file.exists())
	{
		// qDebug() << "Skipping write file, because it exists already: " << full_filename;
		return true;
	}

	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		qDebug() << "Could not create file: " << full_filename;
		return false;
	}

	QTextStream out(&file);
	out << data.toJson();
	file.close();
	qDebug() << "Created file: " << full_filename;

	return true;
}
}

StravaClient::StravaClient() : DataProvider()
{
	qInfo("(StravaClient): Constructor");
}

StravaClient::~StravaClient()
{
	qInfo("(StravaClient): Destructor");
}

/*
* Read credentials from file, and set refresh token
* If init_hin is provided, will not read the credentials, just use it from
* argument - used only for testing
* becuase it is from a different executeable and QStandardPath is different
* Can throw std::runtime_error
*/
bool StravaClient::initilize(const DataProviderInitializationHint& init_hint)
{
	const StravaCredential* credentials_hint =
		std::get_if<StravaCredential>(&init_hint);

	// Use credentials_hint if provided, otherwise read credentials
	StravaCredential credentials;
	if (credentials_hint)
		credentials = *credentials_hint;
	else if (!credentials.readCredentials())
		throw std::runtime_error("Could not read credentials");

	if (!setAccessToken(credentials))
		throw std::runtime_error("Could not set access token");

	return true;
}

DataProviderSetupWidget* StravaClient::createSetupWidget()
{
	return new StravaSetupWidget();
}

QString StravaClient::getType()
{
	return STRAVA_CLIENT;
}

/*
*	Gets al the activity summaries. Checks for the latest 100 activities, takes about 2 seconds
*/
std::vector<ActivitySummary> StravaClient::getAllActivities(ErrorDetail& error)
{
	setLoggedInAthlete();

	auto dir = getStravaCacheLocation();
	if (!dir.exists() || dir.entryList(QDir::Files).isEmpty())
	{
		// Refresh whole cache if cache directory does not exist, or is empty
		refreshActivitySummaryCache();
	}
	else
	{
		// Get and write the last 100 activities
		auto latest_acts = getActivitySummariesFromStrava(1, 100, error);
		if (!latest_acts)
		{
			qWarning() << "(StravaClient): Got error reply when trying to get activities: " << error.getMessage();
			return {};
		}
	
		for (const auto& act_reply : latest_acts->getArray())
		{
			writeActivityToFileFromReply(act_reply);
		}
	}

	// Read all activities from cache
	for (const auto& file_str : dir.entryList(QDir::Files))
	{
		QFile file(dir.filePath(file_str));
		if (!file.open(QIODevice::ReadOnly))
		{
			qWarning() << "(StravaClient): Could not open file: " << file_str;
			continue;
		}

		// Create a NetworkReply to parse the json data
		auto reply_from_file = NetworkReply(file.readAll());
		auto act_summary = activitySummaryFromStravaReply(reply_from_file, error);
		if (!act_summary)
		{
			qWarning() << "(StravaClient): Could not create ActivitySummary from file: " << file_str;
			continue;
		}

		file.close();
		_act_summaries.push_back(*act_summary);
	}


	return _act_summaries;
}

bool StravaClient::setAccessToken(const StravaCredential& credentials)
{
	auto client = HttpClient::get();

	NetworkRequest request(AUTH_URL, NetworkRequestType::POST);
	request.addQueryItem(CLIENT_ID, credentials.client_id);
	request.addQueryItem(CLIENT_SECRET, credentials.client_secret);
	request.addQueryItem(REFRESH_TOKEN, credentials.refresh_token);
	request.addQueryItem(GRANT_TYPE, REFRESH_TOKEN);

	ErrorDetail error;
	auto reply = client->waitForReply(request, error, 15 * 1000);
	if (!reply)
		throw error;

	const auto& access_token = reply->getStringValue(ACCESS_TOKEN);
	if (!access_token)
		throw std::runtime_error(
			QString("Reply did not contain access token").toStdString());

	_access_token = *access_token;
	qInfo() << "ACCESS TOKEN: " << _access_token;
	return true;
}

void StravaClient::authorizeRequest(NetworkRequest& request) const
{
	request.addHeaderItem("Authorization", QString("Bearer %1").arg(_access_token));
}

bool StravaClient::refreshActivitySummaryCache()
{
	qInfo() << "(StravaClient) Refreshing activity cache";

	auto client = HttpClient::get();
	if (!client)
		return false;

	deleteStravaCache();

	int estimated_act_count = getEstimatedActivityCount();
	if (estimated_act_count > 15000)
		qWarning() << "(StravaClient) Throttleing API requests to not exceed limits";

	ErrorDetail error;

	int requested_per_page = 200;
	int got_per_page = requested_per_page;
	int page = 1;
	while (got_per_page == requested_per_page)
	{
		auto reply = getActivitySummariesFromStrava(page, requested_per_page, error);
		if (!reply)
		{
			qWarning() << "(StravaClient): Got error reply when trying to get activities: " << error.getMessage();
			return false;
		}

		const auto& acts = reply->getArray();
		for (const auto& act_reply : acts)
		{
			if (!writeActivityToFileFromReply(act_reply))
			{
				qDebug() << "(StravaClient): Could not write activitiy: " << act_reply.getRawData();
			}
		}

		page++;
		got_per_page = acts.size();
	}

	return true;
}

/*
* Gets the requested number of activities for the page.
* Writes them to the StravaClient location as json and saves it in _act_summaries
*/
std::shared_ptr<NetworkReply> StravaClient::getActivitySummariesFromStrava(int page, int act_per_page, ErrorDetail& error)
{
	auto client = HttpClient::get();
	if (!client)
		return {};

	NetworkRequest request(ACTIVITIES_URL, NetworkRequestType::GET);
	request.addQueryItem("page", QString::number(page));
	request.addQueryItem("per_page", QString::number(act_per_page));
	authorizeRequest(request);

	return client->waitForReply(request, error, 15 * 1000);
}

int StravaClient::getEstimatedActivityCount()
{
	auto client = HttpClient::get();
	if (!client)
		return 0;

	NetworkRequest request(ACTIVITY_STATS_URL.arg(_athlete_id), NetworkRequestType::GET);
	authorizeRequest(request);

	ErrorDetail error;
	auto reply = client->waitForReply(request, error, 15 * 1000);
	if (!reply)
	{
		qWarning() << "(StravaClient): Could not get athlete stats";
		qDebug() << error.getMessage();
		return 0;
	}

	// Read activity count for all provided total stats and sum it up
	int activity_count = 0;
	const std::vector<QString> act_total_children = { "all_ride_totals", "all_run_totals", "all_swim_totals" };
	for (const auto& act_total_child_value : act_total_children)
	{
		if (auto act_total_child = reply->getChild(act_total_child_value))
		{
			if (auto count = act_total_child->getIntValue("count"))
				activity_count += *count;
		}
	}

	return activity_count;
}

bool StravaClient::setLoggedInAthlete()
{
	auto client = HttpClient::get();
	if (!client)
		return false;

	NetworkRequest request(LOGGED_IN_ATHLETE_URL, NetworkRequestType::GET);
	authorizeRequest(request);

	ErrorDetail error;
	auto reply = client->waitForReply(request, error, 15 * 1000);
	if (!reply)
	{
		qWarning() << "(StravaClient): Could not get logged in athlete";
		qDebug() << error.getMessage();
		return false;
	}

	auto athlete_id = reply->getIntValue("id");
	if (!athlete_id)
	{
		qWarning() << "(StravaClient): The reply did not contain the athlete id";
		qDebug() << reply->getRawData();
		return false;
	}

	_athlete_id = QString::number(*athlete_id);
	return true;
}


} // namespace Providers::StravaClient
