#ifndef RELLENOTABLAS
#define RELLENOTABLAS

#include <lista.h>
#include <QTableWidget>
#include <interfaz.h>
#include "maincontroller.h"

template<typename Contenedor>
void rellenarTabla(Contenedor lista, QTableWidget* tabla, NodoUnisys* criterio){
    int filas=0;
    tabla->clear();
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

template<typename Contenedor>
/*bool*/void encontrarID(Contenedor lista, int *ID){
    //bool encontrado=false;
    auto iter=lista.begin();
    size_t count=lista.count();
    int buscar = *ID;
    for (size_t i=0; i<count; i++){
        if (iter->buscarID(buscar)){
            //encontrado=true;
            *ID=i;
            //return encontrado;
        }
        iter++;
    }
    //return encontrado;
}

//template<typename Contenedor>
//void limpiarListas(Contenedor &lista){
//    auto iter=lista->begin();
//    size_t count=lista->count();
//    for (size_t i=0; i<count; i++){
//        if(lista->at(i).borrado()==true){
//            lista->erase(iter);
//        }
//        iter++;
//    }
//}

#endif // RELLENOTABLAS

