#ifndef SELECTUSERLOGIN_H
#define SELECTUSERLOGIN_H

#include <QDialog>

#include "c_user.h"
#include "compania.h"
#include "owner.h"
#include "oficina.h"
#include "maincontroller.h"
#include "util.h"

namespace Ui {
class selectUserLogin;
}

class selectUserLogin : public QDialog {
    Q_OBJECT

public:
    explicit selectUserLogin(QWidget *parent = 0);
    ~selectUserLogin();

    /**
     * @brief setController
     *
     * Establece el controller en la nueva ventana.
     */
    void setController (MainController &);

private:
    Ui::selectUserLogin *ui;

    /**
     * @brief controller_
     *
     * Contiene todos los datos durante la ejecución del programa.
     */
    MainController *controller_;

    /**
     * @brief buscarOfi
     *
     * Contiene la posición de las Oficinas que se muestran en el ComboOficinas.
     */
    pel::List <int> buscarOfi;
    /**
     * @brief buscarOwn
     *
     * Contiene la posición de los Owners que se muestran en el ComboOwner.
     */
    pel::List <int> buscarOwn;

    /**
     * @brief criterio
     *
     * User que contiene los datos en sus respectivos campos por los que se quiere filtrar a la hora de mostrar los Usuarios.
     */
    c_user criterio;

    /**
     * @brief showOwners
     *
     * Muestra los Owners en el ComboOwner para seleccionar por el que se quiere filtrar.
     */
    void showOwners ();

private slots:
    /**
     * @brief showOficinas
     *
     * Muestra las Oficinas en el ComboOficinas para seleccionar por el que se quiere filtrar.
     */
    void showOficinas();
    /**
     * @brief showUsers
     *
     * Muestra todos los Usuarios con los filtros establecidos en la Tabla de Users.
     */
    void showUsers();
    /**
     * @brief aceptar
     *
     * Abre la siguiente ventana según el usuario que se haya seleccionado.
     */
    void aceptar();
};

#endif // SELECTUSERLOGIN_H
