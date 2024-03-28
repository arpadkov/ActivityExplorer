#include <gtest/gtest.h>

#include "HttpClient.h"


TEST(TestHttpClient, TestGetClient) {
	auto client1 = HttpClient::get();
	auto client2 = HttpClient::get();

	EXPECT_EQ(client1, client2);
}
