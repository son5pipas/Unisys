#include "maincontroller.h"

#include <QDebug>
#include <algorithm>
#include <qmessagebox.h>

//ROI

MainController::MainController() {

}

void MainController::init(){
    load_users();
    load_owners();
    load_oficinas();
    load_negos();
    load_peticiones();
}

MainController::~MainController() {

}


int MainController::getUltimoIDuser() const
{
    return ultimoIDuser;
}

void MainController::setUltimoIDuser()
{
    ultimoIDuser++;
}

int MainController::getUltimoIDowners() const
{
    return ultimoIDowners;
}

void MainController::setUltimoIDowners()
{
    ultimoIDowners++;
}

int MainController::getUltimoIDoficinas() const
{
    return ultimoIDoficinas;
}

void MainController::setUltimoIDoficinas()
{
    ultimoIDoficinas++;
}

int MainController::getUltimoIDnegos() const
{
    return ultimoIDnegos;
}

void MainController::setUltimoIDnegos()
{
    ultimoIDnegos++;
}

int MainController::getUltimoIDpeticiones() const
{
    return ultimoIDpeticiones;
}

void MainController::setUltimoIDpeticiones()
{
    ultimoIDpeticiones++;
}


bool MainController::getSuperUser() const
{
    return superUser;
}

void MainController::setSuperUser(bool value)
{
    superUser = value;
}
void MainController::load_users() {
    users=CargaDatos::leerUser();
}

void MainController::load_owners() {
    owners=CargaDatos::leerOwners();
}

void MainController::load_oficinas() {
    oficinas=CargaDatos::leerOficinas();
}

void MainController::load_negos() {
    negos=CargaDatos::leerNegos();
}

void MainController::load_peticiones() {
    peticiones=CargaDatos::leerPeticion();
}

pel::List<c_peticion> MainController::getPeticiones(){
    return peticiones;
}

void MainController::setPeticiones(c_peticion peticion){
    peticiones.append(peticion);
}

pel::List<c_user> MainController::getUsers(){
    return users;
}

pel::List<c_owner> MainController::getOwners(){
    return owners;
}

pel::List<c_oficina> MainController::getOficinas(){
    return oficinas;
}

pel::List<c_nego> MainController::getNegos(){
    return negos;
}

void MainController::registrado(int registrado){
    registrado_=registrado;
}

int MainController::getRegistrado(){
    return registrado_;
}

void MainController::setOwner(c_owner setOwner){
    owners.append(setOwner);
}

void MainController::setUser(c_user setUser){
    users.append(setUser);
}

void MainController::setNegos(c_nego setNegos){
    negos.append(setNegos);
}

void MainController::setOficina(c_oficina setOficina){
    oficinas.append(setOficina);
}

void MainController::modificarOwner(int posicion, c_owner modificado){
    auto iter = owners.begin();
    for (int i=0; i<posicion; i++){
        iter++;
    }
    owners.replace(iter, modificado);
}

void MainController::modificarUser(int posicion, c_user modificado){
    auto iter = users.begin();
    for (int i=0; i<posicion; i++){
        iter++;
    }
    users.replace(iter, modificado);

}

void MainController::modificarOficina(int posicion, c_oficina modificado){
    auto iter = oficinas.begin();
    for (int i=0; i<posicion; i++){
        iter++;
    }
    oficinas.replace(iter, modificado);

}

void MainController::modificarNego(int posicion, c_nego modificado){
    auto iter = negos.begin();
    for (int i=0; i<posicion; i++){
        iter++;
    }
    negos.replace(iter, modificado);
}

int MainController::check_user(std::string usuario, std::string pass) {
    int result=0;
    for (size_t i=0; i<this->users.count(); i++){
        if(this->users.at(i).usuario().compare(usuario)==0 && this->users.at(i).contrasena().compare(pass)==0){
            result=users.at(i).role();
            registrado_=i;
        }
    }
    return result;
}

bool MainController::restarPlazas(int posNego, int plazas){
    bool aceptada=false;
    setUltimoIDpeticiones();

    c_peticion peticion;

    peticion.setOrigen(negos.at(posNego).origen());
    peticion.setDestino(negos.at(posNego).destino());

    peticion.setID(ultimoIDpeticiones);
    peticion.setPlazas(plazas);

    int posOficina = users.at(registrado_).ID_oficina();
    encontrarID(oficinas, &posOficina);
    peticion.setOficina(oficinas.at(posOficina).oficina());
    peticion.setContinente(oficinas.at(posOficina).continente());
    peticion.setPais(oficinas.at(posOficina).pais());

    int posOwner = users.at(registrado_).ID_owner();
    encontrarID(owners, &posOwner);
    peticion.setOwner(owners.at(posOwner).owner());
    peticion.setUsuario(users.at(registrado_).nombre());

    QDate local;
    QTime time;
    QDateTime hora;
    local.setDate(local.currentDate().year(), local.currentDate().month(), local.currentDate().day());
    hora.setDate(local);
    hora.setTime(time.currentTime());
    peticion.setPeticion(hora);

    int stock, restantes;
    c_nego restado=getNegos().at(posNego);
    stock=restado.plazas();
    if(stock>=plazas){
        restantes=stock-plazas;
        restado.setPlazas(restantes);
        modificarNego(posNego, restado);
        aceptada=true;
        peticion.setAceptada("Aceptada");
    }else{
        aceptada=false;
        peticion.setAceptada("Denegada");
    }
    setPeticiones(peticion);
    return aceptada;
}

void MainController::limpiarListas(int *owner, int *oficina, int *user, int *nego){

    pel::List<size_t>borrarnego;
    auto iter1 = negos.begin();
    size_t count1 = negos.count();
    for (size_t i=0; i<count1; i++){
        if (negos.at(i).borrado()==true){
            borrarnego.append(i);
        }
        ++iter1;
    }

    for (size_t i=borrarnego.count(); i>0; i--){
        auto iter11 = negos.end();
        qDebug()<<borrarnego.at(i-1);
        size_t count11 = borrarnego.at(i-1);
        for (size_t j=negos.count(); j>count11; j--){
            --iter11;
        }
        negos.erase(iter11);
    }

    pel::List<size_t>borraruser;
    auto iter2 = users.begin();
    size_t count2 = users.count();
    for (size_t i=0; i<count2; i++){
        if (users.at(i).borrado()==true){
            borraruser.append(i);
        }
        ++iter2;
    }

    for (size_t i=borraruser.count(); i>0; i--){
        auto iter22 = users.end();
        qDebug()<<borraruser.at(i-1);
        size_t count22 = borraruser.at(i-1);
        for (size_t j=users.count(); j>count22; j--){
            --iter22;
        }
        users.erase(iter22);
    }

    pel::List<size_t>borrarowners;
    auto iter3 = owners.begin();
    size_t count3 = owners.count();
    for (size_t i=0; i<count3; i++){
        if (owners.at(i).borrado()==true){
            borrarowners.append(i);
        }
        ++iter3;
    }

    for (size_t i=borrarowners.count(); i>0; i--){
        auto iter33 = owners.end();
        qDebug()<<borrarowners.at(i-1);
        size_t count33 = borrarowners.at(i-1);
        for (size_t j=owners.count(); j>count33; j--){
            --iter33;
        }
        owners.erase(iter33);
    }

    pel::List<size_t>borraroficinas;
    auto iter4 = oficinas.begin();
    size_t count4 = oficinas.count();
    for (size_t i=0; i<count4; i++){
        if (oficinas.at(i).borrado()==true){
            borraroficinas.append(i);
        }
        ++iter4;
    }

    for (size_t i=borraroficinas.count(); i>0; i--){
        auto iter44 = oficinas.end();
        qDebug()<<borraroficinas.at(i-1);
        size_t count44 = borraroficinas.at(i-1);
        for (size_t j=oficinas.count(); j>count44; j--){
            --iter44;
        }
        oficinas.erase(iter44);
    }

    *owner = borrarowners.count();
    *oficina = borraroficinas.count();
    *user = borraruser.count();
    *nego = borrarnego.count();
}

void MainController::disminuirNegos(int *negosDisminuidos){
    QDate local;
    local=local.currentDate();
    int numerodisminuido=0;
    for (size_t i=0; i<negos.count(); i++){
        if(local.toJulianDay() >= negos.at(i).fecha().date().toJulianDay()-negos.at(i).dis_fecha() && negos.at(i).disminuido()==false){
            c_nego disminuido = negos.at(i);
            int plazas = negos.at(i).plazas();
            int porcentaje = negos.at(i).porcentaje();
            plazas = plazas - ((plazas*porcentaje)/100);
            disminuido.setPlazas(plazas);
            disminuido.setDisminuido(true);
            modificarNego(i, disminuido);
            numerodisminuido++;
        }
    }
    *negosDisminuidos=numerodisminuido;
}

void MainController::borrarPasados(){
    QDate local;
    local=local.currentDate();
    QTime hora;
    hora = hora.currentTime();
    for (size_t i=0; i<negos.count(); i++){
        if(local >= negos.at(i).fecha().date() && hora > negos.at(i).fecha().time() /*|| negos.at(i).plazas()==0*/){
            c_nego borrar = negos.at(i);
            borrar.setBorrado(true);
            modificarNego(i, borrar);
        }
    }
}

