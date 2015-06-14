#include "cargadatos.h"

//Julius

CargaDatos::CargaDatos() {

}

CargaDatos::~CargaDatos() {

}

pel::List<c_user> CargaDatos::leerUser(){
    pel::List<c_user> usuarios;

    c_user berto    (1,0,0,1,"Alberto HG","1","1");

    c_user comp1    (2,0,0,2,"José Luis HF","cmp1","cmp1"); //comp1.setBorrado(1);
    c_user comp2    (3,0,0,2,"Álvaro AV","cmp2","cmp2");

    c_user berto2   (4,1,0,3,"Sergio PL","ow11","ow11");
    c_user berto3   (5,1,0,3,"Guille RS","ow12","ow12");

    c_user jl       (6,2,0,3,"Roi SR","ow21","ow21");
    c_user berto4   (7,2,0,3,"David CG","ow22","ow22");

    c_user berto5   (8,1,1,4,"Adrián VM","of11","of11");
    c_user berto6   (9,1,1,4,"Daniel TL","of12","of12");
    c_user jl2      (10,1,1,4,"Esther AT","of13","of13");
    c_user berto7   (11,1,1,4,"Nines MF","of14","of14");
    c_user berto8   (12,1,2,4,"Gema RC","of15","of15");
    c_user jl3      (13,1,2,4,"Juan AT","of16","of16");
    c_user berto9   (14,1,3,4,"Macarena TB","of17","of17");

    c_user berto10  (15,2,4,4,"Altea AA","of21","of21");
    c_user jl4      (16,2,4,4,"Javier DL","of22","of22");
    c_user berto11  (17,2,5,4,"Miguel Ángel LL","of23","of23");
    c_user berto12  (18,2,6,4,"Mario MS","of24","of24");
    c_user jl5      (19,2,6,4,"Alex MR","of25","of25");

    usuarios.append(comp1);
    usuarios.append(comp2);
    usuarios.append(berto);
    usuarios.append(berto2);
    usuarios.append(berto3);
    usuarios.append(berto4);
    usuarios.append(berto5);
    usuarios.append(berto6);
    usuarios.append(berto7);
    usuarios.append(berto8);
    usuarios.append(berto9);
    usuarios.append(berto10);
    usuarios.append(berto11);
    usuarios.append(berto12);
    usuarios.append(jl);
    usuarios.append(jl2);
    usuarios.append(jl3);
    usuarios.append(jl4);
    usuarios.append(jl5);

    return usuarios;
}

pel::List<c_owner> CargaDatos::leerOwners(){
    pel::List<c_owner> owners;

    c_owner elcorteingles (1,"El Corte Inglés","El Corte Inglés S.A.", "A-28017895", "902224411","C/ Hermosilla, 112", "28009", "Madrid", "Madrid", "España", "A");
    c_owner halcon        (2,"Halcón Viajes","Viajes Halcón S.A.U", "A-10005510", "912182128","Carretera Arenal a Llucmajor Km 21,5 Polígono Son Noguera", "07620", "Llucmajor", "Islas Baleares", "España", "B");

    owners.append(elcorteingles);
    owners.append(halcon);

    return owners;
}

pel::List<c_oficina> CargaDatos::leerOficinas(){
    pel::List<c_oficina> oficinas;

    c_oficina elcorte1   (1, 1, "Suecia", "Viajes el Corte Inglés Suecia S.L.", "A-28136478", "913135590", "C/ Suecia, 35", "28022", "Madrid", "Madrid", "España", "Europa", "L-V: 09:30-14:00 y 16:30-20:00 / S:10:00-14:00");
    c_oficina elcorte2   (2, 1, "Viajes Granada", "Agencia de Viajes Granadian S.L.", "A-40295826", "958536574", "Camino de Ronda, 75", "18004", "Granada", "Granada", "España", "Europa", "L-V: 09:30-14:30 y 16:30-20:00 / S:10:00-14:30");
    c_oficina elcorte3   (3, 1, "Campo de las Naciones", "Viajes Madrileños S.L.", "A-57648305", "917416462", "Avda. de Los Andes, 50", "28042", "Madrid", "Madrid", "España", "Europa", "L-S: 10:00 - 22:00 / D: 11:00 - 21:00");
    c_oficina halcon1    (4, 2, "Halcón Goya", "Viajes Goya S.L.", "A-20355906", "914359160", "C/ Goya, 23", "28009", "Madrid", "Madrid", "España", "Europa", "Mañanas: de 09:30 a 13:30 / Tardes: de 16:00 a 20:00"); //halcon1.setBorrado(1);
    c_oficina halcon2    (5, 2, "Halcón Viajes Valladolid", "Valladolid Viaja S.L.", "A-22022938", "983350600", "C/ San Lorenzo, 4", "47001", "Valladolid", "Valladolid", "España", "Europa", "Mañanas: de 09:30 a 13:30 / Tardes: de 16:00 a 20:00");
    c_oficina halcon3    (6, 2, "Viajes la Rambla", "Viajes La Rambla S.L.", "A-29095843", "934852909", "Rambla del Poblenou, 70", "08005", "Barcelona", "Barcelona", "España", "Europa", "Mañanas: de 09:30 a 13:30 / Tardes: de 16:00 a 20:00");

    oficinas.append(elcorte1);
    oficinas.append(elcorte2);
    oficinas.append(elcorte3);
    oficinas.append(halcon1);
    oficinas.append(halcon2);
    oficinas.append(halcon3);

    return oficinas;
}

pel::List<c_nego> CargaDatos::leerNegos(){
    pel::List<c_nego> negos;
    c_nego a1 (1, 1, 0/*30*/, 20,  "Granada", "París",         QDateTime(QDate(2015,8,3), QTime(10,50)), 25);
    c_nego a2 (2, 1, 40, 10,       "Madrid", "Londres",        QDateTime(QDate(2015,8,3), QTime(11,50)), 25);
    c_nego a3 (3, 1, 50, 20,       "Barcelona", "Berlin",      QDateTime(QDate(2015,8,3), QTime(12,50)), 25);
    c_nego a4 (4, 1, 30, 30,       "Valencia", "Copenhague",   QDateTime(QDate(2015,8,3), QTime(13,50)), 25);
    c_nego a5 (5, 1, 0/*40*/, 20,  "Granada", "Roma",          QDateTime(QDate(2015,8,3), QTime(14,50)), 25);
    c_nego a6 (6, 1, 50, 10,       "Madrid", "París",          QDateTime(QDate(2015,8,4), QTime(10,50)), 25);
    c_nego a7 (7, 1, 30, 20,       "Barcelona", "Londres",     QDateTime(QDate(2015,8,4), QTime(11,50)), 25);
    c_nego a8 (8, 1, 0/*40*/, 30,  "Valencia", "Berlin",       QDateTime(QDate(2015,8,4), QTime(12,50)), 25);
    c_nego a9 (9, 1, 50, 20,       "Granada", "Copenhague",    QDateTime(QDate(2015,8,4), QTime(13,50)), 25);
    c_nego a10 (10, 1, 30, 10,     "Madrid", "Roma",           QDateTime(QDate(2015,8,4), QTime(14,50)), 25);
    c_nego a11 (11, 1, 40, 20,     "Barcelona", "París",       QDateTime(QDate(2015,8,5), QTime(10,50)), 25);
    c_nego a12 (12, 1, 50, 30,     "Valencia", "Londres",      QDateTime(QDate(2015,8,5), QTime(11,50)), 25);
    c_nego a13 (13, 1, 30, 20,     "Granada", "Berlin",        QDateTime(QDate(2015,8,5), QTime(12,50)), 25);
    c_nego a14 (14, 1, 40, 10,     "Madrid", "Copenhague",     QDateTime(QDate(2015,8,5), QTime(13,50)), 25);
    c_nego a15 (15, 1, 50, 20,     "Barcelona", "Roma",        QDateTime(QDate(2015,8,5), QTime(14,50)), 25);
    c_nego a16 (16, 1, 30, 30,     "Valencia", "París",        QDateTime(QDate(2015,8,6), QTime(10,50)), 25);
    c_nego a17 (17, 1, 40, 20,     "Granada", "Londres",       QDateTime(QDate(2015,8,6), QTime(11,50)), 25);
    c_nego a18 (18, 1, 50, 10,     "Madrid", "Berlin",         QDateTime(QDate(2015,8,6), QTime(12,50)), 25);
    c_nego a19 (19, 1, 30, 20,     "Barcelona", "Copenhague",  QDateTime(QDate(2015,8,6), QTime(13,50)), 25);
    c_nego a20 (20, 1, 40, 30,     "Valencia", "Roma",         QDateTime(QDate(2015,8,6), QTime(14,50)), 25);
    c_nego b1 (21, 2, 50, 20,      "Granada", "París",         QDateTime(QDate(2015,8,3), QTime(10,50)), 25);
    c_nego b2 (22, 2, 30, 10,      "Madrid", "Londres",        QDateTime(QDate(2015,8,3), QTime(11,50)), 25);
    c_nego b3 (23, 2, 40, 20,      "Barcelona", "Berlin",      QDateTime(QDate(2015,8,3), QTime(12,50)), 25);
    c_nego b4 (24, 2, 50, 30,      "Valencia", "Copenhague",   QDateTime(QDate(2015,8,3), QTime(13,50)), 25);
    c_nego b5 (25, 2, 30, 20,      "Granada", "Roma",          QDateTime(QDate(2015,8,3), QTime(14,50)), 25);
    c_nego b6 (26, 2, 40, 10,      "Madrid", "París",          QDateTime(QDate(2015,8,4), QTime(10,50)), 25);
    c_nego b7 (27, 2, 50, 20,      "Barcelona", "Londres",     QDateTime(QDate(2015,8,4), QTime(11,50)), 25);
    c_nego b8 (28, 2, 30, 30,      "Valencia", "Berlin",       QDateTime(QDate(2015,8,4), QTime(12,50)), 25);
    c_nego b9 (29, 2, 40, 20,      "Granada", "Copenhague",    QDateTime(QDate(2015,8,4), QTime(13,50)), 25);
    c_nego b10 (30, 2, 50, 30,     "Madrid", "Roma",           QDateTime(QDate(2015,8,4), QTime(14,50)), 25);
    c_nego b11 (31, 2, 30, 20,     "Barcelona", "París",       QDateTime(QDate(2015,8,5), QTime(10,50)), 25);
    c_nego b12 (32, 2, 40, 10,     "Valencia", "Londres",      QDateTime(QDate(2015,8,5), QTime(11,50)), 25);
    c_nego b13 (33, 2, 50, 20,     "Granada", "Berlin",        QDateTime(QDate(2015,8,5), QTime(12,50)), 25);
    c_nego b14 (34, 2, 30, 30,     "Madrid", "Copenhague",     QDateTime(QDate(2015,8,5), QTime(13,50)), 25);
    c_nego b15 (35, 2, 40, 20,     "Barcelona", "Roma",        QDateTime(QDate(2015,8,5), QTime(14,50)), 25);
    c_nego b16 (36, 2, 50, 10,     "Valencia", "París",        QDateTime(QDate(2015,8,6), QTime(10,50)), 25);
    c_nego b17 (37, 2, 30, 20,     "Granada", "Londres",       QDateTime(QDate(2015,8,6), QTime(11,50)), 25);
    c_nego b18 (38, 2, 40, 30,     "Madrid", "Berlin",         QDateTime(QDate(2015,8,6), QTime(12,50)), 25);
    c_nego b19 (39, 2, 50, 20,     "Barcelona", "Copenhague",  QDateTime(QDate(2015,8,6), QTime(13,50)), 25);
    c_nego b20 (40, 2, 30, 10,     "Valencia", "Roma",         QDateTime(QDate(2015,8,6), QTime(14,50)), 25);
    c_nego p1 (41, 1, 30, 20,      "Prueba", "Con Prueba",     QDateTime(QDate(2015,8,3), QTime(10,50)), 25);
    c_nego p2 (42, 1, 40, 10,      "Prueba", "Con Prueba",     QDateTime(QDate(2015,8,3), QTime(11,50)), 25);
    c_nego p3 (43, 1, 50, 20,      "Prueba", "Con Prueba 2",   QDateTime(QDate(2015,8,3), QTime(12,50)), 25);
    c_nego p4 (44, 1, 30, 30,      "Prueba 2", "2 Prueba",     QDateTime(QDate(2015,8,3), QTime(13,50)), 25);
    c_nego p5 (45, 1, 40, 20,      "Prueba 2", "2 Prueba",     QDateTime(QDate(2015,8,3), QTime(14,50)), 25);

    a1.setBorrado(true);
    a20.setBorrado(true);
    //p5.setBorrado(true);
    a2.setDisminuido(true);
    a4.setDisminuido(true);
    a6.setDisminuido(true);
    a8.setDisminuido(true);

    negos.append(a1);
    negos.append(a2);
    negos.append(a3);
    negos.append(a4);
    negos.append(a5);
    negos.append(a6);
    negos.append(a7);
    negos.append(a8);
    negos.append(a9);
    negos.append(a10);
    negos.append(a11);
    negos.append(a12);
    negos.append(a13);
    negos.append(a14);
    negos.append(a15);
    negos.append(a16);
    negos.append(a17);
    negos.append(a18);
    negos.append(a19);
    negos.append(a20);
    negos.append(b1);
    negos.append(b2);
    negos.append(b3);
    negos.append(b4);
    negos.append(b5);
    negos.append(b6);
    negos.append(b7);
    negos.append(b8);
    negos.append(b9);
    negos.append(b10);
    negos.append(b11);
    negos.append(b12);
    negos.append(b13);
    negos.append(b14);
    negos.append(b15);
    negos.append(b16);
    negos.append(b17);
    negos.append(b18);
    negos.append(b19);
    negos.append(b20);
    negos.append(p1);
    negos.append(p2);
    negos.append(p3);
    negos.append(p4);
    negos.append(p5);

    return negos;
}

pel::List<c_peticion> CargaDatos::leerPeticion(){
    pel::List<c_peticion> peticiones;

    c_peticion nueva1 (1, 3, "Halcón Viajes", "Campo de las Naciones", "José Luis", "España", "Europa", "Granada", "Paris", "Aceptada", QDateTime(QDate(2015,06,15), QTime(14,18)));
    c_peticion nueva2 (2, 3, "Halcón Viajes", "Campo de las Naciones", "José Luis", "España", "Europa", "Madrid", "Berlin", "Aceptada", QDateTime(QDate(2015,06,15), QTime(14,18)));
    c_peticion nueva3 (3, 3, "Halcón Viajes", "Campo de las Naciones", "José Luis", "España", "Europa", "Sevilla", "Valencia", "Denegada", QDateTime(QDate(2015,06,15), QTime(14,18)));
    c_peticion nueva4 (4, 3, "Halcón Viajes", "Campo de las Naciones", "José Luis", "España", "Europa", "Londres", "Barcelona", "Aceptada", QDateTime(QDate(2015,06,15), QTime(14,18)));
    c_peticion nueva5 (5, 3, "Halcón Viajes", "Campo de las Naciones", "José Luis", "España", "Europa", "Malaga", "Paris", "Aceptada", QDateTime(QDate(2015,06,15), QTime(14,18)));
    c_peticion nueva6 (6, 3, "Halcón Viajes", "Campo de las Naciones", "José Luis", "España", "Europa", "Roma", "Barcelona", "Aceptada", QDateTime(QDate(2015,06,15), QTime(14,18)));
    c_peticion nueva7 (7, 3, "Halcón Viajes", "Campo de las Naciones", "José Luis", "España", "Europa", "Copenhage", "Berlin", "Denegada", QDateTime(QDate(2015,06,15), QTime(14,18)));
    c_peticion nueva8 (8, 3, "Halcón Viajes", "Campo de las Naciones", "José Luis", "España", "Europa", "Berlin", "Madrid", "Denegada", QDateTime(QDate(2015,06,15), QTime(14,18)));

    peticiones.append(nueva1);
    peticiones.append(nueva2);
    peticiones.append(nueva3);
    peticiones.append(nueva4);
    peticiones.append(nueva5);
    peticiones.append(nueva6);
    peticiones.append(nueva7);
    peticiones.append(nueva8);

    return peticiones;
}
