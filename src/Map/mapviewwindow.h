#pragma once

#include <QDialog>

namespace Ui {
class MapViewWindow;
}

class MapViewWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MapViewWindow(QWidget *parent = nullptr);
    ~MapViewWindow();

private:
    Ui::MapViewWindow *ui;
};

