#include "ui_historial.h"

#include <QDebug>

#include "historial.h"

historial::historial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::historial)
{
    ui->setupUi(this);
}

historial::~historial()
{
    compania v2;
    v2.setController(*controller_);
    v2.exec();
    delete ui;
}

void historial::setController(MainController &controller){
    controller_=&controller;
    inicial();
}

void historial::inicial(){
    QDateTime fecha;
    QDate date;
    date.setDate(1900,01,01);
    QTime time;
    time.setHMS(01,01,01);
    fecha.setDate(date);
    fecha.setTime(time);

    criterio.setContinente(" ");
    criterio.setOrigen(" ");
    criterio.setDestino(" ");
    criterio.setOficina(" ");
    criterio.setOwner(" ");
    criterio.setPais(" ");
    criterio.setPeticion(fecha);

    QDate local;
    local.setDate(local.currentDate().year(), local.currentDate().month(), local.currentDate().day());
    ui->dateFechaFilter->setDate(local);

    showPeticiones();
    showOwner();
    showOficina();
    showContinente();
    showPais();
    showEstados();

    ui->labels->setEnabled(false);
}

void historial::showPeticiones(){
    this->limpiarLabel();

    std::string owner=ui->comboOwnerFilter->currentText().toStdString();
    criterio.setOwner(owner);
    std::string oficina=ui->comboOficinaFilter->currentText().toStdString();
    criterio.setOficina(oficina);
    std::string continente=ui->comboContinenteFilter->currentText().toStdString();
    criterio.setContinente(continente);
    std::string pais=ui->comboPais->currentText().toStdString();
    criterio.setPais(pais);
    std::string estado=ui->comboEstado->currentText().toStdString();
    qDebug()<<"current estado" << ui->comboEstado->currentText();
    criterio.setAceptada(estado);

    bool fechaActivada=false;
    fechaActivada=ui->checkFecha->checkState();

    QTime time;
    time.setHMS(01,01,01);
    QDateTime fecha;

    if(fechaActivada==true){
        ui->dateFechaFilter->setEnabled(true);
        ui->labelFechaFilter->setEnabled(true);

        QDate date;
        date=ui->dateFechaFilter->date();

        fecha.setDate(date);
        fecha.setTime(time);
        criterio.setPeticion(fecha);
    }else{
        ui->dateFechaFilter->setEnabled(false);
        ui->labelFechaFilter->setEnabled(false);

        QDate date;
        date.setDate(1900,01,01);

        fecha.setDate(date);
        fecha.setTime(time);
        criterio.setPeticion(fecha);
    }

    rellenarTabla(controller_->getPeticiones(), ui->tablePeticiones, &criterio);
}

void historial::showOwner(){
    ui->comboOwnerFilter->clear();
    ui->comboOwnerFilter->addItem(" ");
    for (size_t i=0; i<controller_->getPeticiones().count(); i++){
        bool encontrado=false;
        for (int j=0; j<ui->comboOwnerFilter->count(); j++){
            std::string owner=controller_->getPeticiones().at(i).getOwner();
            std::string comboOwner=ui->comboOwnerFilter->itemText(j).toStdString();
            if(owner==comboOwner){
                encontrado=true;
            }
        }
        if(encontrado==false){
            ui->comboOwnerFilter->addItem(QString::fromStdString(controller_->getPeticiones().at(i).getOwner()));
            encontrado=true;
        }
    }
}

void historial::showOficina(){
    ui->comboOficinaFilter->clear();
    ui->comboOficinaFilter->addItem(" ");
    for (size_t i=0; i<controller_->getPeticiones().count(); i++){
        bool encontrado=false;
        for (int j=0; j<ui->comboOficinaFilter->count(); j++){
            std::string oficina=controller_->getPeticiones().at(i).getOficina();
            std::string comboOficina=ui->comboOficinaFilter->itemText(j).toStdString();
            if(oficina==comboOficina){
                encontrado=true;
            }
        }
        if(encontrado==false){
            ui->comboOficinaFilter->addItem(QString::fromStdString(controller_->getPeticiones().at(i).getOficina()));
            encontrado=true;
        }
    }
}

void historial::showContinente(){
    ui->comboContinenteFilter->clear();
    ui->comboContinenteFilter->addItem(" ");
    for (size_t i=0; i<controller_->getPeticiones().count(); i++){
        bool encontrado=false;
        for (int j=0; j<ui->comboContinenteFilter->count(); j++){
            std::string continente=controller_->getPeticiones().at(i).getContinente();
            std::string comboContinente=ui->comboContinenteFilter->itemText(j).toStdString();
            if(continente==comboContinente){
                encontrado=true;
            }
        }
        if(encontrado==false){
            ui->comboContinenteFilter->addItem(QString::fromStdString(controller_->getPeticiones().at(i).getContinente()));
            encontrado=true;
        }
    }
}

void historial::showPais(){
    ui->comboPais->clear();
    ui->comboPais->addItem(" ");
    for (size_t i=0; i<controller_->getPeticiones().count(); i++){
        bool encontrado=false;
        for (int j=0; j<ui->comboPais->count(); j++){
            std::string pais=controller_->getPeticiones().at(i).getPais();
            std::string comboPais=ui->comboPais->itemText(j).toStdString();
            if(pais==comboPais){
                encontrado=true;
            }
        }
        if(encontrado==false){
            ui->comboPais->addItem(QString::fromStdString(controller_->getPeticiones().at(i).getPais()));
            encontrado=true;
        }
    }
}

void historial::showEstados(){
    ui->comboEstado->clear();
    ui->comboEstado->addItem(" ");
    ui->comboEstado->addItem("Aceptada");
    ui->comboEstado->addItem("Denegada");
}

void historial::showLabel(){
    QString ID = ui->tablePeticiones->item(ui->tablePeticiones->currentRow(), 4)->text();
    int seleccionado = ID.toInt();
    encontrarID(controller_->getPeticiones(), &seleccionado);

    QString nego = QString::fromStdString(controller_->getPeticiones().at(seleccionado).origen() + " - " + controller_->getPeticiones().at(seleccionado).destino());

    ui->txtUsuario->setText(QString::fromStdString(controller_->getPeticiones().at(seleccionado).getUsuario()));
    ui->txtPais->setText(QString::fromStdString(controller_->getPeticiones().at(seleccionado).getPais()));
    ui->txtOwner->setText(QString::fromStdString(controller_->getPeticiones().at(seleccionado).getOwner()));
    ui->txtNego->setText(QString(nego));
    ui->txtContinente->setText(QString::fromStdString(controller_->getPeticiones().at(seleccionado).getContinente()));
    ui->date->setDate(QDate(controller_->getPeticiones().at(seleccionado).getPeticion().date()));
    ui->time->setTime(QTime(controller_->getPeticiones().at(seleccionado).getPeticion().time()));
    ui->spinPlazas->setValue(controller_->getPeticiones().at(seleccionado).getPlazas());
    ui->txtOficina->setText(QString::fromStdString(controller_->getPeticiones().at(seleccionado).getOficina()));

    if(controller_->getPeticiones().at(seleccionado).aceptada()=="Aceptada"){
        ui->labelEstado->setText("ACEPTADA");
        QPalette *palette= new QPalette();
        palette->setColor(QPalette::WindowText,Qt::green);
        ui->labelEstado->setPalette(*palette);
    }else{
        ui->labelEstado->setText("DENEGADA");
        QPalette *palette= new QPalette();
        palette->setColor(QPalette::WindowText,Qt::red);
        ui->labelEstado->setPalette(*palette);
    }
}

void historial::limpiarLabel(){
    ui->txtUsuario->clear();
    ui->txtPais->clear();
    ui->txtOwner->clear();
    ui->txtNego->clear();
    ui->txtContinente->clear();
    QDate local;
    local.setDate(local.currentDate().year(), local.currentDate().month(), local.currentDate().day());
    QTime hora;
    hora.currentTime();
    ui->date->setDate(QDate(local));
    ui->time->setTime(QTime(hora));
    ui->spinPlazas->cleanText();
    ui->txtOficina->clear();
    ui->labelEstado->clear();
}
