#ifndef INTERFAZ
#define INTERFAZ

#include <QTableWidget>

class NodoUnisys{
public:
    NodoUnisys(){}
    virtual ~NodoUnisys(){}

    virtual void rellenarFila (QTableWidget *tabla, int pos)=0;
    virtual void setHeader (QTableWidget *tabla)=0;
    virtual bool compare(NodoUnisys *criterio)=0;
    virtual bool buscarID(int &ID)=0;
};

#endif // INTERFAZ

