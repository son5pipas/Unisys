#ifndef GESTIONAROFICINA_H
#define GESTIONAROFICINA_H

#include <QDialog>

#include "owner.h"
#include "maincontroller.h"
#include "lista.h"
#include "interfaz.h"
#include "util.h"

namespace Ui {
class gestionarOficina;
}

class gestionarOficina : public QDialog
{
    Q_OBJECT

public:
    explicit gestionarOficina(QWidget *parent = 0);
    ~gestionarOficina();

    void setController (MainController &);

private:
    Ui::gestionarOficina *ui;

    MainController *controller_;

    pel::List<int> buscarOficina;

    c_oficina criterio;

    int mostrados, opcion;

    void inicial();
    void limpiarLabel();

private slots:
    void showOficina();
    void showLabel();
    void nuevo();
    void modificar();
    void borrar();
    void aceptar();
    void cancelar();
};

#endif // GESTIONAROFICINA_H
