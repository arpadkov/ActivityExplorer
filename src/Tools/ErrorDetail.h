#pragma once

#include <QString>

class ErrorDetail
{
public:
	ErrorDetail();
	ErrorDetail(const QString& message);
	ErrorDetail(std::exception exception);
	~ErrorDetail();

	void setMessage(const QString& message);

	QString getMessage() const;

private:
	QString _error_message;

};