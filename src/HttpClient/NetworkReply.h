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
	std::optional<NetworkReply> getChild(const QString& key) const;
	QString getRawData() const;

private:
	QJsonDocument _data;
};