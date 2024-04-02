#pragma once

#include "NetworkReply.h"

#include <ErrorDetail.h>

#include <QObject>
#include <QNetworkAccessManager>
#include <QMutex>
#include <memory>

// Forwards
class NetworkRequest;


/*
* Simplified interface to handle Http requests, abstracts away QNetworkManager, QNetworkReply and QNetworkRequest.
* Singleton, to have only one QNetworkAccessManager object.
*/
class HttpClient : public QObject
{

Q_OBJECT

public:
	static std::shared_ptr<HttpClient> get();

	void postRequest(const NetworkRequest& request, const QByteArray& data);
	void getRequest(const NetworkRequest& request);

	std::shared_ptr<NetworkReply> waitForReply(const NetworkRequest& request, ErrorDetail& error, int timeout_ms = -1);
	std::shared_ptr<NetworkReply> waitForReply(const NetworkRequest& request, ErrorDetail& error, const QByteArray& data = {}, int timeout_ms = -1);

	~HttpClient();
	HttpClient(const HttpClient& cl) = delete;
	void operator=(const HttpClient& cl) = delete;

private:

	HttpClient();

	static std::shared_ptr<HttpClient> client_ptr;

	static QMutex _mutex;

	QNetworkAccessManager _manager;

private slots:
	void onReplyReceived(QNetworkReply* reply);

signals:
	void receivedReply(std::shared_ptr<NetworkReply> reply);
	void receivedError(ErrorDetail error);
};
