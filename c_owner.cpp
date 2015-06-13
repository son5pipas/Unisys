#include "c_owner.h"


int c_owner::ID() const
{
    return ID_;
}

void c_owner::setID(int ID)
{
    ID_ = ID;
}

bool c_owner::borrado() const
{
    return borrado_;
}

void c_owner::setBorrado(const bool borrado)
{
    borrado_ = borrado;
}

std::string c_owner::owner() const
{
    return owner_;
}

void c_owner::setOwner(const std::string &owner)
{
    owner_ = owner;
}

std::string c_owner::razon() const
{
    return razon_;
}

void c_owner::setRazon(const std::string &razon)
{
    razon_ = razon;
}

std::string c_owner::NIF() const
{
    return NIF_;
}

void c_owner::setNIF(const std::string &NIF)
{
    NIF_ = NIF;
}

std::string c_owner::tlfn() const
{
    return tlfn_;
}

void c_owner::setTlfn(const std::string &tlfn)
{
    tlfn_ = tlfn;
}

std::string c_owner::direccion() const
{
    return direccion_;
}

void c_owner::setDireccion(const std::string &direccion)
{
    direccion_ = direccion;
}

std::string c_owner::CP() const
{
    return CP_;
}

void c_owner::setCP(const std::string &CP)
{
    CP_ = CP;
}

std::string c_owner::poblacion() const
{
    return poblacion_;
}

void c_owner::setPoblacion(const std::string &poblacion)
{
    poblacion_ = poblacion;
}

std::string c_owner::provincia() const
{
    return provincia_;
}

void c_owner::setProvincia(const std::string &provincia)
{
    provincia_ = provincia;
}

std::string c_owner::pais() const
{
    return pais_;
}

void c_owner::setPais(const std::string &pais)
{
    pais_ = pais;
}

std::string c_owner::observaciones() const
{
    return observaciones_;
}

void c_owner::setObservaciones(const std::string &observaciones)
{
    observaciones_ = observaciones;
}

void c_owner::rellenarFila(QTableWidget *tabla, int pos){
    tabla->setItem(pos,0,new QTableWidgetItem(QString::fromStdString(owner())));
    tabla->setItem(pos,1,new QTableWidgetItem(QString::fromStdString(tlfn())));
    tabla->setItem(pos,2,new QTableWidgetItem(QString::fromStdString(direccion())));
    tabla->setItem(pos,3,new QTableWidgetItem(QString::fromStdString(poblacion())));
    tabla->setItem(pos,4,new QTableWidgetItem(QString::number(ID())));
}

void c_owner::setHeader(QTableWidget *tabla){
    tabla->setColumnCount(5);
    tabla->hideColumn(4);
    tabla->setHorizontalHeaderLabels(QString("Owner;Teléfono;Dirección;Población").split(";"));
}

bool c_owner::compare(NodoUnisys *criterio){
    bool mostrar=true;
    c_owner* comparar = static_cast<c_owner*> (criterio);
    comparar->setBorrado(true);
    if(this->borrado_==comparar->borrado()){
        mostrar=false;
    }
    return mostrar;
}

bool c_owner::buscarID(int &ID){
    bool encontrado=false;
    if(this->ID()==ID){
        encontrado=true;
    }
    return encontrado;
}

c_owner::c_owner (){ }

c_owner::c_owner (int ID, std::string owner, std::string razon, std::string NIF, std::string tlfn,
                  std::string direccion, std::string CP, std::string poblacion, std::string provincia,
                 std::string pais, std::string observaciones) :
                 ID_(ID), borrado_(false), owner_(owner), razon_(razon), NIF_(NIF), tlfn_(tlfn),
                 direccion_(direccion), CP_(CP), poblacion_(poblacion), provincia_(provincia),
                 pais_(pais), observaciones_(observaciones){

}

c_owner::~c_owner()
{

}

