#pragma once

#include "ErrorDetail.h"

#include <QtWidgets/QDialog>

// Forwards
namespace Ui
{
class ErrorDialog;
}

class ErrorDetail;

class ErrorDialog : public QDialog
{
	Q_OBJECT

public:
	ErrorDialog(const ErrorDetail& error_detail, QWidget* parent = nullptr);
	~ErrorDialog();

	static void showFrom(const ErrorDetail& error_detail);

private:
	Ui::ErrorDialog* ui;
};