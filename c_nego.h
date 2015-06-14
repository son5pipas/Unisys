#ifndef C_NEGO_H
#define C_NEGO_H

#include <string>
#include <QDateTime>
#include <interfaz.h>


class c_nego: public NodoUnisys{
private:
    long ID_;
    int ID_owner_;
    int plazas_;
    int porcentaje_;
    bool borrado_;
    bool disminuido_;
    std::string origen_;
    std::string destino_;
    QDateTime fecha_;
    int dis_fecha_;

public:
    c_nego();
    c_nego(int ID, int ID_owner, int plazas, int porcentaje, std::string origen, std::string destino,
           QDateTime fecha, int dis_fecha);
    ~c_nego();

    long ID() const;
    void setID(long ID);
    int ID_owner() const;
    void setID_owner(int ID_owner);
    int plazas() const;
    void setPlazas(int plazas);
    int porcentaje() const;
    void setPorcentaje(int porcentaje);
    bool borrado() const;
    void setBorrado(bool borrado);
    bool disminuido() const;
    void setDisminuido(bool disminuido);
    std::string origen() const;
    void setOrigen(const std::string &origen);
    std::string destino() const;
    void setDestino(const std::string &destino);
    QDateTime fecha() const;
    void setFecha(const QDate &fecha, const QTime &time);
    int dis_fecha() const;
    void setDis_fecha(int dis_fecha);

    void rellenarFila(QTableWidget *tabla, int pos);
    void setHeader (QTableWidget *tabla);
    bool compare (NodoUnisys *criterio);
    bool buscarID (int &ID);
    //void setController(MainController &);
};

#endif // C_NEGO_H
