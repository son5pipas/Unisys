#include "ui_owner.h"

#include "owner.h"

//Sergio

owner::owner(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::owner)
{
    ui->setupUi(this);
}

owner::~owner()
{
    if(controller_->getSuperUser()==true){
        selectUserLogin v1;
        v1.setController(*controller_);
        v1.exec();
    }
    delete ui;
}

void owner::openVentana31(){
    gestionarOficina v31;
    v31.setController(*controller_);
    v31.exec();
}

void owner::openVentana32(){
    gestionarUsuario v32;
    v32.setController(*controller_);
    v32.exec();
}

void owner::openVentana33(){
    consultarNegos v33;
    v33.setController(*controller_);
    v33.exec();
}

void owner::setController (MainController &controller){
    controller_=&controller;
}
