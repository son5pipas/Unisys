#ifndef RELLENOTABLAS
#define RELLENOTABLAS

#include <QTableWidget>

#include "lista.h"
#include "maincontroller.h"
#include "interfaz.h"

template<typename Contenedor>
void rellenarTabla(Contenedor lista, QTableWidget* tabla, NodoUnisys* criterio){
    int filas=0;
    tabla->clear();
    tabla->setRowCount(0);
    if (!lista.empty()){
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
    }
}

template<typename Contenedor>
void encontrarID(Contenedor lista, int *ID){
    auto iter=lista.begin();
    size_t count=lista.count();
    int buscar = *ID;
    for (size_t i=0; i<count; i++){
        if (iter->buscarID(buscar)){
            *ID=i;        
        }
        iter++;
    }
}

#endif // RELLENOTABLAS

