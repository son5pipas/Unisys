#include "ui_compania.h"

#include <QDebug>

#include "compania.h"

//Guillermo

compania::compania(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::compania)
{
    ui->setupUi(this);
}

compania::~compania()
{
    if(controller_->getSuperUser()==true){
        selectUserLogin v1;
        v1.setController(*controller_);
        v1.exec();
    }
    delete ui;
}

void compania::openVentana21(){
    gestionarOwner v21;
    this->close();
    v21.setController(*controller_);
    v21.exec();
}

void compania::openVentana22(){
    gestionarUsuario v22;
    this->close();
    v22.setController(*controller_);
    v22.exec();
}

void compania::openVentana23(){
    gestionarNegos v23;
    this->close();
    v23.setController(*controller_);
    v23.exec();
}

void compania::openVentana24(){
    historial v24;
    this->close();
    v24.setController(*controller_);
    v24.exec();
}

void compania::openVentana25(){
    int owner=0, oficina=0, user=0 ,nego=0;
    controller_->limpiarListas(&owner, &oficina, &user, &nego);

    QString informacion = QString("Han sido eliminados:\n- %1 owners\n- %2 oficinas\n- %3 usuarios\n- %4 negos").arg(owner).arg(oficina).arg(user).arg(nego);
    QMessageBox::information(this, "",QString(informacion));
}

void compania::setController (MainController &controller){
    this->controller_=&controller;
    this->comprobarNegos();
}

void compania::comprobarNegos(){
    int disminuidos=0;
    controller_->disminuirNegos(&disminuidos);
    if (disminuidos!=0){
        QString informacion = QString("Se han disminuido %1 negos hoy").arg(disminuidos);
        QMessageBox::information(this, "", informacion);
    }

    controller_->borrarPasados();
}
