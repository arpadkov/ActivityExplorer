#include "NetworkReply.h"

#include <QJsonObject>
#include <QNetworkReply>


NetworkReply::NetworkReply(const QByteArray& data)
{
	_data = QJsonDocument::fromJson(data);
}

NetworkReply::NetworkReply(const QString& data)
{
	_data = QJsonDocument::fromJson(data.toUtf8());
}

NetworkReply::NetworkReply(const QJsonDocument& data) : _data(data)
{
}

NetworkReply::~NetworkReply()
{
	qInfo() << "NetworkReply DESTRUCTOR";
}

std::optional<QString> NetworkReply::getStringValue(const QString& key) const
{
	auto json = _data.object();
	if (json.contains(key))
		return json.value(key).toString();

	return {};
}

std::optional<NetworkReply> NetworkReply::getChild(const QString& key) const
{
	auto json = _data.object();
	if (json.contains(key))
		return NetworkReply(QJsonDocument(json.value(key).toObject()));

	return {};
}

QString NetworkReply::getRawData() const
{
	return _data.toJson();
}
