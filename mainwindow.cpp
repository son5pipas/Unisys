#include "ui_mainwindow.h"

#include <qmessagebox.h>

#include "mainwindow.h"

//Alvaro

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    this->controller.init();
}


MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::login(){
    int role;
    role=controller.check_user(ui->txtUser->text().toStdString(), ui->txtPass->text().toStdString());

    switch (role){
        case 1:{
            selectUserLogin v1;
            controller.setSuperUser(true);
            v1.setController(controller);
            v1.exec();
            ui->btnClean->clicked();
        }
            break;
        case 2:{
            compania v2;
            controller.setSuperUser(false);
            v2.setController(controller);
            v2.exec();
            ui->btnClean->clicked();
        }
            break;
        case 3:{
            owner v3;
            controller.setSuperUser(false);
            v3.setController(controller);
            v3.exec();
            ui->btnClean->clicked();
        }
            break;
        case 4:{
            oficina v4;
            controller.setSuperUser(false);
            v4.setController(controller);
            v4.exec();
            ui->btnClean->clicked();
        }
            break;
        default:{
            ui->btnClean->clicked();
            ui->labelError->setText("Usuario o contraseña erróneos");
        }
            break;
    }
}

