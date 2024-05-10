#include <gtest/gtest.h>

#include <Activity.h>
#include <ActivityOverviewModel.h>
#include <StravaClient/StravaActivityReaderThread.h>

#include <QApplication>
#include <QEventLoop>
#include <QTimer>
#include <QDir>
#include <QObject>

using namespace Widgets;
using namespace Providers;
using namespace Providers::StravaClient;

std::vector<ActivitySummary> getTestActivities()
{
	// TODO: Create some generic method to create test activities
	// For now: use strava client-s activity reader thread with some test files

	qInfo() << "Current working directory:" << QDir::currentPath();

	QDir test_acts_dir = QDir(QDir::currentPath());
	test_acts_dir.cd("test_activities");

	std::vector<QString> files;
	for (const auto& file : test_acts_dir.entryList(QDir::Files))
		files.push_back(file);

	QEventLoop wait_loop;

	std::vector<ActivitySummary> acts;

	auto reader = new StravaActivityReaderThread(files, test_acts_dir, &wait_loop);
	QObject::connect(reader, &StravaActivityReaderThread::finished, reader, &QObject::deleteLater);
	QObject::connect(reader, &StravaActivityReaderThread::readFinished, &wait_loop,
		[&](const std::vector<ActivitySummary>& read_acts)
		{
			for (const auto& act : read_acts)
				acts.push_back(act);
			wait_loop.quit();
		});
	reader->start();

	QTimer::singleShot(5 * 1000, &wait_loop, &QEventLoop::quit);

	// Wait until the reading is finished
	wait_loop.exec();

	return acts;
}

ActivityOverviewModel getTestOverviewModel()
{
	auto acts = getTestActivities();

	return ActivityOverviewModel(acts, nullptr);
}

template <typename T>
void testListsEqual(QList<T> lhv, QList<T> rhv)
{
	if (lhv.size() != rhv.size())
		GTEST_FAIL();

	for (int i = 0; i < lhv.size(); i++)
		EXPECT_EQ(lhv.at(i), rhv.at(i));
}

TEST(TestActivityOverviewModel, TestYearCategories)
{
	auto model = getTestOverviewModel();
	model.setGroupedBy(EActivityGroupedBy::Year);

	QStringList expected_year_categories = {"2018", "2019", "2020", "2021", "2022", "2023", "2024"};
	auto categories = model.getCategories();

	testListsEqual<QString>(expected_year_categories.toList(), categories.toList());
}

TEST(TestActivityOverviewModel, TestMonthCategories)
{
	auto model = getTestOverviewModel();
	model.setGroupedBy(EActivityGroupedBy::Month);
	model.setDateRange(QDate(2022, 5, 1), QDate(2023, 9, 25));

	QStringList expected_month_categories = {"2022-May", "2022-June", "2022-July", "2022-August", "2022-September",
		"2022-October", "2022-November", "2022-December", "2023-January", "2023-February", "2023-March", "2023-April",
		"2023-May", "2023-June", "2023-July", "2023-August", "2023-September"};
	auto categories = model.getCategories();

	testListsEqual<QString>(expected_month_categories.toList(), categories.toList());
}

TEST(TestActivityOverviewModel, TestDayCategories)
{
	auto model = getTestOverviewModel();
	model.setGroupedBy(EActivityGroupedBy::Day);
	model.setDateRange(QDate(2023, 5, 28), QDate(2023, 6, 3));

	QStringList expected_day_categories = { "May-28", "May-29", "May-30", "May-31", "June-01", "June-02", "June-03" };
	auto categories = model.getCategories();

	testListsEqual<QString>(expected_day_categories.toList(), categories.toList());
}

TEST(TestActivityOverviewModel, TestValuesForAttributeByCategory)
{
	auto model = getTestOverviewModel();
	model.setGroupedBy(EActivityGroupedBy::Day);
	model.setDateRange(QDate(2023, 5, 28), QDate(2023, 6, 3));

	auto values = model.getValuesForAttributeByCategory(
		ActivitySummary::ESummableAttribute::Distance, EActivityType::Run);
	for (const auto& val : values)
		qInfo() << val;

}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	QApplication a(argc, argv);
	return RUN_ALL_TESTS();
	a.exec();
}