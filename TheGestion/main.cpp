#include <QApplication>
#include "theacceuil.h"
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <QString>
#include <QtCore>


int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    TheAcceuil acceuil;
    acceuil.BBD_Connexion();
    acceuil.show();
//LIBS += -LC:\wamp64\bin\mysql\mysql5.7.19\lib -llibmysql
//LIBS += -LC:\"Program Files"\MySQL\"MySQL Server 8.0"\lib -llibmysql
//C:\\Users\\User\\Documents\\Qt_Projects\\CpooJuniorEntreprise\\template.txt
    return app.exec();
}
