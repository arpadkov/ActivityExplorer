#include "StravaSetupWidget.h"

#include "StravaClient.h"
#include "StravaCredentials.h"

#include <HttpClient/HttpClient.h>
#include <Tools/ErrorDialog.h>

#include <QDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QWebEngineView>
#include <QUrl>
#include <QUrlQuery>

#include "ui_strava_setup_widget.h"


namespace Providers::StravaClient
{

const QString GET_AUTH_CODE_URL = "http://www.strava.com/oauth/authorize?client_id=%1&response_type=code&redirect_uri=http://localhost/exchange_token&approval_prompt=force&scope=read,activity:read_all";

StravaSetupWidget::StravaSetupWidget(QWidget *parent)
	: DataProviderSetupWidget(parent), ui(new Ui::StravaSetupWidget)
{
	ui->setupUi(this);

	QObject::connect(ui->authorize_button, &QPushButton::clicked, this, &StravaSetupWidget::onAuthorize);

	fillFromConfigFile();
}

StravaSetupWidget::~StravaSetupWidget()
{}

void StravaSetupWidget::fillFromConfigFile()
{
	StravaCredential credentials;
	credentials.readCredentials();

	ui->client_id_edit->setText(credentials.client_id);
	ui->client_secret_edit->setText(credentials.client_secret);
}

bool StravaSetupWidget::isConfigured() const
{
	return !(ui->client_id_edit->text().isEmpty() || ui->client_secret_edit->text().isEmpty() || ui->refresh_token_edit->text().isEmpty() || ui->authentication_code_edit->text().isEmpty());
}

/* Write StravaCredentials */
void StravaSetupWidget::onAccepted()
{
	const QString& client_id = ui->client_id_edit->text();
	const QString& client_secret = ui->client_secret_edit->text();
	const QString& refresh_token = ui->refresh_token_edit->text();

	StravaCredential credentials(client_id, client_secret, refresh_token);
	credentials.saveCredentials();
}

void StravaSetupWidget::onAuthorize()
{
	if (!fillAuthorizationCode())
		return;

	fillRefreshToken();
}

/*
* Opens a mini browser with the client id.
* Sets the authorization code in the widget, which is used to get the refresh token.
*/
bool StravaSetupWidget::fillAuthorizationCode()
{
	const QString& client_id = ui->client_id_edit->text();
	const QString& client_secret = ui->client_secret_edit->text();

	auto auth_dlg = QDialog();
	auth_dlg.setWindowTitle("authorize strava access");

	auto layout = QVBoxLayout();
	auth_dlg.setLayout(&layout);

	auto web_view = QWebEngineView();
	web_view.load(QUrl(GET_AUTH_CODE_URL.arg(client_id)));

	layout.addWidget(&web_view);

	const QString code_match = AUTH_CODE + "=";
	QString forwarded_url;
	QObject::connect(&web_view, &QWebEngineView::urlChanged, this, [&]()
		{
			forwarded_url = web_view.url().toString();
			if (forwarded_url.contains(code_match))
				auth_dlg.accept();
		});

	auth_dlg.exec();

	// Return if the dialog was canceled
	if (!forwarded_url.contains(code_match))
		return false;

	QString code;
	int startIndex = forwarded_url.indexOf(code_match);
	if (startIndex != -1) {
		startIndex += code_match.length(); // Move the index to the beginning of the code
		int endIndex = forwarded_url.indexOf('&', startIndex);
		if (endIndex != -1) {
			code = forwarded_url.mid(startIndex, endIndex - startIndex);
		}
	}

	ui->authentication_code_edit->setText(code);
	return true;
}

bool StravaSetupWidget::fillRefreshToken()
{
	auto client = HttpClient::get();

	const QString& client_id = ui->client_id_edit->text();
	const QString& client_secret = ui->client_secret_edit->text();
	const QString& auth_code = ui->authentication_code_edit->text();

	NetworkRequest request(AUTH_URL);
	request.addQueryItem(CLIENT_ID, client_id);
	request.addQueryItem(CLIENT_SECRET, client_secret);
	request.addQueryItem(AUTH_CODE, auth_code);
	request.addQueryItem(GRANT_TYPE, AUTH_CODE_TYPE);

	ErrorDetail error;
	auto reply = client->waitForReply(request, error, 15 * 1000);
	if (!reply)
		throw error;

	const auto& refresh_token = reply->getValue(REFRESH_TOKEN);
	if (refresh_token.isEmpty())
	{
		ErrorDialog::showFrom(QString("json does not contain refresh token\n%1"));
		return false;
	}

	ui->refresh_token_edit->setText(refresh_token);
	qInfo() << "REFRESH TOKEN: " << refresh_token;
	return true;
}

}
