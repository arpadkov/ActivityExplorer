#include "StravaClient.h"
#include "StravaSetupWidget.h"
#include "StravaCredentials.h"

#include <HttpClient.h>
#include <NetworkRequest.h>


namespace Providers::StravaClient
{

StravaClient::StravaClient() : DataProvider()
{
	qInfo("(StravaClient): Constructor");
}

StravaClient::~StravaClient()
{
	qInfo("(StravaClient): Destructor");
}

/* Read credentials from file, and set refresh token
  Can throw std::runtime_error */
bool StravaClient::initilize()
{
	auto credentials = StravaCredential();
	if (!credentials.readCredentials())
		throw std::runtime_error("Could not read credentials");

	if (!setAccessToken(credentials))
		throw std::runtime_error("Could not set access token");

	return true;
}

DataProviderSetupWidget* StravaClient::createSetupWidget()
{
	return new StravaSetupWidget();
}

QString StravaClient::getType()
{
	return STRAVA_CLIENT;
}

bool StravaClient::setAccessToken(const StravaCredential& credentials)
{
	auto client = HttpClient::get();

	NetworkRequest request(AUTH_URL);
	request.addQueryItem(CLIENT_ID, credentials.client_id);
	request.addQueryItem(CLIENT_SECRET, credentials.client_secret);
	request.addQueryItem(REFRESH_TOKEN, credentials.refresh_token);
	request.addQueryItem(GRANT_TYPE, REFRESH_TOKEN);

	ErrorDetail error;
	auto reply = client->waitForReply(request, error, 15 * 1000);
	if (!reply)
		throw error;

	const auto& access_token = 	reply->getValue(ACCESS_TOKEN);
	if (access_token.isEmpty())
		throw std::runtime_error(QString("Reply did not contain access token").toStdString());

	_access_token = access_token;
	qInfo() << "ACCESS TOKEN: " << _access_token;
	return true;
}


} // namespace Providers::StravaClient
