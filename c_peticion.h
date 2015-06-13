#ifndef C_PETICION_H
#define C_PETICION_H
#include <QDateTime>
#include <QString>
#include "interfaz.h"

class c_peticion : public NodoUnisys{
private:
    std::string owner_;
    std::string continente_;
    std::string pais_;
    std::string oficina_;
    std::string aceptada_;
    QDateTime peticion_;
    int plazas_;
    std::string nego_;
    std::string usuario_;
    int ID_;

public:
    c_peticion();
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
    std::string nego() const;
    void setNego(const std::string &nego);
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
