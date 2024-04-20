#include "NetworkReply.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkReply>


NetworkReply::NetworkReply(const QByteArray& data) : _data(QJsonDocument::fromJson(data))
{
}

NetworkReply::NetworkReply(const QString& data) : _data(QJsonDocument::fromJson(data.toUtf8()))
{
}

NetworkReply::NetworkReply(const QJsonDocument& data) : _data(data)
{
}

NetworkReply::~NetworkReply()
{
}

std::optional<QString> NetworkReply::getStringValue(const QString& key) const
{
	auto json = _data.object();
	if (json.contains(key))
		return json.value(key).toString();

	return {};
}

std::optional<qint64> NetworkReply::getIntValue(const QString& key) const
{
	auto json = _data.object();
	if (json.contains(key))
		return json.value(key).toInteger();

	return {};
}

std::optional<float> NetworkReply::getFloatValue(const QString& key) const
{
	auto json = _data.object();
	if (json.contains(key))
		return json.value(key).toDouble();

	return {};
}

std::optional<const NetworkReply> NetworkReply::getChild(const QString& key) const
{
	auto json = _data.object();
	if (json.contains(key))
		return NetworkReply(QJsonDocument(json.value(key).toObject()));

	return {};
}

std::vector<NetworkReply> NetworkReply::getArray() const
{
	std::vector<NetworkReply> out;

	if (!_data.isArray())
		return out;

	auto json_array = _data.array();
	for (const auto& json : json_array)
		out.push_back(NetworkReply(QJsonDocument(json.toObject())));

	return out;
}

QString NetworkReply::getRawData() const
{
	return _data.toJson();
}

QJsonDocument NetworkReply::getData() const
{
	return _data;
}
