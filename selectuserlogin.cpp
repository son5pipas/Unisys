#include "ui_selectuserlogin.h"

#include <QStandardItemModel>
#include <QStandardItem>
#include <qstring.h>
#include <qmessagebox.h>
#include <qstringlist.h>
#include <QListWidgetItem>

#include "selectuserlogin.h"

//JL

selectUserLogin::selectUserLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selectUserLogin) {
    ui->setupUi(this);
}

selectUserLogin::~selectUserLogin(){
    delete ui;
}

void selectUserLogin::setController (MainController &controller){
    this->controller_=&controller;

    criterio.setID_oficina(0);
    criterio.setID_owner(0);
    criterio.setRole(-1);

    this->showOwners();
    this->showOficinas();
    this->showUsers();
}

void selectUserLogin::showUsers (){
    int iowner=ui->comboOwner->currentIndex();
    int owner= 0;
    if (buscarOwn.empty()!=true && iowner>0){
        owner=buscarOwn.at(iowner-1);
    }
    int ioficina=ui->comboOficina->currentIndex();
    int oficina = 0;
    if(buscarOfi.empty()!=true && ioficina>0){
        oficina=buscarOfi.at(ioficina-1);
    }

    criterio.setID_owner(owner);
    criterio.setID_oficina(oficina);

    rellenarTabla(controller_->getUsers(), ui->tableUser, &criterio);
}

void selectUserLogin::showOwners (){
    buscarOwn.clear();
    ui->comboOwner->clear();
    ui->comboOwner->addItem(" ");
    for (size_t i=0; i<controller_->getOwners().count(); i++){
        if(controller_->getOwners().at(i).borrado()!=1){
            ui->comboOwner->addItem(QString::fromStdString(controller_->getOwners().at(i).owner()));
            buscarOwn.append(controller_->getOwners().at(i).ID());
        }
    }
}

void selectUserLogin::showOficinas (){
    int iowner=ui->comboOwner->currentIndex();
    int owner=0;
    if (buscarOwn.empty()!=true && iowner>0){
        owner=buscarOwn.at(iowner-1);
    }

    buscarOfi.clear();
    ui->comboOficina->clear();
    ui->comboOficina->addItem(" ");
    for (size_t i=0; i<controller_->getOficinas().count(); i++){
        if(controller_->getOficinas().at(i).ID_owner()==owner && controller_->getOficinas().at(i).borrado()!=1){
            ui->comboOficina->addItem(QString::fromStdString(controller_->getOficinas().at(i).oficina()));
            buscarOfi.append(controller_->getOficinas().at(i).ID());
        }
    }
}

void selectUserLogin::aceptar(){
    QModelIndexList selectedList = ui->tableUser->selectionModel()->selectedRows();

    controller_->registrado(0);
    if (!selectedList.empty()){

        QString ID = ui->tableUser->item(ui->tableUser->currentRow(), 2)->text();
        int seleccionado = ID.toInt();
        encontrarID(controller_->getUsers(), &seleccionado);

        int role= 0;
        controller_->registrado(seleccionado);
        role = controller_->getUsers().at(seleccionado).role();
        switch (role){
            case 1:{
                selectUserLogin v1;
                v1.setController(*controller_);
                v1.exec();
            }
                break;
            case 2:{
                compania v2;
                this->close();
                v2.setController(*controller_);
                v2.exec();
             }
                break;
            case 3:{
                owner v3;
                v3.setController(*controller_);
                v3.exec();
            }
                break;
            case 4:{
                oficina v4;
                v4.setController(*controller_);
                v4.exec();
            }
                break;
            default:{
            }
                break;
        }
    }else{
        QMessageBox::information(this, "", "Debe seleccionar un usuario");
    }
}
