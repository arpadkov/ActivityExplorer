#include "HttpClient.h"
#include "NetworkRequest.h"

#include <QEventLoop>
#include <QNetworkReply>
#include <QTimer>


std::shared_ptr<HttpClient> HttpClient::client_ptr = nullptr;
QMutex HttpClient::_mutex;

HttpClient::HttpClient()
{
	qInfo() << "(HttpClient) Constructor";

	QObject::connect(&_manager, &QNetworkAccessManager::finished, this, &HttpClient::onReplyReceived);
}

HttpClient::~HttpClient()
{
	qInfo() << "(HttpClient) Destructor";
}

/* Geths the pointer to the only existing HttpClient */
std::shared_ptr<HttpClient> HttpClient::get()
{
	QMutexLocker<QMutex> locker(&_mutex);

	if (!client_ptr)
		client_ptr = std::shared_ptr<HttpClient>(new HttpClient());

	return client_ptr;
}

void HttpClient::postRequest(const NetworkRequest& request,
	const QByteArray& data)
{
	_manager.post(request.getQNetworkRequest(), data);
}

void HttpClient::getRequest(const NetworkRequest& request)
{
	_manager.get(request.getQNetworkRequest());
}

std::shared_ptr<NetworkReply> HttpClient::waitForReply(
	const NetworkRequest& request, ErrorDetail& error, int timeout_ms)
{
	return waitForReply(request, error, {}, timeout_ms);
}

// TODO: should check if the received reply is the one that has been sent, to not mess up asynchronous requests
// -> connect to QNetworkRequest::finished
// TODO: use mutexlocker where needed
std::shared_ptr<NetworkReply> HttpClient::waitForReply(
	const NetworkRequest& request,
	ErrorDetail& error,
	const QByteArray& data,
	int timeout_ms)
{
	std::shared_ptr<NetworkReply> reply;

	// Empty event loop to wait until the request is finished
	QEventLoop wait_loop;
	QObject::connect(this, &HttpClient::receivedReply, &wait_loop, [&]()
		{
			wait_loop.quit();
		});
	QObject::connect(this, &HttpClient::receivedError, &wait_loop, [&]()
		{
			wait_loop.quit();
		});

	// Connect to own receivedReply signal to get the parsed reply
	QObject::connect(this, &HttpClient::receivedReply, &wait_loop,
		[&](std::shared_ptr<NetworkReply> rep)
		{
			reply = rep;
		});

	// Connect to own receivedError signal
	QObject::connect(this, &HttpClient::receivedError, &wait_loop,
		[&](ErrorDetail err)
		{
			error = err;
		});

	// Exit loop after timeout
	if (timeout_ms > 0)
		QTimer::singleShot(timeout_ms, &wait_loop, &QEventLoop::quit);

	switch (request.type)
	{
	case NetworkRequestType::GET:
		getRequest(request);
		break;
	case NetworkRequestType::POST:
		postRequest(request, data);
		break;
	default:
		break;
	}

	wait_loop.exec();

	return reply;
}

/* The QNetworkReply will be deleted once this method exits, so save the
* contents first, before emitting signal */
void HttpClient::onReplyReceived(QNetworkReply* reply)
{

	if (reply->error() != QNetworkReply::NoError)
	{
		const QString& error = reply->errorString();
		const QString& content = QString(reply->readAll());
		qInfo() << "(HttpClient) Got reply with error: " << error << 
			"\n" << content;
		Q_EMIT receivedError(ErrorDetail(error));
		return;
	}

	Q_EMIT receivedReply(std::make_shared<NetworkReply>(reply->readAll()));

	reply->deleteLater();
}

