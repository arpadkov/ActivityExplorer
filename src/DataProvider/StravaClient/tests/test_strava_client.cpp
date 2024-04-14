#include <gtest/gtest.h>

#include <DataProvider.h>
#include <StravaClient.h>
#include <StravaCredentials.h>

#include <QApplication>
#include <QDir>
#include <QString>

using namespace Providers::StravaClient;

/*
* Get the StravaClient credentials location, but since QStandardPath depends on
* the executable name
* change test_strava_client to ActivityExplorer
*/
QString getStravaCredentialsLocationFromTest()
{
	QString original_filename = Providers::getDataProviderLocation() +
		QDir::separator() +
		STRAVA_CLIENT_FOLDER +
		QDir::separator() +
		USER_DATA_FILE;

	return original_filename.replace("test_strava_client", "ActivityExplorer");
}

TEST(TestStravaClient, TestInitialize)
{
	auto cl = std::make_shared<StravaClient>();

	auto credentials_hint = StravaCredential();
	credentials_hint.readCredentials(getStravaCredentialsLocationFromTest());

	EXPECT_NO_THROW(cl->initilize(credentials_hint));
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	QApplication a(argc, argv);
	return RUN_ALL_TESTS();
	a.exec();
}
