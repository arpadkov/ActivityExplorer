#include "StravaCredentials.h"

#include "StravaClient.h"

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

namespace StravaClient
{

namespace
{
QString getStravaClientLocation()
{
	return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QDir::separator() + STRAVA_CLIENT_FOLDER + QDir::separator() + USER_DATA_FILE;
}
}

StravaCredential::StravaCredential(QString client_id_, QString client_secret_, QString refresh_token_)
	: client_id(client_id_), client_secret(client_secret_), refresh_token(refresh_token_)
{
}

StravaCredential::StravaCredential() {};

StravaCredential::~StravaCredential() {};


void StravaCredential::readCredentials()
{
	QFile file(getStravaClientLocation());
	if (!file.open(QIODevice::ReadOnly))
		return;

	qInfo() << "FILENAME: " << getStravaClientLocation();

	auto bytes = file.readAll();
	file.close();

	QJsonParseError error;
	QJsonDocument document = QJsonDocument::fromJson(bytes, &error);
	if (error.error != QJsonParseError::NoError)
	{
		qInfo() << "Could not open json: " << error.errorString();
		return;
	}

	if (!document.isObject())
	{
		qInfo() << "Json has wrong format";
		return;
	}

	auto json_obj = document.object();
	if (!json_obj.contains(CLIENT_ID) || !json_obj.contains(CLIENT_SECRET) || !json_obj.contains(REFRESH_TOKEN))
	{
		qInfo() << "User data is missing from json";
		return;
	}

	client_id = json_obj.value(CLIENT_ID).toString();
	client_secret = json_obj.value(CLIENT_SECRET).toString();
	refresh_token = json_obj.value(REFRESH_TOKEN).toString();
}

bool StravaCredential::saveCredentials()
{
	if (client_id.isEmpty() || client_secret.isEmpty() || refresh_token.isEmpty())
	{
		qInfo() << "Trying to write empty credentials";
		return;
	}

	QFile file(getStravaClientLocation());
	if (!file.open(QIODevice::ReadOnly))
		return;

	QJsonObject json_object;
	json_object["client_id"] = client_id;
	json_object["client_secret"] = client_secret;
	json_object["refresh_token"] = refresh_token;

	QJsonDocument jso_doc(json_object);

	file.write(jso_doc.toJson());
	file.close();
}



}