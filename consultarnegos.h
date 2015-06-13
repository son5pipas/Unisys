#ifndef CONSULTARNEGOS_H
#define CONSULTARNEGOS_H

#include <QDialog>
#include <maincontroller.h>
#include <lista.h>
#include <c_nego.h>
#include <util.h>

namespace Ui {
class consultarNegos;
}

class consultarNegos : public QDialog
{
    Q_OBJECT

public:
    explicit consultarNegos(QWidget *parent = 0);
    ~consultarNegos();

    void setController (MainController &);

private:
    Ui::consultarNegos *ui;

    MainController *controller_;
    QDate dateLocal_;
    pel::List<int> buscarNegos;
    pel::List<int> buscarOrigen;
    pel::List<int> buscarDestino;
    c_nego criterio;

    void inicial();
    void showOrigen();
    void showDestino();

private slots:
    void showNegos();
//    void activarFecha();
    void showLabel();
    void selectedOrigen();
    void selectedDestino();
    void selectedFecha();
};

#endif // CONSULTARNEGOS_H
