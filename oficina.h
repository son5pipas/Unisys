#ifndef OFICINA_H
#define OFICINA_H

#include <QDialog>
#include <maincontroller.h>
#include <lista.h>
#include "util.h"

namespace Ui {
class oficina;
}

class oficina : public QDialog
{
    Q_OBJECT

public:
    explicit oficina(QWidget *parent = 0);
    ~oficina();

    void setController (MainController &);
private:
    Ui::oficina *ui;

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
    void activarReservas();
    void reservar();
};

#endif // OFICINA_H
