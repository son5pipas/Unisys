#ifndef COMPANIA_H
#define COMPANIA_H

#include <QDialog>

#include "selectuserlogin.h"
#include "gestionarowner.h"
#include "gestionarusuario.h"
#include "gestionarnegos.h"
#include "historial.h"


namespace Ui {
class compania;
}

class compania : public QDialog
{
    Q_OBJECT

public:
    explicit compania(QWidget *parent = 0);
    ~compania();

    void setController (MainController &);

private:
    Ui::compania *ui;

    MainController *controller_;

    void comprobarNegos();

private slots:
    void openVentana21();
    void openVentana22();
    void openVentana23();
    void openVentana24();
    void openVentana25();
};

#endif // COMPANIA_H
