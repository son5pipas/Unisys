#include "ui_oficina.h"

#include <QMessageBox>

#include "oficina.h"

// Sergio

oficina::oficina(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::oficina)
{
    ui->setupUi(this);
}

oficina::~oficina()
{
    if(controller_->getSuperUser()==true){
        selectUserLogin v1;
        v1.setController(*controller_);
        v1.exec();
    }
    delete ui;
}

void oficina::setController (MainController &controller){
    controller_=&controller;
    this-> inicial();

    QDate date;
    date.setDate(1900,01,01);
    QTime time;
    time.setHMS(01,01,01);

    criterio.setBorrado(false);
    criterio.setDestino(" ");
    criterio.setDisminuido(false);
    criterio.setFecha(date,time);
    criterio.setID(controller_->getUsers().at(controller_->getRegistrado()).ID_oficina());
    criterio.setID_owner(controller_->getUsers().at(controller_->getRegistrado()).ID_owner());
    criterio.setOrigen(" ");
    criterio.setPlazas(0);
    criterio.setPorcentaje(0);
    criterio.setDis_fecha(0);

    this->showOrigen();
    this->showDestino();
}

void oficina::inicial(){
    QDate local;
    dateLocal_.setDate(local.currentDate().year(), local.currentDate().month(), local.currentDate().day());

    this->showNegos();

    ui->reservas->setEnabled(false);
    ui->dateFechaFilter->setEnabled(false);
    ui->checkFecha->setChecked(false);
    ui->labelFechaFilter->setEnabled(false);
    ui->tablaNegos->setEnabled(true);
    ui->dateFechaFilter->setDate(dateLocal_);
    ui->labelEstado->clear();
    ui->spinPlazas->setValue(0);
}

void oficina::showOrigen(){
    int owner=controller_->getUsers().at(controller_->getRegistrado()).ID_owner();
    buscarOrigen.clear();
    ui->comboOrigenFilter->clear();
    ui->comboOrigenFilter->addItem(" ");
    for (size_t i=0; i<controller_->getNegos().count(); i++){
        if(controller_->getNegos().at(i).borrado()!=1 && controller_->getNegos().at(i).ID_owner()==owner){
            bool encontrado=false;
            for (int j=0; j<ui->comboOrigenFilter->count(); j++){
                std::string origen=controller_->getNegos().at(i).origen();
                std::string comboOrigen=ui->comboOrigenFilter->itemText(j).toStdString();
                if(origen==comboOrigen){
                    encontrado=true;
                }
            }
            if(encontrado==false){
                ui->comboOrigenFilter->addItem(QString::fromStdString(controller_->getNegos().at(i).origen()));
                buscarOrigen.append(i);
                encontrado=true;
            }
        }
    }
}

void oficina::showDestino(){
    int owner=controller_->getUsers().at(controller_->getRegistrado()).ID_owner();
    buscarDestino.clear();
    ui->comboDestinoFilter->clear();
    ui->comboDestinoFilter->addItem(" ");
    for (size_t i=0; i<controller_->getNegos().count(); i++){
        if(controller_->getNegos().at(i).borrado()!=1 && controller_->getNegos().at(i).ID_owner()==owner){
            bool encontrado=false;
            for (int j=0; j<ui->comboDestinoFilter->count(); j++){
                std::string destino=controller_->getNegos().at(i).destino();
                std::string comboDestino=ui->comboDestinoFilter->itemText(j).toStdString();
                if(destino==comboDestino){
                    encontrado=true;
                }
            }
            if(encontrado==false){
                ui->comboDestinoFilter->addItem(QString::fromStdString(controller_->getNegos().at(i).destino()));
                buscarDestino.append(i);
                encontrado=true;
            }
        }
    }
}

void oficina::showNegos(){
    std::string origen=ui->comboOrigenFilter->currentText().toStdString();
    criterio.setOrigen(origen);
    std::string destino=ui->comboDestinoFilter->currentText().toStdString();
    criterio.setDestino(destino);
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

    rellenarTabla(controller_->getNegos(), ui->tablaNegos, &criterio);
}

void oficina::activarReservas(){
    ui->reservas->setEnabled(true);
    ui->labelEstado->clear();
}

void oficina::reservar(){
    QString ID = ui->tablaNegos->item(ui->tablaNegos->currentRow(), 5)->text();
    int seleccionado = ID.toInt();
    encontrarID(controller_->getNegos(), &seleccionado);
    int plazas = ui->spinPlazas->value();

    if(plazas==0){
        QMessageBox::information(this, "", "Se debe seleccionar al menos 1 plaza.");
    }else{
        QMessageBox::StandardButton reservas;
        reservas = QMessageBox::question(this, "", "¿Quiere reservar " + QString::number(plazas) + " plazas, para el vuelo: " + QString::fromStdString(controller_->getNegos().at(seleccionado).origen()) + " - " + QString::fromStdString(controller_->getNegos().at(seleccionado).destino()), QMessageBox::Yes | QMessageBox:: No);
        if(reservas == QMessageBox::Yes){
            bool aceptada=controller_->restarPlazas(seleccionado, plazas);
            if(aceptada==true){
                this->inicial();
                ui->labelEstado->setText("SOLICITUD ACEPTADA");
                QPalette *palette= new QPalette();
                palette->setColor(QPalette::WindowText,Qt::green);
                ui->labelEstado->setPalette(*palette);
                QMessageBox::information(this, "", "Se han reservado " + QString::number(plazas) + " plazas, para el vuelo: " + QString::fromStdString(controller_->getNegos().at(seleccionado).origen()) + " - " + QString::fromStdString(controller_->getNegos().at(seleccionado).destino()));
            }else{
                this->inicial();
                ui->labelEstado->setText("SOLICITUD DENEGADA");
                QPalette *palette= new QPalette();
                palette->setColor(QPalette::WindowText,Qt::red);
                ui->labelEstado->setPalette(*palette);
                QMessageBox::information(this, "", "¡SOLICITUD DENEGADA!   No se dispone de " + QString::number(plazas) + " plazas, sólo hay disponibles " + QString::number(controller_->getNegos().at(seleccionado).plazas()) + " para el vuelo: " + QString::fromStdString(controller_->getNegos().at(seleccionado).origen()) + " - " + QString::fromStdString(controller_->getNegos().at(seleccionado).destino()));
            }
        }else if(reservas == QMessageBox::No){
            this->inicial();
        }
    }
}
