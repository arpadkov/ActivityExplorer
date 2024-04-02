#include <gtest/gtest.h>

#include "HttpClient.h"
#include <NetworkRequest.h>

#include <QApplication>
#include <QDir>
#include <QFile>
#include <QStandardPaths>

const QString ITEM_1_KEY = "item_1";
const QString ITEM_1_VALUE = "value_1";
const QString ITEM_2_KEY = "item_2";
const QString ITEM_2_VALUE = "value_2";

const QString TEST_DATA = "here is some test data";

const QString TEST_DATA_FILE = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QDir::separator() + "testfile.txt";

void writeTestDataFile()
{
	QFile file(TEST_DATA_FILE);

	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		FAIL() << "could not write testfile";

	QTextStream out(&file);
	out << TEST_DATA.toUtf8();

	file.close();
}

QByteArray readTestDataFile()
{
	QFile file(TEST_DATA_FILE);
	if (!file.open(QIODevice::ReadOnly))
		return {};

	QByteArray data = file.readAll();
	file.close();

	return data;
}



TEST(TestHttpClient, TestGetClient) {
	// Must get the same pointer
	auto client1 = HttpClient::get();
	auto client2 = HttpClient::get();

	EXPECT_EQ(client1, client2);
}

TEST(TestHttpClient, TestWaitForReplyGet)
{
	auto client = HttpClient::get();

	const QString test_get_url = "https://httpbin.org/get";

	NetworkRequest request(test_get_url, NetworkRequestType::GET);
	request.addQueryItem(ITEM_1_KEY, ITEM_1_VALUE);
	request.addQueryItem(ITEM_2_KEY, ITEM_2_VALUE);

	ErrorDetail error;
	auto reply = client->waitForReply(request, error, 15 * 1000);

	if (!reply)
	{
		std::cout << "(TestHttpClient) Error\n" << error.getMessage().toStdString();
		FAIL() << "got no reply";
	}

	// Sent items are received back in the "args" key
	auto args_value = reply->getChild("args");
	if (!args_value)
		FAIL() << "has no args child";

	auto item1_value = args_value->getStringValue(ITEM_1_KEY);
	EXPECT_TRUE(item1_value == ITEM_1_VALUE);

	auto item2_value = args_value->getStringValue(ITEM_2_KEY);
	EXPECT_TRUE(item2_value == ITEM_2_VALUE);

	std::cout << "(TestHttpClient) Raw reply\n" << reply->getRawData().toStdString();
	//EXPECT_TRUE(false);	// Shitty way of showing logs
}

TEST(TestHttpClient, TestWaitForReplyPost)
{
	auto client = HttpClient::get();

	const QString test_post_url = "https://httpbin.org/post";

	NetworkRequest request(test_post_url, NetworkRequestType::POST);
	request.addQueryItem(ITEM_1_KEY, ITEM_1_VALUE);
	request.addQueryItem(ITEM_2_KEY, ITEM_2_VALUE);

	writeTestDataFile();
	auto data = readTestDataFile();

	ErrorDetail error;
	auto reply = client->waitForReply(request, error, data, 15 * 1000);

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

	auto reply_data = reply->getStringValue("data");
	EXPECT_TRUE(reply_data == TEST_DATA);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	QApplication a(argc, argv);
	return RUN_ALL_TESTS();
	a.exec();
}

