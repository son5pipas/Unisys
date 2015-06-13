#include "gestionaroficina.h"
#include "ui_gestionaroficina.h"
#include <QMessageBox>
#include <QDebug>

//ROI

gestionarOficina::gestionarOficina(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestionarOficina)
{
    ui->setupUi(this);
}

gestionarOficina::~gestionarOficina()
{
    delete ui;
}

void gestionarOficina::setController (MainController &controller){
    controller_=&controller;
    criterio.setID_owner(controller_->getUsers().at(controller_->getRegistrado()).ID_owner());
    this->inicial();
}

void gestionarOficina::inicial(){
    this->showOficina();
    ui->editOficina->setEnabled(false);
    ui->btnAcpetar->setEnabled(false);
    ui->btnCancelar->setEnabled(false);
    ui->btnModificar->setEnabled(false);
    ui->btnBorrar->setEnabled(false);
    ui->btnNuevo->setEnabled(true);
    ui->tableOficina->setEnabled(true);
}

void gestionarOficina::limpiarLabel(){
    ui->txtOficina->clear();
    ui->txtRazon->clear();
    ui->txtTlfn->clear();
    ui->txtNIF->clear();
    ui->txtPoblacion->clear();
    ui->txtProvincia->clear();
    ui->txtCP->clear();
    ui->txtPais->clear();
    ui->txtContinente->clear();
    ui->txtDireccion->clear();
    ui->plaintxtObservaciones->clear();
}

void gestionarOficina::showOficina(){
    rellenarTabla(controller_->getOficinas(), ui->tableOficina, &criterio);
}

void gestionarOficina::showLabel(){
    qDebug()<<"current: "<<ui->tableOficina->currentRow();
    if (ui->tableOficina->rowCount()>0){
        QString ID = ui->tableOficina->item(ui->tableOficina->currentRow(),4)->text();
        int seleccionado = ID.toInt();
        encontrarID(controller_->getOficinas(), &seleccionado);

        ui->txtOficina->setText(QString::fromStdString(controller_->getOficinas().at(seleccionado).oficina()));
        ui->txtRazon->setText(QString::fromStdString(controller_->getOficinas().at(seleccionado).razon()));
        ui->txtTlfn->setText(QString::fromStdString(controller_->getOficinas().at(seleccionado).tlfn()));
        ui->txtNIF->setText(QString::fromStdString(controller_->getOficinas().at(seleccionado).NIF()));
        ui->txtPoblacion->setText(QString::fromStdString(controller_->getOficinas().at(seleccionado).poblacion()));
        ui->txtProvincia->setText(QString::fromStdString(controller_->getOficinas().at(seleccionado).provincia()));
        ui->txtCP->setText(QString::fromStdString(controller_->getOficinas().at(seleccionado).CP()));
        ui->txtPais->setText(QString::fromStdString(controller_->getOficinas().at(seleccionado).pais()));
        ui->txtContinente->setText(QString::fromStdString(controller_->getOficinas().at(seleccionado).continente()));
        ui->txtDireccion->setText(QString::fromStdString(controller_->getOficinas().at(seleccionado).direccion()));
        ui->plaintxtObservaciones->setPlainText(QString::fromStdString(controller_->getOficinas().at(seleccionado).observaciones()));

        ui->btnModificar->setEnabled(true);
        ui->btnBorrar->setEnabled(true);
    }
}

void gestionarOficina::nuevo(){
    opcion=1;
    ui->editOficina->setEnabled(true);
    ui->tableOficina->clearSelection();
    ui->tableOficina->setEnabled(false);
    ui->btnModificar->setEnabled(false);
    ui->btnBorrar->setEnabled(false);
    ui->btnAcpetar->setEnabled(true);
    ui->btnCancelar->setEnabled(true);
    ui->btnNuevo->setEnabled(false);

    this->limpiarLabel();

    ui->txtOficina->setFocus();
}

void gestionarOficina::modificar(){
    QModelIndexList selectedList = ui->tableOficina->selectionModel()->selectedRows();
    if (!selectedList.empty()){
        opcion=2;
        ui->editOficina->setEnabled(true);
        ui->tableOficina->setEnabled(false);
        ui->txtOficina->setFocus();
        ui->btnAcpetar->setEnabled(true);
        ui->btnCancelar->setEnabled(true);
        ui->btnModificar->setEnabled(false);
        ui->btnBorrar->setEnabled(false);
        ui->btnNuevo->setEnabled(false);
    }
}

void gestionarOficina::borrar(){
    QString ID = ui->tableOficina->item(ui->tableOficina->currentRow(),4)->text();
    int seleccionado = ID.toInt();
    encontrarID(controller_->getOficinas(), &seleccionado);

    ui->editOficina->setEnabled(false);
    ui->tableOficina->setEnabled(false);
    ui->btnAcpetar->setEnabled(false);
    ui->btnCancelar->setEnabled(false);
    ui->btnModificar->setEnabled(false);
    ui->btnBorrar->setEnabled(false);
    ui->btnNuevo->setEnabled(false);
    QMessageBox::StandardButton btnBorrar;
    btnBorrar = QMessageBox::question(this, "", "Está seguro que desea eliminar la oficina: " + QString::fromStdString(controller_->getOficinas().at(seleccionado).oficina()), QMessageBox::Yes | QMessageBox:: No);
    if(btnBorrar == QMessageBox::Yes){
        c_oficina copyBorrar = controller_->getOficinas().at(seleccionado);
        copyBorrar.setBorrado(true);
        controller_->modificarOficina(seleccionado, copyBorrar);
        for(size_t i=0; i<controller_->getUsers().count(); i++){
            if(controller_->getUsers().at(i).ID_oficina()==ID.toInt()){
                c_user copyUser = controller_->getUsers().at(i);
                copyUser.setBorrado(true);
                controller_->modificarUser(i, copyUser);
            }
        }
        this->inicial();
        this->limpiarLabel();
    }else if(btnBorrar == QMessageBox::No){
        this->inicial();
        this->limpiarLabel();
    }
}

void gestionarOficina::aceptar(){
    switch (opcion) {
    case 1:{
        if(ui->txtOficina->text().isEmpty() || ui->txtRazon->text().isEmpty() || ui->txtCP->text().isEmpty() || ui->txtDireccion->text().isEmpty() || ui->txtNIF->text().isEmpty() || ui->txtPais->text().isEmpty() || ui->txtContinente->text().isEmpty() || ui->txtPoblacion->text().isEmpty() || ui->txtProvincia->text().isEmpty() || ui->txtTlfn->text().isEmpty()){
            QMessageBox::information(this, "", "Debe rellenar todos los campos");
        }else{
            c_oficina nuevo;

            controller_->setUltimoIDoficinas();

            nuevo.setID(controller_->getUltimoIDoficinas());
            nuevo.setID_owner(criterio.ID_owner());
            nuevo.setBorrado(false);
            nuevo.setOficina(ui->txtOficina->text().toStdString());
            nuevo.setRazon(ui->txtRazon->text().toStdString());
            nuevo.setNIF(ui->txtNIF->text().toStdString());
            nuevo.setTlfn(ui->txtTlfn->text().toStdString());
            nuevo.setDireccion(ui->txtDireccion->text().toStdString());
            nuevo.setCP(ui->txtCP->text().toStdString());
            nuevo.setPoblacion(ui->txtPoblacion->text().toStdString());
            nuevo.setProvincia(ui->txtProvincia->text().toStdString());
            nuevo.setPais(ui->txtPais->text().toStdString());
            nuevo.setContinente(ui->txtContinente->text().toStdString());
            nuevo.setObservaciones(ui->plaintxtObservaciones->toPlainText().toStdString());
            controller_->setOficina(nuevo);
            this->inicial();
            ui->tableOficina->selectRow(ui->tableOficina->rowCount()-1);
        }
        break;
    }
    case 2:{
        QString ID = ui->tableOficina->item(ui->tableOficina->currentRow(),4)->text();
        int seleccionado = ID.toInt();
        encontrarID(controller_->getOficinas(), &seleccionado);
        int fila = ui->tableOficina->currentRow();

        if(ui->txtOficina->text().isEmpty() || ui->txtRazon->text().isEmpty() || ui->txtCP->text().isEmpty() || ui->txtDireccion->text().isEmpty() || ui->txtNIF->text().isEmpty() || ui->txtPais->text().isEmpty() || ui->txtContinente->text().isEmpty() || ui->txtPoblacion->text().isEmpty() || ui->txtProvincia->text().isEmpty() || ui->txtTlfn->text().isEmpty()){
            QMessageBox::information(this, "", "Todos los campos deben estár rellenos");
        }else{
            c_oficina modificado;
            modificado=controller_->getOficinas().at(seleccionado);
            modificado.setOficina(ui->txtOficina->text().toStdString());
            modificado.setRazon(ui->txtRazon->text().toStdString());
            modificado.setNIF(ui->txtNIF->text().toStdString());
            modificado.setTlfn(ui->txtTlfn->text().toStdString());
            modificado.setDireccion(ui->txtDireccion->text().toStdString());
            modificado.setCP(ui->txtCP->text().toStdString());
            modificado.setPoblacion(ui->txtPoblacion->text().toStdString());
            modificado.setProvincia(ui->txtProvincia->text().toStdString());
            modificado.setPais(ui->txtPais->text().toStdString());
            modificado.setContinente(ui->txtContinente->text().toStdString());
            modificado.setObservaciones(ui->plaintxtObservaciones->toPlainText().toStdString());
            controller_->modificarOficina(seleccionado, modificado);

            this->inicial();

            ui->tableOficina->selectRow(fila);
        }
        break;
    }
    default:
        break;
    }
}

void gestionarOficina::cancelar(){
    this->inicial();
    this->limpiarLabel();
}
