#ifndef CARGADATOS_H
#define CARGADATOS_H

#include <lista.h>
#include <c_user.h>
#include <c_owner.h>
#include <c_oficina.h>
#include <c_nego.h>
#include <c_peticion.h>

class CargaDatos
{
public:
    CargaDatos();
    ~CargaDatos();

    static pel::List<c_user> leerUser();
    static pel::List<c_owner> leerOwners();
    static pel::List<c_oficina> leerOficinas();
    static pel::List<c_nego> leerNegos();
    static pel::List<c_peticion> leerPeticion();
};

#endif // CARGADATOS_H
