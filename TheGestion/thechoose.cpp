#include "thechoose.h"
#include "thenewconv.h"
#include "ui_thechoose.h"
#include "infoentreprise.h"
#include <QtSql>
#include <QSqlDatabase>
#include <infoetudiant.h>
#include <infoprojet.h>
#include <thegeneral.h>
#include <thegestionconvention.h>

TheChoose::TheChoose(QString Nom, QString Prenom, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TheChoose)
{
    ui->setupUi(this);
    this->Prenom = Prenom;
    this->Nom = Nom;
    //ui->GestionAssoButton->setVisible(false);
    LoadInfo();
    connect(ui->NewProjetButton,SIGNAL(clicked()),this,SLOT(startNewProjet()));
    connect(ui->InfoEntButton,SIGNAL(clicked()),this,SLOT(affichageEntreprise()));
    //ui->AdressLabel->setText(Prenom);
    connect(ui->InfoEtuButton,SIGNAL(clicked(bool)),this,SLOT(startInfoEtu()));
    connect(ui->InfoProjetButton, SIGNAL(clicked(bool)), this, SLOT(startInfoProjet()));
    connect(ui->GestionAssoButton, SIGNAL(clicked(bool)), this, SLOT(startGeneral()));
    connect(ui->GestionConvButton, SIGNAL(clicked(bool)),this,SLOT(startGestionConv()));

}
void TheChoose::startGestionConv()
{
    TheGestionConvention *PageNew = new TheGestionConvention(Nom, Prenom);
    PageNew->exec();
}
TheChoose::~TheChoose()
{
    delete ui;
}

void TheChoose::startInfoEtu(){
    infoEtudiant *NewPage = new infoEtudiant(Nom,Prenom);
    NewPage->exec();
}

void TheChoose::startNewProjet(){
    TheNewConv *PageNew = new TheNewConv(Nom,Prenom);
    PageNew->exec();
}

void TheChoose::affichageEntreprise()
{
    InfoEntreprise *PageNew = new InfoEntreprise(Nom,Prenom);

    PageNew->exec();
}
void TheChoose::startInfoProjet()
{
    InfoProjet *PageNew = new InfoProjet(Nom, Prenom);

    PageNew->exec();
}

void TheChoose::startGeneral()
{
    TheGeneral *PageNew = new TheGeneral();

    PageNew->exec();
}
void TheChoose::LoadInfo(){
    QSqlQuery query;
    query.exec("SELECT * FROM user WHERE nomMembre=\""+Nom+"\" and prenomMembre=\""+Prenom+"\"");
    query.next();
    ui->NameLabel->setText(query.value(1).toString());
    ui->SurnameLabel->setText(query.value(2).toString());
    ui->StatutLabel->setText(query.value(3).toString());
    ui->AdressLabel->setText(query.value(7).toString());
    ui->MailLabel->setText(query.value(8).toString());
    ui->TelLabel->setText(query.value(6).toString());

}
