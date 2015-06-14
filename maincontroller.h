#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "cargadatos.h"
#include "lista.h"
#include "c_nego.h"
#include "c_oficina.h"
#include "c_owner.h"
#include "c_peticion.h"
#include "c_user.h"
#include "util.h"

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
    bool superUser;

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
    pel::List<c_peticion> getPeticiones();
    int getUltimoIDuser() const;
    int getUltimoIDowners() const;
    int getUltimoIDoficinas() const;
    int getUltimoIDnegos() const;
    int getUltimoIDpeticiones() const;
    bool getSuperUser() const;

    void setOwner(c_owner);
    void setOficina(c_oficina);
    void setUser(c_user);
    void setNegos(c_nego);
    void setPeticiones(c_peticion);
    void setUltimoIDuser();
    void setUltimoIDowners();
    void setUltimoIDoficinas();
    void setUltimoIDnegos();
    void setUltimoIDpeticiones();
    void setSuperUser(bool value);

    void modificarOwner (int, c_owner);
    void modificarNego (int, c_nego);
    void modificarUser (int, c_user);
    void modificarOficina (int, c_oficina);

    int check_user (std::string, std::string);
    bool restarPlazas (int posNego, int plazas);
    void limpiarListas(int *owner, int *oficina, int *user, int *nego);
    void disminuirNegos(int *negosDisminuidos);
    void borrarPasados();
};

#endif // MAINCONTROLLER_H
