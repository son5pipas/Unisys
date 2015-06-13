#include "rellenotablas.h"

void rellonotablas::rellenarTabla(Contenedor lista, QTableWidget* tabla, NodoUnisys* criterio){
    int filas=0;
    //tabla->setRowCount(filas);
    tabla->clear();
    tabla->setColumnCount(2);
    tabla->setRowCount(0);
    auto iter=lista.begin();
    iter->setHeader(tabla);

    size_t count=lista.count();
    for (size_t i=0; i<count; i++){
        if (iter->compare(criterio)){
            filas++;
            tabla->setRowCount(filas);
            iter->rellenarFila(tabla, filas-1);
        }
        iter++;
    }
    //tabla->setRowCount(filas);
    //return *iter;
}
