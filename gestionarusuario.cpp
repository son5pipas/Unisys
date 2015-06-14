#include "ui_gestionarusuario.h"

#include "gestionarusuario.h"

//Alvaro

gestionarUsuario::gestionarUsuario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestionarUsuario)
{
    ui->setupUi(this);
    this->opcion=0;
}

gestionarUsuario::~gestionarUsuario()
{
    if (controller_->getUsers().at(controller_->getRegistrado()).role()==2){
        compania v2;
        v2.setController(*controller_);
        v2.exec();
    }else{
        owner v3;
        v3.setController(*controller_);
        v3.exec();
    }
    delete ui;
}

void gestionarUsuario::setController (MainController &controller){
    controller_=&controller;
    criterio.setBorrado(false);
    criterio.setID_oficina(0);
    criterio.setID(0);
    criterio.setNombre("0");
    criterio.setUsuario("0");
    this->start();
}

void gestionarUsuario::start(){
    role=controller_->getUsers().at(controller_->getRegistrado()).role();
    switch (role) {
    case 2:{
        criterio.setID_owner(-1);
        this->inicialCompania();
        break;
    }
    case 3:{
        criterio.setID_owner(controller_->getUsers().at(controller_->getRegistrado()).ID_owner());
        this->inicialOwner();
        break;
    }
    default:
        break;
    }
    criterio.setRole(role);
}

void gestionarUsuario::inicialCompania(){
    this->showOwner();
    this->showUsuarios();
    ui->editUser->setEnabled(false);
    ui->btnAcpetar->setEnabled(false);
    ui->btnCancelar->setEnabled(false);
    ui->btnModificar->setEnabled(false);
    ui->btnBorrar->setEnabled(false);
    ui->btnNuevo->setEnabled(true);
    ui->tableUser->setEnabled(true);
    ui->comboOwner->setEnabled(true);
    ui->comboOficina->setEnabled(false);
}

void gestionarUsuario::inicialOwner(){
    this->showOwner();
    this->showUsuarios();
    ui->editUser->setEnabled(false);
    ui->btnAcpetar->setEnabled(false);
    ui->btnCancelar->setEnabled(false);
    ui->btnModificar->setEnabled(false);
    ui->btnBorrar->setEnabled(false);
    ui->btnNuevo->setEnabled(true);
    ui->tableUser->setEnabled(true);
    ui->comboOwner->setEnabled(false);
    ui->comboOficina->setEnabled(true);
}

void gestionarUsuario::showUsuarios(){
    rellenarTabla(controller_->getUsers(), ui->tableUser, &criterio);
}

void gestionarUsuario::showOwner (){
    if (opcion==0){
        buscarOwn.clear();
        ui->comboOwner->clear();
        switch (role){
        case 2:{
            ui->comboOwner->addItem(" ");
            for (size_t i=0; i<controller_->getOwners().count(); i++){
                if(controller_->getOwners().at(i).borrado()!=1){
                    ui->comboOwner->addItem(QString::fromStdString(controller_->getOwners().at(i).owner()));
                    buscarOwn.append(controller_->getOwners().at(i).ID());
                }
            }
            break;
        }
        case 3:{
            for (size_t i=0; i<controller_->getOwners().count(); i++){
                if(controller_->getOwners().at(i).ID()==controller_->getUsers().at(controller_->getRegistrado()).ID_owner() && controller_->getOwners().at(i).borrado()!=1){
                    ui->comboOwner->addItem(QString::fromStdString(controller_->getOwners().at(i).owner()));
                    buscarOwn.append(controller_->getOwners().at(i).ID());
                    criterio.setID_owner(buscarOwn.at(0));
                }
            }
            showOficinas();
            break;
        }
        default:
            break;
        }
    }
}

void gestionarUsuario::showOficinas (){
    buscarOfi.clear();
    ui->comboOficina->clear();
    ui->comboOficina->addItem(" ");
    for (size_t i=0; i<controller_->getOficinas().count(); i++){
        if(controller_->getOficinas().at(i).ID_owner()==criterio.ID_owner() && controller_->getOficinas().at(i).borrado()!=1){
            ui->comboOficina->addItem(QString::fromStdString(controller_->getOficinas().at(i).oficina()));
            buscarOfi.append(controller_->getOficinas().at(i).ID());
        }
    }
}

void gestionarUsuario::selectOwner(){
    int iowner=ui->comboOwner->currentIndex();
    int owner=0;
    if (buscarOwn.empty()!=true && iowner>0){
        owner=buscarOwn.at(iowner-1);
        ui->btnNuevo->setEnabled(true);
    }else{
        if(role ==2){
            ui->btnNuevo->setEnabled(false);
        }
    }
    ui->btnModificar->setEnabled(false);
    ui->btnBorrar->setEnabled(false);
    criterio.setID_owner(owner);
    this->showOficinas();
    this->showUsuarios();
    this->limpiarLabel();
}

void gestionarUsuario::selectOficina(){
    int ioficina=ui->comboOficina->currentIndex();
    int oficina=0;
    if (buscarOfi.empty()!=true && ioficina>0){
        oficina=buscarOfi.at(ioficina-1);
        ui->btnNuevo->setEnabled(true);
    }else {
        if(role==3){
            ui->btnNuevo->setEnabled(false);
        }
    }
    ui->btnModificar->setEnabled(false);
    ui->btnBorrar->setEnabled(false);
    criterio.setID_oficina(oficina);
    this->showUsuarios();
    this->limpiarLabel();
}

void gestionarUsuario::showLabel(){
    QString ID = ui->tableUser->item(ui->tableUser->currentRow(), 2)->text();
    int seleccionado = ID.toInt();
    encontrarID(controller_->getUsers(), &seleccionado);
    ui->txtNombre->setText(QString::fromStdString(controller_->getUsers().at(seleccionado).nombre()));
    ui->txtUser->setText(QString::fromStdString(controller_->getUsers().at(seleccionado).usuario()));
    ui->txtPass->setText(QString::fromStdString(controller_->getUsers().at(seleccionado).contrasena()));

    ui->btnModificar->setEnabled(true);
    ui->btnBorrar->setEnabled(true);
}

void gestionarUsuario::nuevo(){
    opcion=1;
    ui->editUser->setEnabled(true);
    ui->tableUser->clearSelection();
    ui->tableUser->setEnabled(false);
    ui->btnModificar->setEnabled(false);
    ui->btnBorrar->setEnabled(false);
    ui->btnAcpetar->setEnabled(true);
    ui->btnCancelar->setEnabled(true);
    ui->btnNuevo->setEnabled(false);
    ui->comboOwner->setEnabled(false);

    this->limpiarLabel();

    ui->txtNombre->setFocus();
}

void gestionarUsuario::modificar(){
    QModelIndexList selectedList = ui->tableUser->selectionModel()->selectedRows();
    if (!selectedList.empty()){ //Si no hay ninguna seleccion en la tabla de usuarios, no se puede modificar ninguno.
        opcion=2;
        ui->editUser->setEnabled(true);
        ui->tableUser->setEnabled(false);
        ui->txtNombre->setFocus();
        ui->btnAcpetar->setEnabled(true);
        ui->btnCancelar->setEnabled(true);
        ui->btnModificar->setEnabled(false);
        ui->btnBorrar->setEnabled(false);
        ui->btnNuevo->setEnabled(false);
    }
}

void gestionarUsuario::borrar(){
    QString ID = ui->tableUser->item(ui->tableUser->currentRow(),2)->text();
    int seleccionado = ID.toInt();
    encontrarID(controller_->getUsers(), &seleccionado);

    ui->editUser->setEnabled(false);
    ui->tableUser->setEnabled(false);
    ui->btnAcpetar->setEnabled(false);
    ui->btnCancelar->setEnabled(false);
    ui->btnModificar->setEnabled(false);
    ui->btnBorrar->setEnabled(false);
    ui->btnNuevo->setEnabled(false);
    QMessageBox::StandardButton btnBorrar;
    btnBorrar = QMessageBox::question(this, "", "Está seguro que desea eliminar el Usuario: " + QString::fromStdString(controller_->getUsers().at(seleccionado).usuario()), QMessageBox::Yes | QMessageBox:: No);
    if(btnBorrar == QMessageBox::Yes){
        c_user copyUser = controller_->getUsers().at(seleccionado);
        copyUser.setBorrado(true);
        controller_->modificarUser(seleccionado, copyUser);
        if (role==2){
            this->inicialCompania();
        }else{
            this->inicialOwner();
        }
        this->limpiarLabel();
    }else if(btnBorrar == QMessageBox::No){
        if (role==2){
            this->inicialCompania();
        }else{
            this->inicialOwner();
        }
        this->limpiarLabel();
    }
}

void gestionarUsuario::aceptar(){
    switch (opcion) {
    case 1:{
        if(ui->txtNombre->text().isEmpty() || ui->txtPass->text().isEmpty() || ui->txtUser->text().isEmpty()){
            QMessageBox::information(this, "", "Debe rellenar todos los campos");
        }else{
            c_user nuevo;
            controller_->setUltimoIDuser();
            nuevo.setID(controller_->getUltimoIDuser());
            nuevo.setID_owner(criterio.ID_owner());
            if(role==3){
                nuevo.setID_oficina(criterio.ID_oficina());
                nuevo.setRole(4);
            }else{
                nuevo.setID_oficina(0);
                nuevo.setRole(3);
            }
            nuevo.setBorrado(false);
            nuevo.setNombre(ui->txtNombre->text().toStdString());
            nuevo.setUsuario(ui->txtUser->text().toStdString());
            nuevo.setContrasena(ui->txtPass->text().toStdString());
            controller_->setUser(nuevo);
            if(role==3){
                this->inicialOwner();
            }else{
                this->inicialCompania();
            }
            ui->tableUser->selectRow(ui->tableUser->rowCount()-1);
        }
        break;
    }
    case 2:{
        QString ID = ui->tableUser->item(ui->tableUser->currentRow(),2)->text();
        int seleccionado = ID.toInt();
        encontrarID(controller_->getUsers(), &seleccionado);
        int fila = ui->tableUser->currentRow();

        if(ui->txtNombre->text().isEmpty() || ui->txtPass->text().isEmpty() || ui->txtUser->text().isEmpty()){
            QMessageBox::information(this, "", "Todos los campos deben estár rellenos");
        }else{
            c_user modificado;
            modificado=controller_->getUsers().at(seleccionado);
            modificado.setNombre(ui->txtNombre->text().toStdString());
            modificado.setUsuario(ui->txtUser->text().toStdString());
            modificado.setContrasena(ui->txtPass->text().toStdString());
            controller_->modificarUser(seleccionado, modificado);

            if(role==3){
                this->inicialOwner();
            }else{
                this->inicialCompania();
            }

            ui->tableUser->selectRow(fila);
        }
        break;
    }
    default:
        break;
    }
}

void gestionarUsuario::cancelar(){
    if(role==3){
        this->inicialOwner();
    }else{
        this->inicialCompania();
    }
    this->limpiarLabel();
}

void gestionarUsuario::limpiarLabel(){
    ui->txtNombre->clear();
    ui->txtPass->clear();
    ui->txtUser->clear();
}





















/*

void gestionarOwner::aceptar(){
    switch (opcion) {
    case 1:{
        if(ui->txtOwner->text().isEmpty() || ui->txtRazon->text().isEmpty() || ui->txtCP->text().isEmpty() || ui->txtDireccion->text().isEmpty() || ui->txtNIF->text().isEmpty() || ui->txtPais->text().isEmpty() || ui->txtPoblacion->text().isEmpty() || ui->txtProvincia->text().isEmpty() || ui->txtTlfn->text().isEmpty()){
            QMessageBox::information(this, "", "Debe rellenar todos los campos");
        }else{
            c_owner nuevo;
            nuevo.setID(controller_->getOwners().count()+1);
            nuevo.setBorrado(false);
            nuevo.setOwner(ui->txtOwner->text().toStdString());
            nuevo.setRazon(ui->txtRazon->text().toStdString());
            nuevo.setNIF(ui->txtNIF->text().toStdString());
            nuevo.setTlfn(ui->txtTlfn->text().toStdString());
            nuevo.setDireccion(ui->txtDireccion->text().toStdString());
            nuevo.setCP(ui->txtCP->text().toStdString());
            nuevo.setPoblacion(ui->txtPoblacion->text().toStdString());
            nuevo.setProvincia(ui->txtProvincia->text().toStdString());
            nuevo.setPais(ui->txtPais->text().toStdString());
            nuevo.setObservaciones(ui->plaintxtObservaciones->toPlainText().toStdString());
            controller_->setOwner(nuevo);
            this->inicial();
            ui->tableOwner->selectRow(mostrados-1);
        }
        break;
    }
    case 2:{
        QModelIndexList selectedList = ui->tableOwner->selectionModel()->selectedRows();
        int sel, seleccionado;
        for( int i=0; i<selectedList.count(); i++){
            sel=selectedList.at(i).row();
        }
        seleccionado=buscarOwner.at(sel);
        if(ui->txtOwner->text().isEmpty() || ui->txtRazon->text().isEmpty() || ui->txtCP->text().isEmpty() || ui->txtDireccion->text().isEmpty() || ui->txtNIF->text().isEmpty() || ui->txtPais->text().isEmpty() || ui->txtPoblacion->text().isEmpty() || ui->txtProvincia->text().isEmpty() || ui->txtTlfn->text().isEmpty()){
            QMessageBox::information(this, "", "Todos los campos deben estár rellenos");
        }else{
            c_owner modificado;
            modificado=controller_->getOwners().at(seleccionado);
            modificado.setOwner(ui->txtOwner->text().toStdString());
            modificado.setRazon(ui->txtRazon->text().toStdString());
            modificado.setNIF(ui->txtNIF->text().toStdString());
            modificado.setTlfn(ui->txtTlfn->text().toStdString());
            modificado.setDireccion(ui->txtDireccion->text().toStdString());
            modificado.setCP(ui->txtCP->text().toStdString());
            modificado.setPoblacion(ui->txtPoblacion->text().toStdString());
            modificado.setProvincia(ui->txtProvincia->text().toStdString());
            modificado.setPais(ui->txtPais->text().toStdString());
            modificado.setObservaciones(ui->plaintxtObservaciones->toPlainText().toStdString());
            controller_->modificarOwner(seleccionado, modificado);

            this->inicial();
            ui->tableOwner->selectRow(sel);
        }
        break;
    }
    default:
        break;
    }
}

void gestionarOwner::cancelar(){
    this->inicial();
    this->limpiarLabel();
}
*/
