#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <c_user.h>
#include <c_owner.h>
#include <c_oficina.h>
#include <c_nego.h>
#include "util.h"
#include <c_peticion.h>
#include <cargadatos.h>
#include <lista.h>


class MainController {
private:
    pel::List <c_user> users;
    int ultimoIDuser=19;
    pel::List <c_owner> owners;
    int ultimoIDowners=2;
    pel::List <c_oficina> oficinas;
    int ultimoIDoficinas=6;
    pel::List <c_nego> negos;
    int ultimoIDnegos=45;
    pel::List <c_peticion> peticiones;
    int ultimoIDpeticiones=8;

    int registrado_;

    void load_users ();
    void load_owners ();
    void load_oficinas ();
    void load_negos ();
    void load_peticiones ();

public:
    MainController();
    ~MainController();

    void init();
    void registrado(int);
    int getRegistrado();

    pel::List<c_user> getUsers();
    pel::List<c_owner> getOwners();
    pel::List<c_oficina> getOficinas();
    pel::List<c_nego> getNegos();
    void setOwner(c_owner);
    void setOficina(c_oficina);
    void setUser(c_user);
    void setNegos(c_nego);
    void modificarOwner (int, c_owner);
    void modificarNego (int, c_nego);
    void modificarUser (int, c_user);
    void modificarOficina (int, c_oficina);
    pel::List<c_peticion> getPeticiones();
    void setPeticiones(c_peticion);


    int check_user (std::string, std::string);
    bool restarPlazas (int posNego, int plazas);

    int getUltimoIDuser() const;
    void setUltimoIDuser();
    int getUltimoIDowners() const;
    void setUltimoIDowners();
    int getUltimoIDoficinas() const;
    void setUltimoIDoficinas();
    int getUltimoIDnegos() const;
    void setUltimoIDnegos();
    int getUltimoIDpeticiones() const;
    void setUltimoIDpeticiones();
};

#endif // MAINCONTROLLER_H
