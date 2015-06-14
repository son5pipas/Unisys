#include "ui_gestionarowner.h"

#include <qmessagebox.h>
#include <QDebug>

#include "gestionarowner.h"

//Guillermo

gestionarOwner::gestionarOwner(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestionarOwner){
    ui->setupUi(this);

}

gestionarOwner::~gestionarOwner()
{
    compania v2;
    v2.setController(*controller_);
    v2.exec();
    delete ui;
}

void gestionarOwner::setController (MainController &controller){
    controller_=&controller;
    this->inicial();

}

void gestionarOwner::inicial(){
    this->showOwner();
    ui->editOwner->setEnabled(false);
    ui->btnAcpetar->setEnabled(false);
    ui->btnCancelar->setEnabled(false);
    ui->btnModificar->setEnabled(false);
    ui->btnBorrar->setEnabled(false);
    ui->btnNuevo->setEnabled(true);
    ui->tableOwner->setEnabled(true);
}

void gestionarOwner::limpiarLabel(){
    ui->txtOwner->clear();
    ui->txtRazon->clear();
    ui->txtTlfn->clear();
    ui->txtNIF->clear();
    ui->txtPoblacion->clear();
    ui->txtProvincia->clear();
    ui->txtCP->clear();
    ui->txtPais->clear();
    ui->txtDireccion->clear();
    ui->plaintxtObservaciones->clear();
}

void gestionarOwner::showOwner(){
    rellenarTabla(controller_->getOwners(), ui->tableOwner, &criterio);
}

void gestionarOwner::showLabel(){
    QString ID = ui->tableOwner->item(ui->tableOwner->currentRow(),4)->text();
    int seleccionado = ID.toInt();
    encontrarID(controller_->getOwners(), &seleccionado);

    ui->txtOwner->setText(QString::fromStdString(controller_->getOwners().at(seleccionado).owner()));
    ui->txtRazon->setText(QString::fromStdString(controller_->getOwners().at(seleccionado).razon()));
    ui->txtTlfn->setText(QString::fromStdString(controller_->getOwners().at(seleccionado).tlfn()));
    ui->txtNIF->setText(QString::fromStdString(controller_->getOwners().at(seleccionado).NIF()));
    ui->txtPoblacion->setText(QString::fromStdString(controller_->getOwners().at(seleccionado).poblacion()));
    ui->txtProvincia->setText(QString::fromStdString(controller_->getOwners().at(seleccionado).provincia()));
    ui->txtCP->setText(QString::fromStdString(controller_->getOwners().at(seleccionado).CP()));
    ui->txtPais->setText(QString::fromStdString(controller_->getOwners().at(seleccionado).pais()));
    ui->txtDireccion->setText(QString::fromStdString(controller_->getOwners().at(seleccionado).direccion()));
    ui->plaintxtObservaciones->setPlainText(QString::fromStdString(controller_->getOwners().at(seleccionado).observaciones()));

    ui->btnModificar->setEnabled(true);
    ui->btnBorrar->setEnabled(true);
}

void gestionarOwner::nuevo(){
    opcion=1;
    ui->editOwner->setEnabled(true);
    ui->tableOwner->clearSelection();
    ui->tableOwner->setEnabled(false);
    ui->btnModificar->setEnabled(false);
    ui->btnBorrar->setEnabled(false);
    ui->btnAcpetar->setEnabled(true);
    ui->btnCancelar->setEnabled(true);
    ui->btnNuevo->setEnabled(false);

    this->limpiarLabel();

    ui->txtOwner->setFocus();
}

void gestionarOwner::modificar(){
    QModelIndexList selectedList = ui->tableOwner->selectionModel()->selectedRows();
    if (!selectedList.empty()){
        opcion=2;
        ui->editOwner->setEnabled(true);
        ui->tableOwner->setEnabled(false);
        ui->txtOwner->setFocus();
        ui->btnAcpetar->setEnabled(true);
        ui->btnCancelar->setEnabled(true);
        ui->btnModificar->setEnabled(false);
        ui->btnBorrar->setEnabled(false);
        ui->btnNuevo->setEnabled(false);
    }
}

void gestionarOwner::borrar(){
    QString ID = ui->tableOwner->item(ui->tableOwner->currentRow(),4)->text();
    int seleccionado = ID.toInt();
    encontrarID(controller_->getNegos(), &seleccionado);

    ui->editOwner->setEnabled(false);
    ui->tableOwner->setEnabled(false);
    ui->btnAcpetar->setEnabled(false);
    ui->btnCancelar->setEnabled(false);
    ui->btnModificar->setEnabled(false);
    ui->btnBorrar->setEnabled(false);
    ui->btnNuevo->setEnabled(false);
    QMessageBox::StandardButton btnBorrar;
    btnBorrar = QMessageBox::question(this, "", "Está seguro que desea eliminar el Owner: " + QString::fromStdString(controller_->getOwners().at(seleccionado).owner()), QMessageBox::Yes | QMessageBox:: No);
    if(btnBorrar == QMessageBox::Yes){
        c_owner copyBorrar = controller_->getOwners().at(seleccionado);
        copyBorrar.setBorrado(true);
        controller_->modificarOwner(seleccionado, copyBorrar);
        for (size_t i=0; i<controller_->getUsers().count(); i++){
            if(controller_->getUsers().at(i).ID_owner()==ID.toInt()){
                c_user copyUser = controller_->getUsers().at(i);
                copyUser.setBorrado(true);
                controller_->modificarUser(i,copyUser);
            }
        }
        for(size_t i=0; i<controller_->getOficinas().count(); i++){
            if(controller_->getOficinas().at(i).ID_owner()==ID.toInt()){
                c_oficina copyOficina = controller_->getOficinas().at(i);
                copyOficina.setBorrado(true);
                controller_->modificarOficina(i, copyOficina);
            }
        }
        for(size_t i=0; i<controller_->getNegos().count(); i++){
            if(controller_->getNegos().at(i).ID_owner()==ID.toInt()){
                c_nego copyNego = controller_->getNegos().at(i);
                copyNego.setBorrado(true);
                controller_->modificarNego(i, copyNego);
            }
        }
        this->inicial();
        this->limpiarLabel();
    }else if(btnBorrar == QMessageBox::No){
        this->inicial();
        this->limpiarLabel();
    }
}


void gestionarOwner::aceptar(){
    switch (opcion) {
    case 1:{
        if(ui->txtOwner->text().isEmpty() || ui->txtRazon->text().isEmpty() || ui->txtCP->text().isEmpty() || ui->txtDireccion->text().isEmpty() || ui->txtNIF->text().isEmpty() || ui->txtPais->text().isEmpty() || ui->txtPoblacion->text().isEmpty() || ui->txtProvincia->text().isEmpty() || ui->txtTlfn->text().isEmpty()){
            QMessageBox::information(this, "", "Debe rellenar todos los campos");
        }else{
            c_owner nuevo;

            controller_->setUltimoIDowners();

            nuevo.setID(controller_->getUltimoIDowners());
            nuevo.setBorrado(false);
            nuevo.setOwner(ui->txtOwner->text().toStdString());
            nuevo.setRazon(ui->txtRazon->text().toStdString());
            nuevo.setNIF(ui->txtNIF->text().toStdString());
            nuevo.setTlfn(ui->txtTlfn->text().toStdString());
            nuevo.setDireccion(ui->txtDireccion->text().toStdString());
            nuevo.setCP(ui->txtCP->text().toStdString());
            nuevo.setPoblacion(ui->txtPoblacion->text().toStdString());
            nuevo.setProvincia(ui->txtProvincia->text().toStdString());
            nuevo.setPais(ui->txtPais->text().toStdString());
            nuevo.setObservaciones(ui->plaintxtObservaciones->toPlainText().toStdString());

            controller_->setOwner(nuevo);
            this->inicial();
            ui->tableOwner->selectRow(ui->tableOwner->rowCount()-1);
        }
        break;
    }
    case 2:{
        QString ID = ui->tableOwner->item(ui->tableOwner->currentRow(),4)->text();
        int seleccionado = ID.toInt();
        encontrarID(controller_->getOwners(), &seleccionado);
        int fila = ui->tableOwner->currentRow();

        if(ui->txtOwner->text().isEmpty() || ui->txtRazon->text().isEmpty() || ui->txtCP->text().isEmpty() || ui->txtDireccion->text().isEmpty() || ui->txtNIF->text().isEmpty() || ui->txtPais->text().isEmpty() || ui->txtPoblacion->text().isEmpty() || ui->txtProvincia->text().isEmpty() || ui->txtTlfn->text().isEmpty()){
            QMessageBox::information(this, "", "Todos los campos deben estár rellenos");
        }else{
            c_owner modificado;
            modificado=controller_->getOwners().at(seleccionado);
            modificado.setOwner(ui->txtOwner->text().toStdString());
            modificado.setRazon(ui->txtRazon->text().toStdString());
            modificado.setNIF(ui->txtNIF->text().toStdString());
            modificado.setTlfn(ui->txtTlfn->text().toStdString());
            modificado.setDireccion(ui->txtDireccion->text().toStdString());
            modificado.setCP(ui->txtCP->text().toStdString());
            modificado.setPoblacion(ui->txtPoblacion->text().toStdString());
            modificado.setProvincia(ui->txtProvincia->text().toStdString());
            modificado.setPais(ui->txtPais->text().toStdString());
            modificado.setObservaciones(ui->plaintxtObservaciones->toPlainText().toStdString());
            controller_->modificarOwner(seleccionado, modificado);

            this->inicial();
            ui->tableOwner->selectRow(fila);
        }
        break;
    }
    default:
        break;
    }
}

void gestionarOwner::cancelar(){
    this->inicial();
    this->limpiarLabel();
}
