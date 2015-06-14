#ifndef C_PETICION_H
#define C_PETICION_H
#include <QDateTime>
#include <QString>
#include "interfaz.h"

class c_peticion : public NodoUnisys{
private:
    int ID_;
    int plazas_;
    std::string owner_;
    std::string oficina_;
    std::string usuario_;
    std::string pais_;
    std::string continente_;
    std::string origen_;
    std::string destino_;
    std::string aceptada_;
    QDateTime peticion_;

public:
    c_peticion();
    c_peticion(int ID, int plazas, std::string owner, std::string oficina, std::string usuario, std::string pais, std::string continente, std::string origen, std::string destino, std::string aceptada, QDateTime peticion);
    ~c_peticion();

    QDateTime getPeticion() const;
    void setPeticion(const QDateTime &value);
    int getPlazas() const;
    void setPlazas(int value);
    std::string getContinente() const;
    void setContinente(const std::string &value);
    std::string getPais() const;
    void setPais(const std::string &value);
    std::string getOwner() const;
    void setOwner(const std::string &value);
    std::string getOficina() const;
    void setOficina(const std::string &value);
    std::string origen() const;
    void setOrigen(const std::string &origen);
    std::string destino() const;
    void setDestino(const std::string &destino);
    std::string getUsuario() const;
    void setUsuario(const std::string &value);
    std::string aceptada() const;
    void setAceptada(const std::string &aceptada);


    void rellenarFila(QTableWidget *tabla, int pos);
    void setHeader (QTableWidget *tabla);
    bool compare (NodoUnisys *criterio);
    bool buscarID (int &ID);
    int ID() const;
    void setID(int ID);
};

#endif // C_PETICION_H
