#include <gtest/gtest.h>

#include <Activity.h>
#include <DataProvider.h>
#include <ErrorDetail.h>
#include <StravaClient.h>
#include <StravaCredentials.h>

#include <QApplication>
#include <QDir>
#include <QString>

using namespace Providers::StravaClient;

// =================================================================================== //
// These tests require a configured StravaClient with valid credentials and activities //
// =================================================================================== //

static std::shared_ptr<StravaClient> client;

/*
* Get the StravaClient location, but since QStandardPath depends on the executable name
* change test_strava_client to ActivityExplorer
*/
QString getStravaClientDirectory()
{
	QString original_filename = Providers::getDataProviderLocation() + QDir::separator() + STRAVA_CLIENT_FOLDER;

	return original_filename.replace("test_strava_client", "ActivityExplorer");
}

void initializeStravaClient()
{
	auto credentials_hint = StravaCredential();
	credentials_hint.readCredentials(getStravaClientDirectory() + QDir::separator() + USER_DATA_FILE);

	auto cl = std::make_shared<StravaClient>();
	if (cl->initilize(credentials_hint))
		client = cl;
}

TEST(TestStravaClient, TestInitialize)
{
	EXPECT_NO_THROW(initializeStravaClient());
}

TEST(TestStravaClient, TestOther)
{
	if (!client)
		initializeStravaClient();

	QCoreApplication::setApplicationName("ActivityExplorer");

	ErrorDetail error;
	auto acts = client->getAllActivities(error);
	EXPECT_FALSE(acts.empty());
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	QApplication a(argc, argv);
	return RUN_ALL_TESTS();
	a.exec();
}
