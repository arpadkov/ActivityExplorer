#pragma once

#include <QWidget>
#include <DataProvider/DlgSetupDataProvider.h>

namespace Ui
{
class StravaSetupWidget;
}

namespace Providers::StravaClient
{

class StravaSetupWidget : public DataProviderSetupWidget
{
	Q_OBJECT

public:
	StravaSetupWidget(QWidget *parent = nullptr);
	~StravaSetupWidget();

public Q_SLOTS:


private:
	void setAuthorizationCode();
	void setRefreshToken();

	QString _client_id;
	QString _client_secret;
	QString _auth_code;
	QString _refresh_token;

	Ui::StravaSetupWidget* ui;
	 
};

}  // namespace Providers::StravaClient
