#include "c_user.h"


int c_user::ID() const
{
    return ID_;
}

void c_user::setID(int ID)
{
    ID_ = ID;
}

int c_user::ID_owner() const
{
    return ID_owner_;
}

void c_user::setID_owner(int ID_owner)
{
    ID_owner_ = ID_owner;
}

int c_user::ID_oficina() const
{
    return ID_oficina_;
}

void c_user::setID_oficina(int ID_oficina)
{
    ID_oficina_ = ID_oficina;
}

short c_user::role() const
{
    return role_;
}

void c_user::setRole(short role)
{
    role_ = role;
}

bool c_user::borrado() const
{
    return borrado_;
}

void c_user::setBorrado(bool borrado)
{
    borrado_ = borrado;
}

std::string c_user::nombre() const
{
    return nombre_;
}

void c_user::setNombre(const std::string &nombre)
{
    nombre_ = nombre;
}

std::string c_user::usuario() const
{
    return usuario_;
}

void c_user::setUsuario(const std::string &usuario)
{
    usuario_ = usuario;
}

std::string c_user::contrasena() const
{
    return contrasena_;
}

void c_user::setContrasena(const std::string &contrasena)
{
    contrasena_ = contrasena;
}


c_user::c_user(){

}

c_user::c_user(int ID, int ID_owner, int ID_oficina, short role, std::string nombre, std::string usuario, std::string contrasena) :
    ID_(ID), ID_owner_(ID_owner), ID_oficina_(ID_oficina), role_(role), nombre_(nombre),
               usuario_(usuario), contrasena_(contrasena){ this->setBorrado(false);

}

c_user::~c_user()
{

}

void c_user::rellenarFila(QTableWidget *tabla, int pos){
    tabla->setItem(pos,0,new QTableWidgetItem(QString::fromStdString(this->nombre())));
    tabla->setItem(pos,1,new QTableWidgetItem(QString::fromStdString(this->usuario())));
    tabla->setItem(pos,2,new QTableWidgetItem(QString::number(this->ID())));
}

void c_user::setHeader(QTableWidget *tabla){
    tabla->setColumnCount(3);
    tabla->hideColumn(2);
    tabla->setHorizontalHeaderLabels(QString("Nombre;Usuario").split(";"));
}

bool c_user::compare(NodoUnisys *criterio){
    bool mostrar=false;
    c_user* comparar=static_cast<c_user*>(criterio);
    if(comparar->role()==2){
        if(this->ID_owner()==comparar->ID_owner() && this->ID_oficina()==comparar->ID_oficina() && this->role()==3 && this->borrado()!=1){
            mostrar=true;
        }
    }else if(comparar->role()==3){
        if(this->ID_owner()==comparar->ID_owner() && this->ID_oficina()==comparar->ID_oficina() && this->role()==4 && this->borrado()!=1){
            mostrar=true;
        }
    }else if(comparar->role()==-1){
        if(this->ID_owner()==comparar->ID_owner() && this->ID_oficina()==comparar->ID_oficina() && this->role()!=1 && this->borrado()!=1){
            mostrar=true;
        }
    }
    return mostrar;
}

bool c_user::buscarID(int &ID){
    bool encontrado=false;
    if(this->ID()==ID){
        encontrado=true;
    }
    return encontrado;
}
