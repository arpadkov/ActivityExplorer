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
using namespace Providers::StravaClient;

std::vector<Providers::ActivitySummary> getTestActivities()
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

	std::vector<Providers::ActivitySummary> acts;

	auto reader = new StravaActivityReaderThread(files, test_acts_dir, &wait_loop);
	QObject::connect(reader, &StravaActivityReaderThread::finished, reader, &QObject::deleteLater);
	QObject::connect(reader, &StravaActivityReaderThread::readFinished, &wait_loop,
		[&](const std::vector<Providers::ActivitySummary>& read_acts)
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

TEST(TestActivityOverviewModel, TestCategories)
{
	auto acts = getTestActivities();
	for (const auto& act : acts)
		qInfo() << "ACT: " << act.start_date;

	EXPECT_TRUE(true);
}

// TODO: This should be removed, only needed because of StravaActivityReaderThread
int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	QApplication a(argc, argv);
	return RUN_ALL_TESTS();
	a.exec();
}