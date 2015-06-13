#ifndef C_OFICINA_H
#define C_OFICINA_H

#include <string>
#include <iostream>
#include <interfaz.h>

class c_oficina: public NodoUnisys{
private:
    int ID_;
    int ID_owner_;
    bool borrado_;
    std::string oficina_;
    std::string razon_;
    std::string NIF_;
    std::string tlfn_;
    std::string direccion_;
    std::string CP_;
    std::string poblacion_;
    std::string provincia_;
    std::string pais_;
    std::string continente_;
    std::string observaciones_;

public:
    c_oficina();

    c_oficina(int ID, int ID_owner, std::string oficina, std::string razon, std::string NIF, std::string tlfn,
              std::string direccion, std::string CP, std::string poblacion, std::string provincia,
              std::string pais, std::string continente, std::string observaciones);
    ~c_oficina();

    int ID() const;
    void setID(int ID);
    int ID_owner() const;
    void setID_owner(int ID_owner);
    bool borrado() const;
    void setBorrado(bool borrado);
    std::string oficina() const;
    void setOficina(const std::string &oficina);
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
    std::string continente() const;
    void setContinente(const std::string &continente);
    std::string observaciones() const;
    void setObservaciones(const std::string &observaciones);

    void rellenarFila(QTableWidget *tabla, int pos);
    void setHeader (QTableWidget *tabla);
    bool compare (NodoUnisys *criterio);
    bool buscarID (int &ID);
};

#endif // C_OFICINA_H
