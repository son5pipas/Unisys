#ifndef GESTIONARNEGOS_H
#define GESTIONARNEGOS_H

#include <QDialog>
#include <maincontroller.h>
#include <lista.h>
#include <c_nego.h>
#include <util.h>

namespace Ui {
class gestionarNegos;
}

class gestionarNegos : public QDialog
{
    Q_OBJECT

public:
    explicit gestionarNegos(QWidget *parent = 0);
    ~gestionarNegos();

    void setController (MainController &);

private:
    Ui::gestionarNegos *ui;

    MainController *controller_;
    QDate dateLocal_;
    pel::List<int> buscarOwner;
    pel::List<int> buscarNegos;
    pel::List<int> buscarOrigen;
    pel::List<int> buscarDestino;
    c_nego criterio;
    int opcion;

    void inicial();
    void limpiarLabel();
    void showOwner();
    void showNegos();
    void showOrigen();
    void showDestino();



private slots:
    void selectedOwner();
    void selectedOrigen();
    void selectedDestino();
    void selectedFecha();
    void showLabel();
    void nuevo();
    void modificar();
    void borrar();
    void aceptar();
    void cancelar();

};

#endif // GESTIONARNEGOS_H
