#include "infoentreprise.h"
#include "ui_infoentreprise.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <thenewentreprise.h>

InfoEntreprise::InfoEntreprise(QString Nom, QString Prenom, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoEntreprise)
{
    ui->setupUi(this);
    this->Nom = Nom;
    this->Prenom=Prenom;
    LoadInfo();
    QSqlQuery query;

    query.exec("SELECT count(*) FROM Entreprise");
    query.next();

    ui->tableInfoEntreprise->setRowCount(query.value(0).toInt());

    m_tableHeader<<"numero Entreprise"<<"Nom Entreprise";

    int NbColonne = 2; // rentrer ici le nombre de colonne

    ui->tableInfoEntreprise->setColumnCount(NbColonne);

    query.exec("SELECT idEntreprise, nomEntreprise FROM Entreprise");

    int i(0);
    while (query.next())
    {
        for(int j(0); j<NbColonne;j++)
        {
            ui->tableInfoEntreprise->setItem(i,j, new QTableWidgetItem(query.value(j).toString()));
        }
        i++;
    }
   ui->tableInfoEntreprise->setHorizontalHeaderLabels(m_tableHeader);
   ui->tableInfoEntreprise->setSelectionBehavior(QAbstractItemView::SelectRows);
   ui->tableInfoEntreprise->setSelectionMode(QAbstractItemView::SingleSelection);

   connect(ui->validEntrepriseButton, SIGNAL(clicked(bool)), this, SLOT(valideEntreprise()));
   connect(ui->buttonNewEnt,SIGNAL(clicked(bool)),this,SLOT(startNewEnt()));
}

void InfoEntreprise::startNewEnt(){
    TheNewEntreprise *NewPage = new TheNewEntreprise(Nom,Prenom);
    NewPage->exec();
}

void InfoEntreprise::valideEntreprise()
{
    QList<QTableWidgetItem*> recept = ui->tableInfoEntreprise->selectedItems();
    if(recept.isEmpty()==false)
    {
        infoProjetEntreprise(recept.value(0)->text());
    }
    else
    {
        QMessageBox::information(this, "Pas d'entreprise selectionné ! ", "Veuillez selectionner une entreprise");
    }


}

void InfoEntreprise::infoProjetEntreprise(QString idEntreprise)
{
    QSqlQuery query;

    query.exec("SELECT count(idProjet) FROM Projet WHERE idEntre ="+idEntreprise);
    query.next();

    ui->tableDesProjEntreprise->setRowCount(query.value(0).toInt());
    m_tableHeaderProjEntre<<"Numero Projet"<<"Titre Projet"<<"Nom Responsable"
                <<"Statut"<<"dateDebut"<<"dateFin"<<"avancement Projet";
    int NbColonne = 7;
    ui->tableDesProjEntreprise->setColumnCount(NbColonne);

    query.exec("SELECT idProjet, titreProjet, nomMembre as Nom_Responsable, P.statut as statut, dateDebut, dateFin, avancement FROM Projet P, User U WHERE P.idResponsable = U.idMembre AND idEntre ="+idEntreprise);

    int i(0);

    while(query.next())
    {
        for(int j(0);j<NbColonne;j++)
        {
            ui->tableDesProjEntreprise->setItem(i,j, new QTableWidgetItem(query.value(j).toString()));
        }
        i++;
    }


    ui->tableDesProjEntreprise->setHorizontalHeaderLabels(m_tableHeaderProjEntre);
    ui->tableDesProjEntreprise->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableDesProjEntreprise->setSelectionMode(QAbstractItemView::SingleSelection);
}

void    InfoEntreprise::LoadInfo(){
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

InfoEntreprise::~InfoEntreprise()
{
    delete ui;
}
