#ifndef COMPANIA_H
#define COMPANIA_H

#include <QDialog>
#include <gestionarowner.h>
#include <gestionarusuario.h>
#include <gestionarnegos.h>
#include <log.h>
#include <maincontroller.h>

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

private slots:
    void openVentana21();
    void openVentana22();
    void openVentana23();
    void openVentana24();
    void openVentana25();
};

#endif // COMPANIA_H
