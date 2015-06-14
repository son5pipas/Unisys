#ifndef GESTIONARNEGOS_H
#define GESTIONARNEGOS_H

#include <QDialog>

#include "compania.h"
#include "maincontroller.h"
#include "lista.h"
#include "c_nego.h"
#include "util.h"

namespace Ui {
class gestionarNegos;
}

class gestionarNegos : public QDialog
{
    Q_OBJECT

public:
    explicit gestionarNegos(QWidget *parent = 0);
    ~gestionarNegos();

    /**
     * @brief setController
     * @param controller
     *
     * Establece el controller en la nueva ventana.
     */
    void setController (MainController &controller);

private:
    Ui::gestionarNegos *ui;

    /**
     * @brief controller_
     *
     * Contiene todos los datos durante la ejecución del programa.
     */
    MainController *controller_;

    /**
     * @brief buscarOwner
     *
     * Contiene la posición de los Owners que se muestran en el ComboOwner.
     */
    pel::List<int> buscarOwner;
    /**
     * @brief buscarOrigen
     *
     * Contiene la posición de los Negos que se muestran en el ComboOrigen.
     */
    pel::List<int> buscarOrigen;
    /**
     * @brief buscarDestino
     *
     * Contiene la posición de los Negos que se muestran en el ComboDestino.
     */
    pel::List<int> buscarDestino;

    /**
     * @brief dateLocal_
     *
     * Fecha actual del ordenador.
     */
    QDate dateLocal_;
    /**
     * @brief criterio
     *
     * Nego que contiene los datos en sus respectivos campos por los que se quiere filtrar a la hora de mostrar los Negos.
     */
    c_nego criterio;

    /**
     * @brief opcion
     *
     * Identifica la acción que se ha seleccionado entre Nuevo y Modificar.
     */
    int opcion;

    /**
     * @brief inicial
     *
     * Establece la configuración inicial.
     */
    void inicial();
    /**
     * @brief limpiarLabel
     *
     * Limpia los labels.
     */
    void limpiarLabel();
    /**
     * @brief showOwner
     *
     * Muestra los Owners en el ComboOwner para seleccionar por el que se quiere filtrar.
     */
    void showOwner();
    /**
     * @brief showOrigen
     *
     * Muestra el origen de los negos existentes en el ComboOrigen para seleccionar por el que se quiere filtrar.
     */
    void showOrigen();
    /**
     * @brief showDestino
     *
     * Muestra el destino de los negos existentes en el ComboOrigen para seleccionar por el que se quiere filtrar.
     */
    void showDestino();
    /**
     * @brief showNegos
     *
     * Muestra todos los negos con los filtros establecidos en la Tabla de Negos.
     */
    void showNegos();

private slots:
    /**
     * @brief selectedOwner
     *
     * Establece el Owner seleccionado en el ComboOwner como filtro.
     */
    void selectedOwner();
    /**
     * @brief selectedOrigen
     *
     * Establece el Origen seleccionado en el ComboOrigen como filtro.
     */
    void selectedOrigen();
    /**
     * @brief selectedDestino
     *
     * Establece el Destino seleccionado en el ComboDestino como filtro.
     */
    void selectedDestino();
    /**
     * @brief selectedFecha
     *
     * Establece la Fecha seleccionada en el dateFilter como filtro.
     */
    void selectedFecha();
    /**
     * @brief showLabel
     *
     * Rellena todos los labels con los campos del nego seleccionado en la TablaNegos.
     */
    void showLabel();
    /**
     * @brief nuevo
     *
     * Permite la escritura en los labels vacíos para crear un nuevo nego.
     */
    void nuevo();
    /**
     * @brief modificar
     *
     * Permite la escritura en los labels rellenos con el Nego seleccionado en la TablaNegos para modificar los campos del Nego mostrado.
     */
    void modificar();
    /**
     * @brief borrar
     *
     * Hace un borrado lógico del nego seleccionado en la TablaNegos.
     */
    void borrar();
    /**
     * @brief aceptar
     *
     * Crea el nuevo Nego introducido o establece las modificaciones en el Nego seleccionado.
     */
    void aceptar();
    /**
     * @brief cancelar
     *
     * Cancela la creación o modificación de los Negos.
     */
    void cancelar();

};

#endif // GESTIONARNEGOS_H
