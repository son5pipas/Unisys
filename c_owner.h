#ifndef C_OWNER_H
#define C_OWNER_H

#include <iostream>
#include <string>
#include "interfaz.h"

class c_owner: public NodoUnisys{
private:
    int ID_;
    bool borrado_;
    std::string owner_;
    std::string razon_;
    std::string NIF_;
    std::string tlfn_;
    std::string direccion_;
    std::string CP_;
    std::string poblacion_;
    std::string provincia_;
    std::string pais_;
    std::string observaciones_;

public:
    c_owner ();
    c_owner(int ID, std::string owner, std::string razon, std::string NIF, std::string tlfn,
            std::string direccion, std::string CP, std::string poblacion, std::string provincia,
           std::string pais, std::string observaciones);
    ~c_owner();

    int ID() const;
    void setID(int ID);
    bool borrado() const;
    void setBorrado(const bool borrado);
    std::string owner() const;
    void setOwner(const std::string &owner);
    std::string razon() const;
    void setRazon(const std::string &razon);
    std::string NIF() const;
    void setNIF(const std::string &NIF);
    std::string tlfn() const;
    void setTlfn(const std::string &tlfn);
    std::string direccion() const;
    void setDireccion(const std::string &direccion);
    std::string CP() const;
    void setCP(const std::string &CP);
    std::string poblacion() const;
    void setPoblacion(const std::string &poblacion);
    std::string provincia() const;
    void setProvincia(const std::string &provincia);
    std::string pais() const;
    void setPais(const std::string &pais);
    std::string observaciones() const;
    void setObservaciones(const std::string &observaciones);

    void rellenarFila(QTableWidget *tabla, int pos);
    void setHeader (QTableWidget *tabla);
    bool compare (NodoUnisys *criterio);
    bool buscarID (int &ID);
};

#endif // C_OWNER_H
