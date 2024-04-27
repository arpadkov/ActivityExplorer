#include "StravaActivityReaderThread.h"
#include "StravaActivityConverter.h"

#include <ErrorDetail.h>
#include <NetworkReply.h>

#include <QDebug>

namespace Providers::StravaClient
{

StravaActivityReaderThread::StravaActivityReaderThread(
	const std::vector<QString>& filenames, const QDir& dir, QObject* parent) :
	QThread(parent), _filenames(filenames), _dir(dir)
{

}

void StravaActivityReaderThread::run()
{
	std::vector<ActivitySummary> act_summaries;

	for (const auto& filename : _filenames)
	{
		QFile file(_dir.filePath(filename));
		if (!file.open(QIODevice::ReadOnly))
		{
			qWarning() << "(StravaClient): Could not open file: " << filename;
			continue;
		}

		// Create a NetworkReply to parse the json data
		ErrorDetail error;
		auto reply_from_file = NetworkReply(file.readAll());
		auto act_summary = activitySummaryFromStravaReply(reply_from_file, error);
		if (!act_summary)
		{
			qWarning() << "(StravaClient): Could not create ActivitySummary from file: " << filename;
			continue;
		}

		file.close();
		act_summaries.push_back(*act_summary);
	}

	Q_EMIT readFinished(act_summaries);
}

}