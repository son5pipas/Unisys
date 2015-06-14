#ifndef GESTIONARUSUARIO_H
#define GESTIONARUSUARIO_H

#include <QDialog>
#include <qmessagebox.h>

#include "compania.h"
#include "owner.h"
#include "maincontroller.h"
#include "util.h"


// MOSTRAR COMBO OWNER

namespace Ui {
class gestionarUsuario;
}

class gestionarUsuario : public QDialog
{
    Q_OBJECT

public:
    explicit gestionarUsuario(QWidget *parent = 0);
    ~gestionarUsuario();

    void setController (MainController &);

private:
    Ui::gestionarUsuario *ui;

    MainController *controller_;
    pel::List<int> buscarOwn;
    pel::List<int> buscarOfi;
    pel::List<int> buscarUser;
    c_user criterio;
    int role;
    int opcion;
    int mostrados;

    void inicialCompania();
    void inicialOwner();
    void showUsuarios();
    void showOwner();
    void showOficinas();
    void start();
    void limpiarLabel();


private slots:
    void selectOwner();
    void selectOficina();
    void nuevo();
    void modificar();
    void borrar();
    void aceptar();
    void cancelar();
    void showLabel();
};

#endif // GESTIONARUSUARIO_H
