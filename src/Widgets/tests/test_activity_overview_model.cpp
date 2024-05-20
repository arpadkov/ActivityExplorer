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

template<typename T>
void testVectorsEqual(std::vector<T> lhv, std::vector<T> rhv)
{
	if (lhv.size() != rhv.size())
		GTEST_FAIL();

	for (int i = 0; i < lhv.size(); i++)
		EXPECT_EQ(lhv.at(i), rhv.at(i));
}

TEST(TestActivityOverviewModel, TestYearCategories)
{
	auto model = getTestOverviewModel();
	auto grouped_by = EActivityGroupedBy::Year;
	model.setGroupedBy(grouped_by);
	model.setDateRange(QDate(2018, 01, 01), QDate(2024, 12, 31));

	std::vector<ActivityCategory> expected_year_categories =
	{
		ActivityCategory(QDate(2018, 01, 01), QDate(2018, 12, 31), grouped_by),
		ActivityCategory(QDate(2019, 01, 01), QDate(2019, 12, 31), grouped_by),
		ActivityCategory(QDate(2020, 01, 01), QDate(2020, 12, 31), grouped_by),
		ActivityCategory(QDate(2021, 01, 01), QDate(2021, 12, 31), grouped_by),
		ActivityCategory(QDate(2022, 01, 01), QDate(2022, 12, 31), grouped_by),
		ActivityCategory(QDate(2023, 01, 01), QDate(2023, 12, 31), grouped_by),
		ActivityCategory(QDate(2024, 01, 01), QDate(2024, 12, 31), grouped_by),
	};

	auto categories = model.getCategories();

	testVectorsEqual<ActivityCategory>(expected_year_categories, categories);
}

TEST(TestActivityOverviewModel, TestMonthCategories)
{
	auto model = getTestOverviewModel();
	auto grouped_by = EActivityGroupedBy::Month;
	model.setGroupedBy(grouped_by);
	model.setDateRange(QDate(2022, 5, 1), QDate(2023, 9, 25));

	std::vector<ActivityCategory> expected_month_categories =
	{
		ActivityCategory(QDate(2022, 05, 01), QDate(2022, 05, 31), grouped_by),
		ActivityCategory(QDate(2022, 6, 1), QDate(2022, 6, 30), grouped_by),
		ActivityCategory(QDate(2022, 7, 1), QDate(2022, 7, 31), grouped_by),
		ActivityCategory(QDate(2022, 8, 1), QDate(2022, 8, 31), grouped_by),
		ActivityCategory(QDate(2022, 9, 1), QDate(2022, 9, 30), grouped_by),
		ActivityCategory(QDate(2022, 10, 1), QDate(2022, 10, 31), grouped_by),
		ActivityCategory(QDate(2022, 11, 1), QDate(2022, 11, 30), grouped_by),
		ActivityCategory(QDate(2022, 12, 1), QDate(2022, 12, 31), grouped_by),
		ActivityCategory(QDate(2023, 1, 1), QDate(2023, 1, 31), grouped_by),
		ActivityCategory(QDate(2023, 2, 1), QDate(2023, 2, 28), grouped_by),
		ActivityCategory(QDate(2023, 3, 1), QDate(2023, 3, 31), grouped_by),
		ActivityCategory(QDate(2023, 4, 1), QDate(2023, 4, 30), grouped_by),
		ActivityCategory(QDate(2023, 5, 1), QDate(2023, 5, 31), grouped_by),
		ActivityCategory(QDate(2023, 6, 1), QDate(2023, 6, 30), grouped_by),
		ActivityCategory(QDate(2023, 7, 1), QDate(2023, 7, 31), grouped_by),
		ActivityCategory(QDate(2023, 8, 1), QDate(2023, 8, 31), grouped_by),
		ActivityCategory(QDate(2023, 9, 1), QDate(2023, 9, 30), grouped_by)
	};

	auto categories = model.getCategories();

	testVectorsEqual<ActivityCategory>(expected_month_categories, categories);
}

TEST(TestActivityOverviewModel, TestDayCategories)
{
	auto model = getTestOverviewModel();
	auto grouped_by = EActivityGroupedBy::Day;
	model.setGroupedBy(grouped_by);
	model.setDateRange(QDate(2023, 5, 28), QDate(2023, 6, 3));

	std::vector<ActivityCategory> expected_day_categories =
	{
		ActivityCategory(QDate(2023, 5, 28), QDate(2023, 5, 28), grouped_by),
		ActivityCategory(QDate(2023, 5, 29), QDate(2023, 5, 29), grouped_by),
		ActivityCategory(QDate(2023, 5, 30), QDate(2023, 5, 30), grouped_by),
		ActivityCategory(QDate(2023, 5, 31), QDate(2023, 5, 31), grouped_by),
		ActivityCategory(QDate(2023, 6, 1), QDate(2023, 6, 1), grouped_by),
		ActivityCategory(QDate(2023, 6, 2), QDate(2023, 6, 2), grouped_by),
		ActivityCategory(QDate(2023, 6, 3), QDate(2023, 6, 3), grouped_by)
	};

	auto categories = model.getCategories();

	for (int i = 0; i < categories.size(); i++)
	{
		qInfo() << expected_day_categories[i].toString(ECategoryStringFormat::Full);
		qInfo() << categories[i].toString(ECategoryStringFormat::Full);
	}

	testVectorsEqual<ActivityCategory>(expected_day_categories, categories);
}

TEST(TestActivityOverviewModel, TestActivitiesByCategory_Day)
{
	auto model = getTestOverviewModel();
	model.setGroupedBy(EActivityGroupedBy::Day);
	model.setDateRange(QDate(2023, 3, 14), QDate(2023, 4, 15));

	std::vector<int> expected_act_numbers_categories
	{
			0, // 2023-03-14
			0, // 2023-03-15
			0, // 2023-03-16
			1, // 2023-03-17
			1, // 2023-03-18
			1, // 2023-03-19
			3, // 2023-03-20
			1, // 2023-03-21
			4, // 2023-03-22
			1, // 2023-03-23
			1, // 2023-03-24
			2, // 2023-03-25
			1, // 2023-03-26
			0, // 2023-03-27
			0, // 2023-03-28
			0, // 2023-03-29
			0, // 2023-03-30
			0, // 2023-03-31
			0, // 2023-04-01
			0, // 2023-04-02
			0, // 2023-04-03
			0, // 2023-04-04
			0, // 2023-04-05
			0, // 2023-04-06
			0, // 2023-04-07
			0, // 2023-04-08
			0, // 2023-04-09
			0, // 2023-04-10
			0, // 2023-04-11
			0, // 2023-04-12
			1, // 2023-04-13
			1, // 2023-04-14
			0  // 2023-04-15
	};

	const auto& acts_by_categories = model.getActivitiesByCategory();
	std::vector<int> act_numbers_categories;
	for (const auto& acts : acts_by_categories)
		act_numbers_categories.push_back(acts.second.size());

	testVectorsEqual<int>(expected_act_numbers_categories, act_numbers_categories);
}

TEST(TestActivityOverviewModel, TestActivitiesByCategory_Month)
{
	auto model = getTestOverviewModel();
	model.setGroupedBy(EActivityGroupedBy::Month);
	model.setDateRange(QDate(2023, 3, 28), QDate(2023, 8, 3));

	std::vector<int> expected_act_numbers_categories
	{
		0, // 2023-03-01 - 2023-03-31
		15, // 2023-04-01 - 2023-04-30
		19, // 2023-05-01 - 2023-05-31
		12, // 2023-06-01 - 2023-06-30
		11, // 2023-07-01 - 2023-07-31
	};

	const auto& acts_by_categories = model.getActivitiesByCategory();
	std::vector<int> act_numbers_categories;
	for (const auto& acts : acts_by_categories)
		act_numbers_categories.push_back(acts.second.size());

	testVectorsEqual<int>(expected_act_numbers_categories, act_numbers_categories);
}

TEST(TestActivityOverviewModel, TestActivitiesByCategory_Year)
{
	auto model = getTestOverviewModel();
	model.setGroupedBy(EActivityGroupedBy::Year);
	model.setDateRange(QDate(2020, 3, 28), QDate(2024, 8, 3));

	std::vector<int> expected_act_numbers_categories
	{
		36, // 2020-01-01 - 2020-12-31
		53, // 2021-01-01 - 2021-12-31
		48, // 2022-01-01 - 2022-12-31
		135, // 2023-01-01 - 2023-12-31
		61, // 2024-01-01 - 2024-12-31
	};

	const auto& acts_by_categories = model.getActivitiesByCategory();
	std::vector<int> act_numbers_categories;
	for (const auto& acts : acts_by_categories)
		act_numbers_categories.push_back(acts.second.size());

	testVectorsEqual<int>(expected_act_numbers_categories, act_numbers_categories);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	QApplication a(argc, argv);
	return RUN_ALL_TESTS();
	a.exec();
}