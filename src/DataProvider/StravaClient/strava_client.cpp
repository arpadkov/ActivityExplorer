#include "StravaClient.h"
#include "StravaSetupWidget.h"
#include "StravaCredentials.h"

#include <QByteArray>
//#include <QDir>
//#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QNetworkReply>
//#include <QStandardPaths>
#include <QUrl>
#include <QUrlQuery>


namespace StravaClient
{

StravaClient::StravaClient() : DataProviderSetup::DataProvider()
{
	qInfo("(StravaClient): Constructor");

	initilize();

	getAccessToken();
}

void StravaClient::initilize()
{
	auto credentials = StravaCredential();
	credentials.readCredentials(); // TODO: save as class member
}

QWidget* StravaClient::createSetupWidget()
{
	return new StravaSetupWidget();
}

QString StravaClient::getType()
{
	return DataProviderSetup::STRAVA_CLIENT;
}

// TODO: DELETE
//bool StravaClient::readUserData()
//{
//	QFile file(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QDir::separator() + STRAVA_CLIENT_FOLDER + QDir::separator() + USER_DATA_FILE);
//	if (!file.open(QIODevice::ReadOnly))
//		return false;
//
//	qInfo() << "FILENAME: " << QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QDir::separator() + STRAVA_CLIENT_FOLDER + QDir::separator() + USER_DATA_FILE;
//
//	auto bytes = file.readAll();
//	file.close();
//
//	QJsonParseError error;
//	QJsonDocument document = QJsonDocument::fromJson(bytes, &error);
//	if (error.error != QJsonParseError::NoError)
//	{
//		qInfo() << "Could not open json: " << error.errorString();
//		return false;
//	}
//
//	if (!document.isObject())
//	{
//		qInfo() << "Json has wrong format";
//		return false;
//	}
//
//	auto json_obj = document.object();
//	if (!json_obj.contains(CLIENT_ID) || !json_obj.contains(CLIENT_SECRET) || !json_obj.contains(REFRESH_TOKEN))
//	{
//		qInfo() << "User data is missing from json";
//		return false;
//	}
//
//	_client_id = json_obj.value(CLIENT_ID).toString();
//	_client_secret = json_obj.value(CLIENT_SECRET).toString();
//	_refresh_token = json_obj.value(REFRESH_TOKEN).toString();
//
//	return true;
//}

bool StravaClient::getAccessToken()
{
	QNetworkAccessManager* manager = new QNetworkAccessManager();

	// TODO handle network rerplies with signal, and do not wait for them in main thread
	QObject::connect(manager, &QNetworkAccessManager::finished, this, [this](QNetworkReply* reply)
		{
			if (reply->error() != QNetworkReply::NoError)
			{
				qInfo() << "GOT REPLY WITH ERROR: " << reply->errorString();
				return;
			}

			QJsonObject json = QJsonDocument::fromJson(reply->readAll()).object();
			if (!json.contains(ACCESS_TOKEN))
				return;

			_access_token = json.value(ACCESS_TOKEN).toString();
			qInfo() << "ACCESS TOKEN: " << _access_token;
		});

	QUrl auth_url = QUrl(AUTH_URL);
	QUrlQuery query = QUrlQuery();
	query.addQueryItem(CLIENT_ID, _client_id);
	query.addQueryItem(CLIENT_SECRET, _client_secret);
	query.addQueryItem(REFRESH_TOKEN, _refresh_token);
	query.addQueryItem(GRANT_TYPE, REFRESH_TOKEN);
	auth_url.setQuery(query);

	QNetworkRequest request = QNetworkRequest(auth_url);

	auto reply = manager->post(request, QByteArray());

	reply->deleteLater();


	return true;
}


} // namespace StravaClient
