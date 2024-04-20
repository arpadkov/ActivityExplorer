#pragma once

#include <QJsonDocument>

// Forwards
class QNetworkReply;

/*
* Interface to handle network replies, responsible for parsing the data and
* returning a useable object.
* For now setup for json replies.
* Responsible for deleting the original reply.
*/
class NetworkReply
{
public:
	NetworkReply() = default;
	NetworkReply(const QByteArray& data);
	NetworkReply(const QString& data);
	NetworkReply(const QJsonDocument& data);
	~NetworkReply();

	std::optional<QString> getStringValue(const QString& key) const;
	std::optional<qint64> getIntValue(const QString& key) const;
	std::optional<float> getFloatValue(const QString& key) const;
	std::optional<const NetworkReply> getChild(const QString& key) const;
	std::vector<NetworkReply> getArray() const;
	QString getRawData() const;
	QJsonDocument getData() const;

private:
	const QJsonDocument _data;
};