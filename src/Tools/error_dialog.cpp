#include "ErrorDialog.h"

#include "ui_error_dialog.h"

ErrorDialog::ErrorDialog(const ErrorDetail& error_detail, QWidget* parent) : QDialog(parent), ui(new Ui::ErrorDialog)
{
	ui->setupUi(this);

	ui->error_label->setText(error_detail.getMessage());
}

ErrorDialog::~ErrorDialog()
{
}

void ErrorDialog::showFrom(const ErrorDetail& error_detail)
{
	ErrorDialog* dlg = new ErrorDialog(error_detail);
	dlg->show();
}
