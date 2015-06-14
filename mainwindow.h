#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "compania.h"
#include "owner.h"
#include "oficina.h"
#include "selectuserlogin.h"
#include "maincontroller.h"
#include "c_user.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    MainController controller;

private slots:
    void login();
};

#endif // MAINWINDOW_H
