#ifndef HISTORIAL_H
#define HISTORIAL_H

#include <QDialog>

#include "compania.h"
#include "maincontroller.h"
#include "util.h"

namespace Ui {
class historial;
}

class historial : public QDialog
{
    Q_OBJECT

public:
    explicit historial(QWidget *parent = 0);
    ~historial();

     void setController (MainController &controller);

private:
    Ui::historial *ui;

    MainController *controller_;

    c_peticion criterio;

    void inicial();
    void showOwner();
    void showOficina();
    void showContinente();
    void showPais();
    void showEstados();
    void limpiarLabel();

private slots:
    void showPeticiones();
    void showLabel();
};

#endif // HISTORIAL_H
