#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmessagebox.h>

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

void MainWindow::openVentana1(){
    selectUserLogin v1;
    v1.setController(controller);
    v1.exec();

}

void MainWindow::openVentana2(){
    compania v2;
    v2.setController(controller);
    v2.exec();   
}

void MainWindow::openVentana3(){
    owner v3;
    v3.setController(controller);
    v3.exec(); 
}

void MainWindow::openVentana4(){
    oficina v4;
    v4.setController(controller);
    v4.exec();  
}

void MainWindow::login(){
    int role;
    role=controller.check_user(ui->txtUser->text().toStdString(), ui->txtPass->text().toStdString());

    switch (role){
        case 1:{
            selectUserLogin v1;
            v1.setController(controller);
            v1.exec();            
        }
            break;
        case 2:{
            compania v2;
            v2.setController(controller);
            v2.exec();
        }
            break;
        case 3:{
            owner v3;
            v3.setController(controller);
            v3.exec();
        }
            break;
        case 4:{
            oficina v4;
            v4.setController(controller);
            v4.exec();
        }
            break;
        default:{
            ui->btnClean->clicked();
            ui->labelError->setText("Usuario o contraseña erróneos");
        }
            break;
    }
}

