#include "ErrorDetail.h"

ErrorDetail::ErrorDetail()
{

}

ErrorDetail::ErrorDetail(const QString& message)
{
	_error_message = message;
}

ErrorDetail::ErrorDetail(std::exception exception)
{
	_error_message = exception.what();
}

ErrorDetail::~ErrorDetail()
{
}

void ErrorDetail::setMessage(const QString& message)
{
	_error_message = message;
}

QString ErrorDetail::getMessage() const
{
	return _error_message;
}

