#ifndef SELECTUSERLOGIN_H
#define SELECTUSERLOGIN_H

#include <QDialog>
#include <c_user.h>
#include <maincontroller.h>
#include <compania.h>
#include <owner.h>
#include <oficina.h>
#include <util.h>

namespace Ui {
class selectUserLogin;
}

class selectUserLogin : public QDialog {
    Q_OBJECT

public:
    explicit selectUserLogin(QWidget *parent = 0);
    ~selectUserLogin();

    void setController (MainController &);

private:
    Ui::selectUserLogin *ui;
    MainController *controller_;
    pel::List <int> buscarOfi;
    pel::List <int> buscarOwn;
    pel::List <int> buscarUser;
    c_user criterio;

//    void showUsers();
    void showOwners ();
//    void showOficinas ();

private slots:
//    void selectOwner(int);
//    void selectOficina();
    void showOficinas();
    void showUsers();
    void aceptar();
};

#endif // SELECTUSERLOGIN_H
