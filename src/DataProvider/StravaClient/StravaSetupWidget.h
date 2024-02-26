#pragma once

#include <QWidget>
#include "ui_strava_setup_widget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
	class StravaSetupWidget;
}
QT_END_NAMESPACE

namespace StravaClient
{

class StravaSetupWidget : public QWidget
{
	Q_OBJECT

public:
	StravaSetupWidget(QWidget *parent = nullptr);
	~StravaSetupWidget();

private:
	void setAuthorizationCode();
	void setRefreshToken();

	QString _client_id;
	QString _client_secret;
	QString _auth_code;
	QString _refresh_token;

	Ui::StravaSetupWidget* ui;
	 
};

}  // namespace StravaClient
