#ifndef CONSULTARNEGOS_H
#define CONSULTARNEGOS_H

#include <QDialog>

#include "owner.h"
#include "maincontroller.h"
#include "lista.h"
#include "c_nego.h"
#include "util.h"

namespace Ui {
class consultarNegos;
}

class consultarNegos : public QDialog
{
    Q_OBJECT

public:
    explicit consultarNegos(QWidget *parent = 0);
    ~consultarNegos();

    /**
     * @brief setController
     *
     * Establece el controller en la nueva ventana.
     */
    void setController (MainController &);

private:
    Ui::consultarNegos *ui;

    /**
     * @brief controller_
     *
     * Contiene todos los datos durante la ejecución del programa.
     */
    MainController *controller_;

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
     * @brief inicial
     *
     * Establece la configuración inicial.
     */
    void inicial();
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

private slots:
    /**
     * @brief showNegos
     *
     * Muestra todos los negos con los filtros establecidos en la Tabla de Negos.
     */
    void showNegos();
    /**
     * @brief showLabel
     *
     * Rellena todos los labels con los campos del nego seleccionado en la TablaNegos.
     */
    void showLabel();
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
};

#endif // CONSULTARNEGOS_H
