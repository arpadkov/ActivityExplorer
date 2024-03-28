#include <gtest/gtest.h>

#include <DataProvider.h>
#include <QString>

TEST(HelloTest, BasicAssertions) {
	QString str1 = "abc";
	QString str2 = "abc";
	
	EXPECT_EQ(str1, str2);
}
