#include <gtest/gtest.h>

#include "HttpClient.h"
#include <NetworkRequest.h>

#include <QtWidgets/QApplication>


TEST(TestHttpClient, TestGetClient) {
	// Must get the same pointer
	auto client1 = HttpClient::get();
	auto client2 = HttpClient::get();

	EXPECT_EQ(client1, client2);
}

TEST(TestHttpClient, TestWaitForReply)
{
	auto client = HttpClient::get();

	const QString test_post_url = "https://httpbin.org/post";

	NetworkRequest request(test_post_url);
	request.addQueryItem("item1", "value1");

	ErrorDetail error;
	auto reply = client->waitForReply(request, error, 3 * 1000);

	EXPECT_TRUE(reply);
	

	auto value = reply->getValue("args");
	std::cout << value.toStdString();
	std::cout << reply->getRawData().toStdString();



	//const auto& access_token = reply->getValue(ACCESS_TOKEN);
	//if (access_token.isEmpty())
	//	throw std::runtime_error(QString("Reply did not contain access token").toStdString());

	//_access_token = access_token;
	//qInfo() << "ACCESS TOKEN: " << _access_token;
	//return true;

	EXPECT_TRUE(false);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	QApplication a(argc, argv);
	return RUN_ALL_TESTS();
	a.exec();
}

