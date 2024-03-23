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

	void fillFromConfigFile();

	virtual bool isConfigured() const override;

	virtual void onAccepted() override;


private:
	void onAuthorize();
	bool fillAuthorizationCode();
	bool fillRefreshToken();

	bool _is_configured = false;

	Ui::StravaSetupWidget* ui;
	 
};

}  // namespace Providers::StravaClient
