#include "NetworkReply.h"

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>

//NetworkReply::NetworkReply()
//{
//}

NetworkReply::NetworkReply(const QByteArray& data) : _data(data)
{
	qInfo() << "NetworkReply CONSTRUCTOR";

}

NetworkReply::~NetworkReply()
{
	qInfo() << "NetworkReply DESTRUCTOR";
	//if (_raw_reply_ptr)
	//	_raw_reply_ptr->deleteLater();
}

QString NetworkReply::getValue(const QString& key) const
{
	QJsonObject json = QJsonDocument::fromJson(_data).object();
	if (json.contains(key))
		return json.value(key).toString();

	return {};
}

QString NetworkReply::getRawData() const
{
	return QString(_data);
}
