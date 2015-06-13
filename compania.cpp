#include "compania.h"
#include "ui_compania.h"

//Guillermo

compania::compania(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::compania)
{
    ui->setupUi(this);
}

compania::~compania()
{
    delete ui;
}

void compania::openVentana21(){
    gestionarOwner v21;
    v21.setController(*controller_);
    v21.exec();
}

void compania::openVentana22(){
    gestionarUsuario v22;
    v22.setController(*controller_);
    v22.exec();
}

void compania::openVentana23(){
    gestionarNegos v23;
    v23.setController(*controller_);
    v23.exec();
}

void compania::openVentana24(){
    Log v24;
    v24.setController(*controller_);
    v24.exec();
}

void compania::openVentana25(){
    auto iter1=controller_->getNegos().begin();
    size_t count1=controller_->getNegos().count();
    for (size_t i=0; i<=count1; i++){
        if(controller_->getNegos().at(i).borrado()==true){
            controller_->getNegos().erase(iter1);
            count1=controller_->getNegos().count();
        }
        iter1++;
    }

    auto iter2=controller_->getOficinas().begin();
    size_t count2=controller_->getOficinas().count();
    for (size_t i=0; i<count2; i++){
        if(controller_->getOficinas().at(i).borrado()==true){
            controller_->getOficinas().erase(iter2);
        }
        iter2++;
    }

    auto iter3=controller_->getOwners().begin();
    size_t count3=controller_->getOwners().count();
    for (size_t i=0; i<count3; i++){
        if(controller_->getOwners().at(i).borrado()==true){
            controller_->getOwners().erase(iter3);
        }
        iter3++;
    }

    auto iter4=controller_->getUsers().begin();
    size_t count4=controller_->getUsers().count();
    for (size_t i=0; i<count4; i++){
        if(controller_->getUsers().at(i).borrado()==true){
            controller_->getUsers().erase(iter4);
        }
        iter4++;
    }
}

void compania::setController (MainController &controller){
    this->controller_=&controller;
}
