#ifndef C_USER_H
#define C_USER_H

#include <string>
#include <iostream>
#include "interfaz.h"


class c_user: public NodoUnisys{
private:
    int ID_;
    int ID_owner_;
    int ID_oficina_;
    short role_;
    bool borrado_;
    std::string nombre_;
    std::string usuario_;
    std::string contrasena_;

public:
    c_user();
    c_user(int ID, int ID_owner, int ID_oficina, short role, std::string nombre, std::string usuario, std::string contrasena);
    ~c_user();

    int ID() const;
    void setID(int ID);
    int ID_owner() const;
    void setID_owner(int ID_owner);
    int ID_oficina() const;
    void setID_oficina(int ID_oficina);
    short role() const;
    void setRole(short role);
    bool borrado() const;
    void setBorrado (bool borrado);
    std::string nombre() const;
    void setNombre(const std::string &nombre);
    std::string usuario() const;
    void setUsuario(const std::string &usuario);
    std::string contrasena() const;
    void setContrasena(const std::string &contrasena);

    void rellenarFila(QTableWidget *tabla, int pos);
    void setHeader (QTableWidget *tabla);
    bool compare (NodoUnisys *criterio);
    bool buscarID (int &ID);
};

#endif // C_USER_H
