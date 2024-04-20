#include "NetworkRequest.h"

#include <QNetworkRequest>
#include <QUrlQuery>

NetworkRequest::NetworkRequest(const QString& url, NetworkRequestType type_) :
	_url(url), type(type_)
{
}

void NetworkRequest::addQueryItem(const QString& key, const QString& value)
{
	_query_items.push_back({ key, value });
}

void NetworkRequest::addHeaderItem(const QString& key, const QString& value)
{
	_header_items.push_back({ key, value });
}

QNetworkRequest NetworkRequest::getQNetworkRequest() const
{
	QUrl auth_url = QUrl(_url);

	QUrlQuery query = QUrlQuery();
	for (const auto& [key, value] : _query_items)
		query.addQueryItem(key, value);

	auth_url.setQuery(query);

	QNetworkRequest request(auth_url);

	for (const auto& [header_key, header_value] : _header_items)
	{
		request.setRawHeader(header_key.toLocal8Bit(), header_value.toLocal8Bit());
	}

	return request;
}
