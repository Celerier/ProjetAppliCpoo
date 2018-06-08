#include "thenewentreprise.h"
#include "ui_thenewentreprise.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>

TheNewEntreprise::TheNewEntreprise(QString Nom, QString Prenom, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TheNewEntreprise)
{
    ui->setupUi(this);
    this->Nom=Nom;
    this->Prenom=Prenom;
    LoadInfo();
    connect(ui->buttonValid,SIGNAL(clicked(bool)),this,SLOT(addEnt()));
    connect(ui->buttonQuit,SIGNAL(clicked(bool)),this,SLOT(close()));
}

TheNewEntreprise::~TheNewEntreprise()
{
    delete ui;
}

void TheNewEntreprise::addEnt(){
    QSqlQuery query;
    int nbId;
    // Definition de l'ID
    query.exec("SELECT max(idEntreprise) FROM Entreprise");;
    if (query.next()){
        nbId = query.value(0).toInt() + 1;
    }
    else{
        nbId = 1 ;
    }
    // Insertion de la nouvelle entreprise
    if(query.exec("INSERT INTO Entreprise VALUES("+QString::number(nbId)+
               ",\""+ui->linenomEntreprise->text()+"\","+
               ui->lineSiret->text()+",\""+ui->lineCorrespondant->text()+"\",\""+
                  ui->lineTel->text()+"\",\""+ui->LineMail->text()+"\")")){
        QMessageBox::information(this,"Insertion","INSERTION DE L'ENTREPRISE : OK");
        // Vide Les champs
        ui->lineCorrespondant->setText("");
        ui->linenomEntreprise->setText("");
        ui->lineSiret->setText("");
        ui->lineTel->setText("");
        ui->LineMail->setText("");
    }
    else{
        QMessageBox::warning(this,"Insertion","INSERTION DE L'ENTREPRISE : ECHEC");
    }

}

void TheNewEntreprise::LoadInfo(){
    QSqlQuery query;
    query.exec("SELECT * FROM user WHERE nomMembre=\""+Nom+"\" and prenomMembre=\""+Prenom+"\"");
    query.next();
    ui->NameLabel->setText(query.value(1).toString());
    ui->SurnameLabel->setText(query.value(2).toString());
    ui->StatutLabel->setText(query.value("statut").toString());
    ui->AdressLabel->setText(query.value("adresseMembre").toString());
    ui->MailLabel->setText(query.value("mailMembre").toString());
    ui->TelLabel->setText(query.value("telMembre").toString());

}


