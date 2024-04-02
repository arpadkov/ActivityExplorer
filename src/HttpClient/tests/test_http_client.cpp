#include <gtest/gtest.h>

#include "HttpClient.h"
#include <NetworkRequest.h>

#include <QtWidgets/QApplication>

const QString ITEM_1_KEY = "item_1";
const QString ITEM_1_VALUE = "value_1";
const QString ITEM_2_KEY = "item_2";
const QString ITEM_2_VALUE = "value_2";


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
	request.addQueryItem(ITEM_1_KEY, ITEM_1_VALUE);
	request.addQueryItem(ITEM_2_KEY, ITEM_2_VALUE);

	ErrorDetail error;
	auto reply = client->waitForReply(request, error, 15 * 1000);

	if (!reply)
		FAIL() << "got no reply";

	// Sent items are received back in the "args" key
	auto args_value = reply->getChild("args");
	if (!args_value)
		FAIL() << "has no args child";

	auto item1_value = args_value->getStringValue(ITEM_1_KEY);
	EXPECT_TRUE(item1_value == ITEM_1_VALUE);

	auto item2_value = args_value->getStringValue(ITEM_2_KEY);
	EXPECT_TRUE(item2_value == ITEM_2_VALUE);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	QApplication a(argc, argv);
	return RUN_ALL_TESTS();
	a.exec();
}

