#include "c_peticion.h"

QDateTime c_peticion::getPeticion() const
{
    return peticion_;
}

void c_peticion::setPeticion(const QDateTime &value)
{
    peticion_ = value;

}

int c_peticion::getPlazas() const
{
    return plazas_;
}

void c_peticion::setPlazas(int value)
{
    plazas_ = value;
}

std::string c_peticion::getContinente() const
{
    return continente_;
}

void c_peticion::setContinente(const std::string &value)
{
    continente_ = value;
}

std::string c_peticion::getPais() const
{
    return pais_;
}

void c_peticion::setPais(const std::string &value)
{
    pais_ = value;
}

std::string c_peticion::getOwner() const
{
    return owner_;
}

void c_peticion::setOwner(const std::string &value)
{
    owner_ = value;
}

std::string c_peticion::getOficina() const
{
    return oficina_;
}

void c_peticion::setOficina(const std::string &value)
{
    oficina_ = value;
}

std::string c_peticion::nego() const
{
    return nego_;
}

void c_peticion::setNego(const std::string &nego)
{
    nego_ = nego;
}

std::string c_peticion::getUsuario() const
{
    return usuario_;
}

void c_peticion::setUsuario(const std::string &value)
{
    usuario_ = value;
}

int c_peticion::ID() const
{
    return ID_;
}

void c_peticion::setID(int ID)
{
    ID_ = ID;
}

std::string c_peticion::aceptada() const
{
    return aceptada_;
}

void c_peticion::setAceptada(const std::string &aceptada)
{
    aceptada_ = aceptada;
}

void c_peticion::rellenarFila(QTableWidget *tabla, int pos){
    QDate fecha=peticion_.date();
    QTime hora=peticion_.time();
    QString date=fecha.toString("dd/MM/yyyy");
    QString time=hora.toString("hh:mm");

    tabla->setItem(pos,0,new QTableWidgetItem(QString::fromStdString(nego_)));
    tabla->setItem(pos,1,new QTableWidgetItem(QString::number(plazas_)));
    tabla->setItem(pos,2,new QTableWidgetItem(QString(date)));
    tabla->setItem(pos,3,new QTableWidgetItem(QString(time)));
    tabla->setItem(pos,4,new QTableWidgetItem(QString::number(ID_)));

    if (aceptada_=="Aceptada"){
        tabla->item(pos,0)->setBackgroundColor(QColor(0,255,60, 125));
        tabla->item(pos,1)->setBackgroundColor(QColor(0,255,60, 125));
        tabla->item(pos,2)->setBackgroundColor(QColor(0,255,60, 125));
        tabla->item(pos,3)->setBackgroundColor(QColor(0,255,60, 125));
    }else{
        tabla->item(pos,0)->setBackgroundColor(QColor(255,128,114,125));
        tabla->item(pos,1)->setBackgroundColor(QColor(255,128,114,125));
        tabla->item(pos,2)->setBackgroundColor(QColor(255,128,114,125));
        tabla->item(pos,3)->setBackgroundColor(QColor(255,128,114,125));
    }
}

void c_peticion::setHeader(QTableWidget *tabla){
    tabla->setColumnCount(5);
    tabla->hideColumn(4);
    tabla->setHorizontalHeaderLabels(QString("Origen - Destino;Plazas;Fecha;Hora").split(";"));
}

bool c_peticion::compare(NodoUnisys *criterio){
    bool mostrar=true;
    c_peticion* comparar=static_cast<c_peticion*>(criterio);

    QDateTime fechaNula;
    QDate date;
    date.setDate(1900,01,01);
    QTime time;
    time.setHMS(01,01,01);
    fechaNula.setDate(date);
    fechaNula.setTime(time);

    if (comparar->getOwner()!=owner_ && comparar->getOwner()!=" "){
        mostrar=false;
    }
    if(comparar->getOficina()!=oficina_ && comparar->getOficina()!=" "){
        mostrar=false;
    }
    if(comparar->getContinente()!=continente_ && comparar->getContinente()!=" "){
        mostrar=false;
    }
    if(comparar->getPais()!=pais_ && comparar->getPais()!=" "){
        mostrar=false;
    }
    if(comparar->getPeticion().date()!=fechaNula.date() && comparar->getPeticion().date()!=peticion_.date()){
        mostrar=false;
    }

    if(comparar->aceptada()!=aceptada() && comparar->aceptada()!=" "){
        mostrar=false;
    }
    return mostrar;
}

bool c_peticion::buscarID(int &ID){
    bool encontrado=false;
    if(this->ID()==ID){
        encontrado=true;
    }
    return encontrado;
}









c_peticion::c_peticion()
{
    
}

c_peticion::~c_peticion()
{
    
}

