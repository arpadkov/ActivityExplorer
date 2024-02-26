#pragma once

#include <QString>

/*
* Class to save/read strava credentials. Responsible for defining the location.
* Should do some encrypting
*/
class StravaCredential
{
public:
	StravaCredential readCredentials();
	bool saveCredentials();

	QString client_id;			// Stored locally and entered manuall
	QString client_secret;		// Stored locally and entered manuall
	QString access_token;		// Stored only for the session
	QString refresh_token;		// Stored locally and entered manuall

private:
	StravaCredential();
	~StravaCredential();
};