#include "Logging.h"

#include <QDateTime>
#include <QDir>
#include <QStandardPaths>
#include <QtDebug>
#include <QFile>
#include <QTextStream>

#include <iostream>
#include <windows.h>

static QString session_log_file;
static QString debug_log_file;

QDir getLogFileDirectory()
{
	QString appDataLocation =
		QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

	QString log_dir_name = "log";
	QDir logDir(appDataLocation);
	if (!logDir.exists(log_dir_name)) {
		logDir.mkdir(log_dir_name);
	}

	logDir.cd(log_dir_name);
	return logDir;
}

void createSessionLogFile(const QString file_name)
{
	QFile log_file(file_name);
	log_file.open(QIODevice::WriteOnly);
	log_file.close();
}

/*
* Debug logs are only stored for one session, and overwritten for new sessions
*/
void createDebugLogFile(const QString file_name)
{
	// Delete existing files starting with "DebugLog"
	QDir dir(QFileInfo(file_name).absolutePath());
	QStringList existingFiles =
		dir.entryList(QStringList() << "DebugLog*", QDir::Files);
	for (const QString& existingFile : existingFiles) {
		QFile::remove(dir.filePath(existingFile));
	}

	QFile log_file(file_name);
	log_file.open(QIODevice::WriteOnly);
	log_file.close();
}

void handleDebugMessage(
	QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
	QFile log_file(debug_log_file);
	log_file.open(QIODevice::WriteOnly | QIODevice::Append);

	QTextStream textStream(&log_file);

	QString time = QDateTime::currentDateTime().toString("hh:mm:ss");

	textStream << time << msg << "\n";
}

void handleInfoMessage(
	QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
	QFile log_file(session_log_file);
	log_file.open(QIODevice::WriteOnly | QIODevice::Append);

	QTextStream textStream(&log_file);

	QString time = QDateTime::currentDateTime().toString("hh:mm:ss");

	switch (type)
	{
	case QtInfoMsg:
		textStream << time << "Info:\t" << msg << "\n";
		OutputDebugString(
			reinterpret_cast<const WCHAR*>(QString("Info: " + msg + "\n").utf16()));
		break;
	case QtWarningMsg:
		textStream << time << "Warning:\t" << msg << "\n";
		OutputDebugString(
			reinterpret_cast<const WCHAR*>(QString("Warning: " + msg +"\n").utf16()));
		break;
	default:
		break;
	}
}

void handleErrorMessage(
	QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
	switch (type)
	{
	case QtCriticalMsg:
		OutputDebugString(reinterpret_cast<const WCHAR*>(
			QString("Critical: " + msg + "\n").utf16()));
		break;
	case QtFatalMsg:
		OutputDebugString(reinterpret_cast<const WCHAR*>(
			QString("Fatal: " + msg + "\n").utf16()));
		abort();
	}
}

void setUpLogging()
{
	auto log_folder = getLogFileDirectory();

	session_log_file = log_folder.filePath(
		"SessionLog-" +
		QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss") + ".log");
	createSessionLogFile(session_log_file);

	debug_log_file = log_folder.filePath(
		"DebugLog-" +
		QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss") + ".log");
	createDebugLogFile(debug_log_file);

	qInstallMessageHandler(messageHandler);
}


void messageHandler(
	QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
	QFile log_file(session_log_file);
	log_file.open(QIODevice::WriteOnly | QIODevice::Append);

	QTextStream textStream(&log_file);

	switch (type)
	{
	case QtDebugMsg:
		handleDebugMessage(type, context, msg);
		break;
	case QtInfoMsg:
	case QtWarningMsg:
		handleInfoMessage(type, context, msg);
		handleDebugMessage(type, context, msg);
		break;
	case QtCriticalMsg:
	case QtFatalMsg:
		handleDebugMessage(type, context, msg);
		handleErrorMessage(type, context, msg);
	}
}