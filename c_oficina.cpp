#include "c_oficina.h"


int c_oficina::ID() const
{
    return ID_;
}

void c_oficina::setID(int ID)
{
    ID_ = ID;
}

int c_oficina::ID_owner() const
{
    return ID_owner_;
}

void c_oficina::setID_owner(int ID_owner)
{
    ID_owner_ = ID_owner;
}

bool c_oficina::borrado() const
{
    return borrado_;
}

void c_oficina::setBorrado(bool borrado)
{
    borrado_ = borrado;
}

std::string c_oficina::oficina() const
{
    return oficina_;
}

void c_oficina::setOficina(const std::string &oficina)
{
    oficina_ = oficina;
}

std::string c_oficina::razon() const
{
    return razon_;
}

void c_oficina::setRazon(const std::string &razon)
{
    razon_ = razon;
}

std::string c_oficina::NIF() const
{
    return NIF_;
}

void c_oficina::setNIF(const std::string &NIF)
{
    NIF_ = NIF;
}

std::string c_oficina::tlfn() const
{
    return tlfn_;
}

void c_oficina::setTlfn(const std::string &tlfn)
{
    tlfn_ = tlfn;
}

std::string c_oficina::direccion() const
{
    return direccion_;
}

void c_oficina::setDireccion(const std::string &direccion)
{
    direccion_ = direccion;
}

std::string c_oficina::CP() const
{
    return CP_;
}

void c_oficina::setCP(const std::string &CP)
{
    CP_ = CP;
}

std::string c_oficina::poblacion() const
{
    return poblacion_;
}

void c_oficina::setPoblacion(const std::string &poblacion)
{
    poblacion_ = poblacion;
}

std::string c_oficina::provincia() const
{
    return provincia_;
}

void c_oficina::setProvincia(const std::string &provincia)
{
    provincia_ = provincia;
}

std::string c_oficina::pais() const
{
    return pais_;
}

void c_oficina::setPais(const std::string &pais)
{
    pais_ = pais;
}

std::string c_oficina::continente() const
{
    return continente_;
}

void c_oficina::setContinente(const std::string &continente)
{
    continente_ = continente;
}

std::string c_oficina::observaciones() const
{
    return observaciones_;
}

void c_oficina::setObservaciones(const std::string &observaciones)
{
    observaciones_ = observaciones;
}


c_oficina::c_oficina ()
{

}

c_oficina::c_oficina(int ID, int ID_owner, std::string oficina, std::string razon, std::string NIF, std::string tlfn,
                     std::string direccion, std::string CP, std::string poblacion, std::string provincia,
                     std::string pais, std::string continente, std::string observaciones) :
                     ID_(ID), ID_owner_(ID_owner), borrado_(false), oficina_(oficina), razon_(razon), NIF_(NIF), tlfn_(tlfn),
                     direccion_(direccion), CP_(CP), poblacion_(poblacion), provincia_(provincia),
                     pais_(pais), continente_(continente), observaciones_(observaciones) {

}

c_oficina::~c_oficina()
{

}

void c_oficina::rellenarFila(QTableWidget *tabla, int pos){
    tabla->setItem(pos,0,new QTableWidgetItem(QString::fromStdString(this->oficina())));
    tabla->setItem(pos,1,new QTableWidgetItem(QString::fromStdString(this->tlfn())));
    tabla->setItem(pos,2,new QTableWidgetItem(QString::fromStdString(this->direccion())));
    tabla->setItem(pos,3,new QTableWidgetItem(QString::fromStdString(this->poblacion())));
    tabla->setItem(pos,4,new QTableWidgetItem(QString::number(this->ID())));
}

void c_oficina::setHeader(QTableWidget *tabla){
    tabla->setColumnCount(5);
    tabla->hideColumn(4);
    tabla->setHorizontalHeaderLabels(QString("Oficina;Teléfono;Dirección;Población").split(";"));
}

bool c_oficina::compare(NodoUnisys *criterio){
    bool mostrar=false;
    c_oficina* comparar = static_cast<c_oficina*> (criterio);
    if(this->ID_owner()==comparar->ID_owner() && this->borrado_!=true){
        mostrar=true;
    }
    return mostrar;
}

bool c_oficina::buscarID(int &ID){
    bool encontrado=false;
    if(this->ID()==ID){
        encontrado=true;
    }
    return encontrado;
}
