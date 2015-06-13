#-------------------------------------------------
#
# Project created by QtCreator 2015-04-14T23:30:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Unisys_01
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    selectuserlogin.cpp \
    compania.cpp \
    gestionarowner.cpp \
    gestionarusuario.cpp \
    gestionarnegos.cpp \
    owner.cpp \
    gestionaroficina.cpp \
    oficina.cpp \
    consultarnegos.cpp \
    c_owner.cpp \
    c_oficina.cpp \
    c_user.cpp \
    c_nego.cpp \
    maincontroller.cpp \
    cargadatos.cpp \
    c_peticion.cpp \
    log.cpp \
    c_fecha.cpp \
    c_fechahora.cpp

CONFIG +=debug
CONFIG += c++11

HEADERS  += mainwindow.h \
    selectuserlogin.h \
    compania.h \
    gestionarowner.h \
    gestionarusuario.h \
    gestionarnegos.h \
    gestionaroficina.h \
    oficina.h \
    consultarnegos.h \
    owner.h \
    c_owner.h \
    c_oficina.h \
    c_user.h \
    c_nego.h \
    maincontroller.h \
    cargadatos.h \
    c_peticion.h \
    log.h \
    interfaz.h \
    lista.h \
    c_fecha.h \
    c_fechahora.h \
    util.h

FORMS    += mainwindow.ui \
    selectuserlogin.ui \
    compania.ui \
    gestionarowner.ui \
    gestionarusuario.ui \
    gestionarnegos.ui \
    owner.ui \
    gestionaroficina.ui \
    oficina.ui \
    consultarnegos.ui \
    log.ui
