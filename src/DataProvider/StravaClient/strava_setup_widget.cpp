#include "StravaSetupWidget.h"

#include "StravaClient.h"

#include <QDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QWebEngineView>
#include <QUrl>
#include <QUrlQuery>


namespace StravaClient
{

const QString GET_AUTH_CODE_URL = "http://www.strava.com/oauth/authorize?client_id=%1&response_type=code&redirect_uri=http://localhost/exchange_token&approval_prompt=force&scope=read,activity:read_all";

StravaSetupWidget::StravaSetupWidget(QWidget *parent)
	: QWidget(parent), ui(new Ui::StravaSetupWidget)
{
	ui->setupUi(this);

	QObject::connect(ui->authorize_button, &QPushButton::clicked, this, &StravaSetupWidget::setAuthorizationCode);
}

StravaSetupWidget::~StravaSetupWidget()
{}

/*
* Opens a mini browser with the client id.
* Returns the authorization code, which is used to get the refresh token.
*/
void StravaSetupWidget::setAuthorizationCode()
{
	_client_id = ui->client_id_edit->text();
	_client_secret = ui->client_secret_edit->text();

	auto auth_dlg = QDialog();
	auth_dlg.setWindowTitle("authorize strava access");

	auto layout = QVBoxLayout();
	auth_dlg.setLayout(&layout);

	auto web_view = QWebEngineView();
	web_view.load(QUrl(GET_AUTH_CODE_URL.arg(_client_id)));

	layout.addWidget(&web_view);

	QString forwarded_url;
	QObject::connect(&web_view, &QWebEngineView::urlChanged, this, [&]()
		{
			forwarded_url = web_view.url().toString();
			if (forwarded_url.contains("code="))
				auth_dlg.accept();
		});

	auth_dlg.exec();

	QString code;
	QString code_start = AUTH_CODE + "=";
	int startIndex = forwarded_url.indexOf(code_start);
	if (startIndex != -1) {
		startIndex += code_start.length(); // Move the index to the beginning of the code
		int endIndex = forwarded_url.indexOf('&', startIndex);
		if (endIndex != -1) {
			code = forwarded_url.mid(startIndex, endIndex - startIndex);
		}
	}

	ui->authentication_code_edit->setText(code);
	_auth_code = code;

	setRefreshToken();
}

void StravaSetupWidget::setRefreshToken()
{
	QNetworkAccessManager* manager = new QNetworkAccessManager();

	QUrl auth_url = QUrl(AUTH_URL);
	QUrlQuery query = QUrlQuery();
	query.addQueryItem(CLIENT_ID, _client_id);
	query.addQueryItem(CLIENT_SECRET, _client_secret);
	query.addQueryItem(AUTH_CODE, _auth_code);
	query.addQueryItem(GRANT_TYPE, AUTH_CODE_TYPE);

	auth_url.setQuery(query);
	QNetworkRequest request = QNetworkRequest(auth_url);
	auto reply = manager->post(request, QByteArray());

	// TODO: use one manager, this is a memory leak !!!
	QObject::connect(manager, &QNetworkAccessManager::finished, this, [this](QNetworkReply* reply)
		{
			if (reply->error() != QNetworkReply::NoError)
			{
				qInfo() << "GOT REPLY WITH ERROR: " << reply->errorString();
				return;
			}

			QJsonObject json = QJsonDocument::fromJson(reply->readAll()).object();
			if (!json.contains(REFRESH_TOKEN))
				return;

			_refresh_token = json.value(ACCESS_TOKEN).toString();
			ui->refresh_token_edit->setText(_refresh_token);
			qInfo() << "REFRESH TOKEN: " << _refresh_token;

			reply->deleteLater();
		});

}

}
