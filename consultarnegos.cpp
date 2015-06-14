#include "ui_consultarnegos.h"

#include "consultarnegos.h"

//JL

consultarNegos::consultarNegos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consultarNegos)
{
    ui->setupUi(this);
}

consultarNegos::~consultarNegos()
{                                       //El destructor de esta ventana ejecuta la de Owner
    owner v3;
    v3.setController(*controller_);
    v3.exec();
    delete ui;
}

void consultarNegos::setController (MainController &controller){
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
    criterio.setID_owner(controller_->getUsers().at(controller_->getRegistrado()).ID_owner());
    criterio.setOrigen(" ");
    criterio.setPlazas(-1);
    criterio.setPorcentaje(0);
    criterio.setDis_fecha(0);

    this->showOrigen();
    this->showDestino();
}

void consultarNegos::inicial(){
    QDate local;
    dateLocal_.setDate(local.currentDate().year(), local.currentDate().month(), local.currentDate().day());

    this->showNegos();

    ui->mostrar->setEnabled(false);
    ui->dateFechaFilter->setEnabled(false);
    ui->checkFecha->setChecked(false);
    ui->labelFechaFilter->setEnabled(false);
    ui->tablaNegos->setEnabled(true);
    ui->dateFechaFilter->setDate(dateLocal_);
}

void consultarNegos::showOrigen(){
    int owner=controller_->getUsers().at(controller_->getRegistrado()).ID_owner();
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

void consultarNegos::showDestino(){
    int owner=controller_->getUsers().at(controller_->getRegistrado()).ID_owner();
    buscarDestino.clear();
    ui->comboDestinoFilter->clear();
    ui->comboDestinoFilter->addItem(" ");
    for (size_t i=0; i<controller_->getNegos().count(); i++){
        if(controller_->getNegos().at(i).borrado()!=1 && controller_->getNegos().at(i).ID_owner()==owner){
            bool encontrado=false;
            for (int j=0; j<ui->comboDestinoFilter->count(); j++){          //Comprueba si el destino se ha mostrado ya para no mostrar el mismo destino varias veces.
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

void consultarNegos::showLabel(){
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
}

void consultarNegos::showNegos(){
    rellenarTabla(controller_->getNegos(),ui->tablaNegos, &criterio);
}

void consultarNegos::selectedOrigen(){
    std::string origen=ui->comboOrigenFilter->currentText().toStdString();
    criterio.setOrigen(origen);

    this->showNegos();
}

void consultarNegos::selectedDestino(){
    std::string destino=ui->comboDestinoFilter->currentText().toStdString();
    criterio.setDestino(destino);

    this->showNegos();
}

void consultarNegos::selectedFecha(){
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
}

