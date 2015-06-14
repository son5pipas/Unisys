#ifndef OWNER_H
#define OWNER_H

#include <QDialog>

#include "gestionaroficina.h"
#include "gestionarusuario.h"
#include "consultarnegos.h"
#include "selectuserlogin.h"
#include "maincontroller.h"

namespace Ui {
class owner;
}

class owner : public QDialog
{
    Q_OBJECT

public:
    explicit owner(QWidget *parent = 0);
    ~owner();

    void setController (MainController &);

private:
    Ui::owner *ui;

    MainController *controller_;

private slots:
    void openVentana31();
    void openVentana32();
    void openVentana33();
};

#endif // OWNER_H
