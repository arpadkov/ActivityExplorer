#include "NetworkRequest.h"

#include <QNetworkRequest>
#include <QUrlQuery>

NetworkRequest::NetworkRequest(const QString& url) : _url(url)
{
}

void NetworkRequest::addQueryItem(const QString& key, const QString& value)
{
	_query_items.push_back({ key, value });
}

QNetworkRequest NetworkRequest::getQNetworkRequest() const
{
	QUrl auth_url = QUrl(_url);

	QUrlQuery query = QUrlQuery();
	for (const auto& [key, value] : _query_items)
		query.addQueryItem(key, value);

	auth_url.setQuery(query);

	return QNetworkRequest(auth_url);
}
