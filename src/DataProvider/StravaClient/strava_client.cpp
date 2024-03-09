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

void StravaClient::initilize()
{
	auto credentials = StravaCredential();
	credentials.readCredentials(); // TODO: save as class member
}

DataProviderSetupWidget* StravaClient::createSetupWidget()
{
	return new StravaSetupWidget();
}

QString StravaClient::getType()
{
	return STRAVA_CLIENT;
}

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


} // namespace Providers::StravaClient
