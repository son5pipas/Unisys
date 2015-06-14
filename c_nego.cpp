#include "c_nego.h"


long c_nego::ID() const
{
    return ID_;
}

void c_nego::setID(long ID)
{
    ID_ = ID;
}

int c_nego::ID_owner() const
{
    return ID_owner_;
}

void c_nego::setID_owner(int ID_owner)
{
    ID_owner_ = ID_owner;
}

int c_nego::plazas() const
{
    return plazas_;
}

void c_nego::setPlazas(int plazas)
{
    plazas_ = plazas;
}

int c_nego::porcentaje() const
{
    return porcentaje_;
}

void c_nego::setPorcentaje(int porcentaje)
{
    porcentaje_ = porcentaje;
}

bool c_nego::borrado() const
{
    return borrado_;
}

void c_nego::setBorrado(bool borrado)
{
    borrado_ = borrado;
}

bool c_nego::disminuido() const
{
    return disminuido_;
}

void c_nego::setDisminuido(bool disminuido)
{
    disminuido_ = disminuido;
}

std::string c_nego::origen() const
{
    return origen_;
}

void c_nego::setOrigen(const std::string &origen)
{
    origen_ = origen;
}

std::string c_nego::destino() const
{
    return destino_;
}

void c_nego::setDestino(const std::string &destino)
{
    destino_ = destino;
}

QDateTime c_nego::fecha() const
{
    return fecha_;
}

void c_nego::setFecha(const QDate &fecha, const QTime &time)
{
    QDateTime nuevo;
    nuevo.setDate(fecha);
    nuevo.setTime(time);
    fecha_ = nuevo;
}

int c_nego::dis_fecha() const
{
    return dis_fecha_;
}

void c_nego::setDis_fecha(int dis_fecha)
{
    dis_fecha_ = dis_fecha;
}

c_nego::c_nego()
{

}

c_nego::c_nego(int ID, int ID_owner, int plazas, int porcentaje, std::string origen, std::string destino,
               QDateTime fecha, int dis_fecha) :
               ID_(ID), ID_owner_(ID_owner), plazas_(plazas), porcentaje_(porcentaje), borrado_(false), disminuido_(false),
               origen_(origen), destino_(destino), fecha_(fecha), dis_fecha_(dis_fecha){

}

c_nego::~c_nego()
{

}

void c_nego::rellenarFila(QTableWidget *tabla, int pos){
    QDate fecha=fecha_.date();
    QTime hora=fecha_.time();
    QString date=fecha.toString("dd/MM/yyyy");
    QString time=hora.toString("hh:mm");

    tabla->setItem(pos,0,new QTableWidgetItem(QString::fromStdString(origen())));
    tabla->setItem(pos,1,new QTableWidgetItem(QString::fromStdString(destino())));
    tabla->setItem(pos,2,new QTableWidgetItem(QString(date)));
    tabla->setItem(pos,3,new QTableWidgetItem(QString(time)));
    tabla->setItem(pos,4,new QTableWidgetItem(QString::number(plazas())));
    tabla->setItem(pos,5,new QTableWidgetItem(QString::number(ID())));

    if (disminuido_==true){
        tabla->item(pos,0)->setBackgroundColor(QColor(240,230,140, 125));
        tabla->item(pos,1)->setBackgroundColor(QColor(240,230,140, 125));
        tabla->item(pos,2)->setBackgroundColor(QColor(240,230,140, 125));
        tabla->item(pos,3)->setBackgroundColor(QColor(240,230,140, 125));
        tabla->item(pos,4)->setBackgroundColor(QColor(240,230,140, 125));
    }
    if (plazas_==0){
        tabla->item(pos,0)->setBackgroundColor(QColor(255,128,114,125));
        tabla->item(pos,1)->setBackgroundColor(QColor(255,128,114,125));
        tabla->item(pos,2)->setBackgroundColor(QColor(255,128,114,125));
        tabla->item(pos,3)->setBackgroundColor(QColor(255,128,114,125));
        tabla->item(pos,4)->setBackgroundColor(QColor(255,128,114,125));
    }
}

void c_nego::setHeader(QTableWidget *tabla){
    tabla->setColumnCount(6);
    tabla->hideColumn(5);
    tabla->setHorizontalHeaderLabels(QString("Origen;Destino;Fecha;Hora;Plazas").split(";"));
}

bool c_nego::compare(NodoUnisys *criterio){
    bool mostrar=true;
    c_nego* comparar=static_cast<c_nego*>(criterio);

    QDateTime fechaNula;
    QDate date;
    date.setDate(1900,01,01);
    QTime time;
    time.setHMS(01,01,01);
    fechaNula.setDate(date);
    fechaNula.setTime(time);

    if (comparar->ID_owner()!=-1){
        if (borrado_==true){
            mostrar=false;
        }
        if(ID_owner_!=comparar->ID_owner()){
            mostrar=false;
        }
        if (comparar->origen()!=" " && origen_!=comparar->origen()){
            mostrar=false;
        }

        if (comparar->destino()!=" " && destino_!=comparar->destino()){
            mostrar=false;
        }
        if (comparar->fecha().date()!=fechaNula.date() && fecha_.date()!=comparar->fecha().date()){
            mostrar=false;
        }
        if (comparar->plazas()==0 && this->plazas()==0){
            mostrar=false;
        }
    }else{
        mostrar=false;
    }

    return mostrar;
}

bool c_nego::buscarID(int &ID){
    bool encontrado=false;
    if(this->ID()==ID){
        encontrado=true;
    }
    return encontrado;
}
