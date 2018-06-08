#include "thegeneral.h"
#include "ui_thegeneral.h"
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <QString>
#include <math.h>
#include <QMessageBox>

TheGeneral::TheGeneral(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TheGeneral)
{
    ui->setupUi(this);
    //ui->testStyle->setStyleSheet("border: 1px solid black; border-radius: 10px;");
    connect(ui->ValidPush, SIGNAL(clicked()), this, SLOT(addUser()));
}

TheGeneral::~TheGeneral()
{
    delete ui;

}

// Ajout utilisateur ou Admin (uniquement par admin)
void TheGeneral::addUser(){
    QSqlQuery query;

        if(query.exec("INSERT INTO user VALUES (\""+ui->nomLineEdit->text()+"\",\""+ui->prenomLineEdit->text()+"\",\""+ui->statutLineEdit->text()+"\",\""+ui->loginLineEdit->text()+"\","+"sqdfqsdfqs"+",\""+ui->telephoneLineEdit->text()+"\",\""+ui->adresseLineEdit->text()+"\",\""+ui->mailLineEdit->text()+"\")"))
        {
            QMessageBox::information(this, "Personne ajouté", " Works ");
        }
        //QString::number(hashage(ui->motDePasseLineEdit->text().toStdString()))
}

unsigned int TheGeneral::hashage(std::string motDePasse)
{
    int hashCode(0);


    for (int i(0); i < motDePasse.length(); i++)
    {
        hashCode += ((int) motDePasse[i]) * (int)(pow(42, i));
    }

    return abs(hashCode) % (3* (int) (pow(10, 9)));
}
