#pragma once

#include <QString>

namespace Providers::StravaClient
{
/*
* Class to save/read strava credentials. Responsible for defining the location.
* Should do some encrypting
*/
class StravaCredential
{
public:
	StravaCredential(QString client_id_, QString client_secret_, QString refresh_token_);
	StravaCredential();
	~StravaCredential();

	bool readCredentials(QString filename_hint = {});
	bool saveCredentials();

	QString client_id;			// Stored locally and entered manuall
	QString client_secret;		// Stored locally and entered manuall
	QString refresh_token;		// Stored locally and entered manuall
};

}