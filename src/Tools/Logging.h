#pragma once

// Forwards
enum QtMsgType;
class QMessageLogContext;
class QString;

void setUpLogging();
void messageHandler(
	QtMsgType type, const QMessageLogContext& context, const QString& msg);