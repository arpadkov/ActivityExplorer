#pragma once

#include <QByteArray>

// Forwards
class QString;
class QNetworkReply;

/*
* Interface to handle network replies, responsible for parsing the data and returning a useable object.
* For now setup for json replies.
* Responsible for deleting the original reply.
*/
class NetworkReply
{
public:
	NetworkReply() = default;
	NetworkReply(const QByteArray& data);
	~NetworkReply();

	QString getValue(const QString& key) const;
	QString getRawData() const;

private:
	QByteArray _data;
	QNetworkReply* _raw_reply_ptr = nullptr;
};