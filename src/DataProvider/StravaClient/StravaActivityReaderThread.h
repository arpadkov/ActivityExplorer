#pragma once

#include <Activity.h>

#include <QDir>
#include <QThread>
#include <QString>

// Forwards
class QString;

namespace Providers::StravaClient
{

class StravaActivityReaderThread : public QThread
{
	Q_OBJECT

public:
	StravaActivityReaderThread(const std::vector<QString>& filenames, const QDir& dir, QObject* parent);

	void run() override;

Q_SIGNALS:
	void readFinished(std::vector<ActivitySummary>);

private:
	std::vector<QString> _filenames;
	QDir _dir;
};

}