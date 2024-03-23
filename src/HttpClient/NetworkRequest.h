#pragma once

#include <QString>

// Forwards
class QNetworkRequest;

class NetworkRequest
{
public:
	NetworkRequest() = delete;
	NetworkRequest(const QString& url);

	void addQueryItem(const QString& key, const QString& value);

	QNetworkRequest getQNetworkRequest() const;

private:
	QString _url;
	std::vector<std::pair<QString, QString>> _query_items;
};