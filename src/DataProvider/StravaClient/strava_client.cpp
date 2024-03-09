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


namespace Providers::StravaClient
{

StravaClient::StravaClient() : DataProvider()
{
	qInfo("(StravaClient): Constructor");
}

/* Read credentials from file, and set refresh token
  Can throw std::runtume_error */
bool StravaClient::initilize()
{
	auto credentials = StravaCredential();
	if (!credentials.readCredentials())
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

bool StravaClient::setAccessToken(const StravaCredential& credentials)
{
	QNetworkAccessManager* manager = new QNetworkAccessManager();

	// TODO handle network rerplies with signal, and do not wait for them in main thread
	QObject::connect(manager, &QNetworkAccessManager::finished, this, [this](QNetworkReply* reply)
		{
			if (reply->error() != QNetworkReply::NoError)
			{
				qInfo() << "GOT REPLY WITH ERROR: " << reply->errorString();
				throw std::runtime_error(QString("Network reply error: %1").arg(reply->errorString()).toStdString());
			}

			QJsonObject json = QJsonDocument::fromJson(reply->readAll()).object();
			if (!json.contains(ACCESS_TOKEN))
				throw std::runtime_error(QString("Reply did not contain access token").toStdString());

			_access_token = json.value(ACCESS_TOKEN).toString();
			qInfo() << "ACCESS TOKEN: " << _access_token;
		});

	QUrl auth_url = QUrl(AUTH_URL);
	QUrlQuery query = QUrlQuery();
	query.addQueryItem(CLIENT_ID, credentials.client_id);
	query.addQueryItem(CLIENT_SECRET, credentials.client_secret);
	query.addQueryItem(REFRESH_TOKEN, credentials.refresh_token);
	query.addQueryItem(GRANT_TYPE, REFRESH_TOKEN);
	auth_url.setQuery(query);

	QNetworkRequest request = QNetworkRequest(auth_url);

	auto reply = manager->post(request, QByteArray());

	reply->deleteLater();


	return true;
}


} // namespace Providers::StravaClient
