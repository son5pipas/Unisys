#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <selectuserlogin.h>
#include <compania.h>
#include <owner.h>
#include <oficina.h>
#include <c_user.h>
#include <maincontroller.h>


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
    void openVentana1();
    void openVentana2();
    void openVentana3();
    void openVentana4();

    void login();
};

#endif // MAINWINDOW_H
