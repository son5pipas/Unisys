#include "maincontroller.h"

#include <algorithm>
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
    std::string nego;
    nego= negos.at(posNego).origen() + " - " + negos.at(posNego).destino();
    peticion.setNego(nego);

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
