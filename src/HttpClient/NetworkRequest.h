#pragma once

#include <QString>

// Forwards
class QNetworkRequest;

enum class NetworkRequestType
{
	UNKNOWN,
	POST,
	GET
};

class NetworkRequest
{
public:
	NetworkRequest() = delete;
	NetworkRequest(const QString& url, NetworkRequestType type_);

	void addQueryItem(const QString& key, const QString& value);

	QNetworkRequest getQNetworkRequest() const;

	NetworkRequestType type;

private:
	QString _url;
	std::vector<std::pair<QString, QString>> _query_items;
};