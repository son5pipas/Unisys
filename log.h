#ifndef LOG_H
#define LOG_H

#include <QDialog>
#include <maincontroller.h>
#include "util.h"

namespace Ui {
class log;
}

class Log : public QDialog
{
    Q_OBJECT

public:
    explicit Log(QWidget *parent = 0);
    ~Log();

    void setController (MainController &controller);



private:
    Ui::log *ui;

    MainController *controller_;
    c_peticion criterio;

//    pel::List<int> buscarOwner;

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

#endif // LOG_H
