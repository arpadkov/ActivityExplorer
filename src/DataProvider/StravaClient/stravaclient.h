#include <QObject>
#include <QString>

// Forwards
class QNetworkReply;

namespace StravaClient
{

class StravaClient : public QObject
{
Q_OBJECT

public:
	StravaClient();

public slots:
	void getAllActivities();

private:
	bool readUserData();
	bool getAccessToken();

	QString _client_id;			// Stored locally and entered manuall
	QString _client_secret;		// Stored locally and entered manuall
	QString _access_token;		// Stored only for the session
	QString _refresh_token;		// Stored locally and entered manuall
};

} // namespace StravaClient

