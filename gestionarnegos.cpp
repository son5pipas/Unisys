#include "ui_gestionarnegos.h"

#include <string>
#include <qmessagebox.h>
#include <QDebug>

#include "gestionarnegos.h"

//JL

gestionarNegos::gestionarNegos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestionarNegos)
{
    ui->setupUi(this);
}

gestionarNegos::~gestionarNegos()
{                                       //El destructor de esta ventana ejecuta la de Compania
    compania v2;
    v2.setController(*controller_);
    v2.exec();
    delete ui;
}

void gestionarNegos::setController (MainController &controller){
    controller_=&controller;

    this-> inicial();

    QDate date;                         //Establece los valores iniciales de filtrado en el Nego criterio.
    date.setDate(1900,01,01);
    QTime time;
    time.setHMS(01,01,01);

    criterio.setBorrado(false);
    criterio.setDestino(" ");
    criterio.setDisminuido(false);
    criterio.setFecha(date,time);
    criterio.setID(0);
    criterio.setID_owner(-1);
    criterio.setOrigen(" ");
    criterio.setPlazas(-1);
    criterio.setPorcentaje(0);
    criterio.setDis_fecha(0);

    this->showOwner();
    this->showOrigen();
    this->showDestino();
}

void gestionarNegos::inicial(){
    QDate local;
    dateLocal_.setDate(local.currentDate().year(), local.currentDate().month(), local.currentDate().day());

    this->showNegos();

    ui->filtrado->setEnabled(true);
    ui->dateFechaFilter->setEnabled(false);
    ui->checkFecha->setChecked(false);
    ui->labelFechaFilter->setEnabled(false);
    ui->tablaNegos->setEnabled(true);
    ui->editNegos->setEnabled(false);
    ui->dateFechaFilter->setDate(dateLocal_);
    ui->btnAcpetar->setEnabled(false);
    ui->btnCancelar->setEnabled(false);
    ui->btnModificar->setEnabled(false);
    ui->btnBorrar->setEnabled(false);
    ui->btnNuevo->setEnabled(false);

    ui->comboOrigenFilter->setCurrentIndex(0);
    ui->comboDestinoFilter->setCurrentIndex(0);
    this->selectedOwner();
}

void gestionarNegos::limpiarLabel(){
    ui->txtOrigen->clear();
    ui->txtDestino->clear();
    ui->dateDis->clear();
    ui->dateVuelo->setDate(dateLocal_);
    ui->plazas->setValue(0);
    ui->porcentaje->setValue(0);
    ui->timeVuelo->setTime(QTime(0,0));
}

void gestionarNegos::showOwner(){
    buscarOwner.clear();
    ui->comboOwnerFilter->clear();
    ui->comboOwnerFilter->addItem(" ");
    for (size_t i=0; i<controller_->getOwners().count(); i++){
        if(controller_->getOwners().at(i).borrado()!=1){
            ui->comboOwnerFilter->addItem(QString::fromStdString(controller_->getOwners().at(i).owner()));
            buscarOwner.append(controller_->getOwners().at(i).ID());
        }
    }
}

void gestionarNegos::showOrigen(){
    int iowner=ui->comboOwnerFilter->currentIndex();
    int owner=0;
    if (buscarOwner.empty()!=true && iowner>0){
        owner=buscarOwner.at(iowner-1);
    };
    buscarOrigen.clear();
    ui->comboOrigenFilter->clear();
    ui->comboOrigenFilter->addItem(" ");
    for (size_t i=0; i<controller_->getNegos().count(); i++){
        if(controller_->getNegos().at(i).borrado()!=1 && controller_->getNegos().at(i).ID_owner()==owner){
            bool encontrado=false;
            for (int j=0; j<ui->comboOrigenFilter->count(); j++){           //Comprueba si el origen se ha mostrado ya para no mostrar el mismo origen varias veces.
                std::string origen=controller_->getNegos().at(i).origen();
                std::string comboOrigen=ui->comboOrigenFilter->itemText(j).toStdString();
                if(origen==comboOrigen){
                    encontrado=true;
                }
            }
            if(encontrado==false){                                          //Si no se ha mostrado el orgien, se muestra.
                ui->comboOrigenFilter->addItem(QString::fromStdString(controller_->getNegos().at(i).origen()));
                buscarOrigen.append(i);
                encontrado=true;
            }
        }
    }
}

void gestionarNegos::showDestino(){
    int iowner=ui->comboOwnerFilter->currentIndex();
    int owner=0;
    if (buscarOwner.empty()!=true && iowner>0){
        owner=buscarOwner.at(iowner-1);
    };
    buscarDestino.clear();
    ui->comboDestinoFilter->clear();
    ui->comboDestinoFilter->addItem(" ");
    for (size_t i=0; i<controller_->getNegos().count(); i++){
        if(controller_->getNegos().at(i).borrado()!=1 && controller_->getNegos().at(i).ID_owner()==owner){
            bool encontrado=false;                                          //Comprueba si el destino se ha mostrado ya para no mostrar el mismo destino varias veces.
            for (int j=0; j<ui->comboDestinoFilter->count(); j++){
                std::string destino=controller_->getNegos().at(i).destino();
                std::string comboDestino=ui->comboDestinoFilter->itemText(j).toStdString();
                if(destino==comboDestino){
                    encontrado=true;
                }
            }
            if(encontrado==false){                                          //Si no se ha mostrado el destino, se muestra.
                ui->comboDestinoFilter->addItem(QString::fromStdString(controller_->getNegos().at(i).destino()));
                buscarDestino.append(i);
                encontrado=true;
            }
        }
    }
}

void gestionarNegos::showNegos(){
    rellenarTabla(controller_->getNegos(), ui->tablaNegos, &criterio);
}

void gestionarNegos::selectedOwner(){
    int owner, iowner=ui->comboOwnerFilter->currentIndex();
    if (buscarOwner.empty()!=true && iowner>0){
        owner=buscarOwner.at(iowner-1);
        ui->btnNuevo->setEnabled(true);
        criterio.setID_owner(owner);
    }else{
        criterio.setID_owner(-1);
        ui->btnNuevo->setEnabled(false);
        ui->btnModificar->setEnabled(false);
        ui->btnBorrar->setEnabled(false);
        ui->btnAcpetar->setEnabled(false);
        ui->btnCancelar->setEnabled(false);
    }

    this->showOrigen();
    this->showDestino();
    this->showNegos();  
    this->limpiarLabel();
}

void gestionarNegos::selectedOrigen(){
    std::string origen=ui->comboOrigenFilter->currentText().toStdString();
    criterio.setOrigen(origen);

    this->showNegos();
    this->limpiarLabel();
    ui->btnModificar->setEnabled(false);
    ui->btnBorrar->setEnabled(false);
    ui->btnAcpetar->setEnabled(false);
    ui->btnCancelar->setEnabled(false);
}

void gestionarNegos::selectedDestino(){
    std::string destino=ui->comboDestinoFilter->currentText().toStdString();
    criterio.setDestino(destino);

    this->showNegos();
    this->limpiarLabel();
    ui->btnModificar->setEnabled(false);
    ui->btnBorrar->setEnabled(false);
    ui->btnAcpetar->setEnabled(false);
    ui->btnCancelar->setEnabled(false);
}

void gestionarNegos::selectedFecha(){
    bool fechaActivada=false;
    fechaActivada=ui->checkFecha->checkState();

    QTime time;
    time.setHMS(01,01,01);

    if(fechaActivada==true){
        ui->dateFechaFilter->setEnabled(true);
        ui->labelFechaFilter->setEnabled(true);

        QDate fecha;
        fecha=ui->dateFechaFilter->date();

        criterio.setFecha(fecha, time);
    }else{
        ui->dateFechaFilter->setEnabled(false);
        ui->labelFechaFilter->setEnabled(false);

        QDate date;
        date.setDate(1900,01,01);

        criterio.setFecha(date,time);
    }

    this->showNegos();
    this->limpiarLabel();
    ui->btnModificar->setEnabled(false);
    ui->btnBorrar->setEnabled(false);
    ui->btnAcpetar->setEnabled(false);
    ui->btnCancelar->setEnabled(false);
}

void gestionarNegos::showLabel(){
    QString ID = ui->tablaNegos->item(ui->tablaNegos->currentRow(),5)->text();
    int seleccionado = ID.toInt();
    encontrarID(controller_->getNegos(), &seleccionado);

    ui->txtOrigen->setText(QString::fromStdString(controller_->getNegos().at(seleccionado).origen()));
    ui->txtDestino->setText(QString::fromStdString(controller_->getNegos().at(seleccionado).destino()));
    ui->dateVuelo->setDate(QDate(controller_->getNegos().at(seleccionado).fecha().date()));
    ui->timeVuelo->setTime(QTime(controller_->getNegos().at(seleccionado).fecha().time()));
    ui->plazas->setValue(controller_->getNegos().at(seleccionado).plazas());
    ui->dateDis->setValue(controller_->getNegos().at(seleccionado).dis_fecha());
    ui->porcentaje->setValue(controller_->getNegos().at(seleccionado).porcentaje());

    ui->btnModificar->setEnabled(true);
    ui->btnBorrar->setEnabled(true);
}

void gestionarNegos::nuevo(){
    opcion=1;
    ui->editNegos->setEnabled(true);
    ui->filtrado->setEnabled(false);
    ui->tablaNegos->clearSelection();
    ui->tablaNegos->setEnabled(false);
    ui->btnModificar->setEnabled(false);
    ui->btnBorrar->setEnabled(false);
    ui->btnAcpetar->setEnabled(true);
    ui->btnCancelar->setEnabled(true);
    ui->btnNuevo->setEnabled(false);

    this->limpiarLabel();

    ui->txtOrigen->setFocus();
}

void gestionarNegos::modificar(){

    QModelIndexList selectedList = ui->tablaNegos->selectionModel()->selectedRows();
    if (!selectedList.empty()){
        opcion=2;
        ui->editNegos->setEnabled(true);
        ui->tablaNegos->setEnabled(false);
        ui->filtrado->setEnabled(false);
        ui->txtOrigen->setFocus();
        ui->btnAcpetar->setEnabled(true);
        ui->btnCancelar->setEnabled(true);
        ui->btnModificar->setEnabled(false);
        ui->btnBorrar->setEnabled(false);
        ui->btnNuevo->setEnabled(false);
    }
}

void gestionarNegos::borrar(){
    QString ID = ui->tablaNegos->item(ui->tablaNegos->currentRow(),5)->text();
    int seleccionado = ID.toInt();
    encontrarID(controller_->getNegos(), &seleccionado);

    ui->editNegos->setEnabled(false);
    ui->tablaNegos->setEnabled(false);
    ui->filtrado->setEnabled(false);
    ui->btnAcpetar->setEnabled(false);
    ui->btnCancelar->setEnabled(false);
    ui->btnModificar->setEnabled(false);
    ui->btnBorrar->setEnabled(false);
    ui->btnNuevo->setEnabled(false);
    QMessageBox::StandardButton QbtnBorrar;
    QbtnBorrar = QMessageBox::question(this, "", "Está seguro que desea eliminar el nego: " + QString::fromStdString(controller_->getNegos().at(seleccionado).origen()) + " - " + QString::fromStdString(controller_->getNegos().at(seleccionado).destino()), QMessageBox::Yes | QMessageBox:: No);
    if(QbtnBorrar == QMessageBox::Yes){
        c_nego copyNegos = controller_->getNegos().at(seleccionado);
        copyNegos.setBorrado(true);
        controller_->modificarNego(seleccionado, copyNegos);
        this->inicial();
        this->limpiarLabel();
    }else if(QbtnBorrar == QMessageBox::No){
        this->inicial();
        this->limpiarLabel();
    }
}

void gestionarNegos::aceptar(){
    switch (opcion) {
    case 1:{
        if(ui->txtOrigen->text().isEmpty() || ui->txtDestino->text().isEmpty() || ui->dateVuelo->date()<=dateLocal_ || dateLocal_.toJulianDay()>=ui->dateVuelo->date().toJulianDay()-ui->dateDis->value()){
            QMessageBox::information(this, "", "Debe rellenar todos los campos");
        }else{
            c_nego nuevo;

            controller_->setUltimoIDnegos();
            int owner, iowner = ui->comboOwnerFilter->currentIndex();
            owner=buscarOwner.at(iowner-1);

            nuevo.setID(controller_->getUltimoIDnegos());
            nuevo.setBorrado(false);
            nuevo.setID_owner(owner);
            nuevo.setOrigen(ui->txtOrigen->text().toStdString());
            nuevo.setDestino(ui->txtDestino->text().toStdString());
            nuevo.setFecha(ui->dateVuelo->date(),ui->timeVuelo->time());
            nuevo.setDisminuido(false);
            nuevo.setDis_fecha(ui->dateDis->value());
            nuevo.setPlazas(ui->plazas->value());
            nuevo.setPorcentaje(ui->porcentaje->value());

            controller_->setNegos(nuevo);

            this->inicial();
            this->showNegos();
            ui->tablaNegos->selectRow(ui->tablaNegos->rowCount()-1);
        }
        break;
    }
    case 2:{
        QString ID = ui->tablaNegos->item(ui->tablaNegos->currentRow(),5)->text();
        int seleccionado = ID.toInt();
        encontrarID(controller_->getNegos(), &seleccionado);
        int fila=ui->tablaNegos->currentRow();

        if(ui->txtOrigen->text().isEmpty() || ui->txtDestino->text().isEmpty() || ui->dateVuelo->date()<=dateLocal_ || dateLocal_.toJulianDay()>=ui->dateVuelo->date().toJulianDay()-ui->dateDis->value()){
            QMessageBox::information(this, "", "Todos los campos deben estár rellenos");
        }else{
            c_nego modificado;
            modificado=controller_->getNegos().at(seleccionado);
            modificado.setOrigen(ui->txtOrigen->text().toStdString());
            modificado.setDestino(ui->txtDestino->text().toStdString());
            modificado.setFecha(ui->dateVuelo->date(),ui->timeVuelo->time());
            modificado.setDisminuido(false);
            modificado.setDis_fecha(ui->dateDis->value());
            modificado.setPlazas(ui->plazas->value());
            modificado.setPorcentaje(ui->porcentaje->value());
            controller_->modificarNego(seleccionado, modificado);

            this->inicial();
            ui->tablaNegos->selectRow(fila);
        }
        break;
    }
    default:
        break;
    }
}

void gestionarNegos::cancelar(){
    this->inicial();
    this->limpiarLabel();
}
