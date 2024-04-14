#pragma once

#include <QtWidgets/QMainWindow>

// Forwards
namespace Ui
{
class MainWindow;
}

namespace Providers
{
class DataProvider;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow* ui;

	std::shared_ptr<Providers::DataProvider> _provider;

public slots:
	void testFunction();

};

