#include "theacceuil.h"
#include "thegeneral.h"
#include "thechoose.h"
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <QString>
#include <QMainWindow>
#include <QtCore>
#include <QPrinter>
#include <QPdfWriter>
#include <QPainter>

TheAcceuil::TheAcceuil() : QMainWindow()
{
    zoneCentrale = new QWidget();
    msg = new QLabel("");

    login_admin = new QLineEdit();
    mdp_admin = new QLineEdit();
    mdp_admin->setEchoMode(QLineEdit::Password);
    valid_admin = new QPushButton("Valider");
    // connect pour admin
    QWidget::connect(valid_admin,SIGNAL(clicked()),this,SLOT(co_admin()));
    //Creation du formulaire admin
    form_admin = new QFormLayout();
    form_admin->addRow("Login : ",login_admin);
    form_admin->addRow("Password : ",mdp_admin);
    form_admin->addRow("Connexion : ",valid_admin);

    login_etu = new QLineEdit();
    mdp_etu = new QLineEdit();
    mdp_etu->setEchoMode(QLineEdit::Password);
    valid_etu = new QPushButton("Valider");
    // connect pour etu
    QWidget::connect(valid_etu,SIGNAL(clicked()),this,SLOT(co_etu()));
    //Creation du formulaire admin
    form_etu = new QFormLayout();
    form_etu->addRow("Login : ",login_etu);
    form_etu->addRow("Password : ",mdp_etu);
    form_etu->addRow("Connexion : ",valid_etu);

    // Le titre
    QLabel *titre = new QLabel("The Gestion");
    titre->setFont(QFont("Comic Sans MS",20));

    // Edition de la page
    globalForm = new QGridLayout();
    globalForm->addWidget(titre,0,0);
    globalForm->addWidget(new QLabel("Admin Log :"),1,0);
    globalForm->addWidget(new QLabel("Etudiant Log :"),1,2);
    globalForm->addLayout(form_admin,2,1);
    globalForm->addLayout(form_etu,2,3);

    zoneCentrale->setLayout(globalForm);

    setCentralWidget(zoneCentrale);

}

// SLOT

// Test de connexion d'un admin
void TheAcceuil::co_admin() {
    QSqlQuery query;
    query.exec("SELECT * FROM User WHERE login=\""+login_admin->text()+
                  "\" AND password=\""+mdp_admin->text()+"\" AND statut=\"admin\" ");
    if (query.next()){
        msg->setText("Admin Co !");
        // Renvoie vers Ecran des choix AVEC un QDialog
        TheChoose *test = new TheChoose(query.value(1).toString(),query.value(2).toString());
        test->exec();
    }
    else {
        msg->setText("Admin NOT Co ..");
    }
    globalForm->addWidget(msg,3,1);

}

// Test de connexion d'un étudiant
void TheAcceuil::co_etu() {
    QSqlQuery query;
    query.exec("SELECT * FROM User WHERE login=\""+login_etu->text()+
                  "\" AND password=\""+mdp_etu->text()+"\" AND statut=\"etu\" ");
    if (query.next()){
        msg->setText("Etu Co !");
        // Renvoie vers Ecran des choix AVEC un QDialog
        TheChoose *test = new TheChoose(query.value(1).toString(),query.value(2).toString());
        test->exec();
    }
    else {
        msg->setText("Etu NOT Co ..");
    }
    globalForm->addWidget(msg,3,2);

}

// Function

// Connexion à la BDD
bool TheAcceuil::BBD_Connexion(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("userBD");
    db.setPassword("junior");
    db.setDatabaseName("JuniorEntreprise");
    if (db.open()) {
        msg->setText("BDD Co !");
        globalForm->addWidget(msg,0,1);
        return true;
    }
    else {
        msg->setText("BDD NOT Co !");
        globalForm->addWidget(msg,0,1);
        return false;
    }

}

/*bool TheAcceuil::BBD_Connexion(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("papuche");
    db.setPassword("3600");
    db.setDatabaseName("JuniorEntreprise");
    if (db.open()) {
        msg->setText("BDD Co !");
        globalForm->addWidget(msg,0,1);
        return true;
    }
    else {
        msg->setText("BDD NOT Co !");
        globalForm->addWidget(msg,0,1);
        return false;
    }

}*/


