#include "thenewconv.h"
#include "ui_thenewconv.h"
#include "convention.h"
#include "pdffacture.h"
#include <vector>
#include <iostream>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDesktopServices>

TheNewConv::TheNewConv(QString Nom, QString Prenom, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TheNewConv)
{
    ui->setupUi(this);
    this->Prenom = Prenom;
    this->Nom = Nom;
    LoadInfo();
    QValidator *qv = new QIntValidator(0,9999999,this);
    ui->lineProjectPrix->setValidator(qv);
    // Signaux des boutons
    connect(ui->ValidButton,SIGNAL(clicked()),this,SLOT(CreateConvention()));

    // Initialisation de la viewtable de gauche
    QSqlQuery query;
    // Récupération du nombre de lignede la table user
    query.exec("SELECT count(*) FROM USER");
    query.next();
    ui->SelectRespTable->setRowCount(query.value(0).toInt());
    //ui->SelectTeamTable->setRowCount(query.value(0).toInt());
    // Penser à modifier en fonction de la table
    m_tableHeader<<"id"<<"Nom"<<"Prenom";
    int NbColonne = 3; // rentrer ici le nombre de colonne
    ui->SelectRespTable->setColumnCount(NbColonne);
    //ui->SelectTeamTable->setColumnCount(NbColonne);
    // Remplissage
    query.exec("SELECT idMembre, nomMembre, prenomMembre FROM USER");
    int i =0;
    while (query.next()){
        for (int j=0;j<NbColonne;j++){
            ui->SelectRespTable->setItem(i,j,new QTableWidgetItem(query.value(j).toString()));
            //ui->SelectTeamTable->setItem(i,j,new QTableWidgetItem(query.value(j).toString()));
        }
        i++;
    }
    // Caractéristiques de la table
    ui->SelectRespTable->setHorizontalHeaderLabels(m_tableHeader);
    ui->SelectRespTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->SelectRespTable->setSelectionMode(QAbstractItemView::SingleSelection);
    //ui->SelectTeamTable->setHorizontalHeaderLabels(m_tableHeader); // pour la team
    //ui->SelectTeamTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->SelectTeamTable->setSelectionMode(QAbstractItemView::MultiSelection);
    // usefull : https://wiki.qt.io/How_to_Use_QTableWidget

    // On rempli la table ETUDIANT
    query.exec("SELECT count(*) FROM Etudiant");
    query.next();
    ui->SelectTeamTable->setRowCount(query.value(0).toInt());
    m_tableHeaderEtu<<"Numero Etudiant"<<"Nom Etudiant"<<"Prenom Etudiant";
    NbColonne = 3;
    ui->SelectTeamTable->setColumnCount(NbColonne);
    query.exec("SELECT idEtu, nomEtu, prenomEtu FROM Etudiant");
    i=0;
    while (query.next())
    {
        for(int j(0); j<NbColonne;j++)
        {
            ui->SelectTeamTable->setItem(i,j ,new QTableWidgetItem(query.value(j).toString()));

        }
        i++;
    }

    ui->SelectTeamTable->setHorizontalHeaderLabels(m_tableHeaderEtu);
    ui->SelectTeamTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->SelectTeamTable->setSelectionMode(QAbstractItemView::MultiSelection);

    // On remplit la QTable pour entreprise
    query.exec("SELECT count(*) FROM Entreprise");
    query.next();
    ui->tableEntreprise->setRowCount(query.value(0).toInt());
    m_tableHeaderEnt<<"numero Entreprise"<<"Nom Entreprise";
    NbColonne = 2; // rentrer ici le nombre de colonne
    ui->tableEntreprise->setColumnCount(NbColonne);
    query.exec("SELECT idEntreprise, nomEntreprise FROM Entreprise");
    i=0;
    while (query.next())
    {
        for(int j(0); j<NbColonne;j++)
        {
            ui->tableEntreprise->setItem(i,j, new QTableWidgetItem(query.value(j).toString()));
        }
        i++;
    }
   ui->tableEntreprise->setHorizontalHeaderLabels(m_tableHeaderEnt);
   ui->tableEntreprise->setSelectionBehavior(QAbstractItemView::SelectRows);
   ui->tableEntreprise->setSelectionMode(QAbstractItemView::SingleSelection);
}

TheNewConv::~TheNewConv()
{
    delete ui;
}

void TheNewConv::CreateConvention(){
    QSqlQuery query;
    std::vector<std::string> TeamProjet;
    std::string RespoProjet;
    std::string Ent;
    int montant=0;
    // Stockage de la selection du responsable
    QList<QTableWidgetItem*> Recep = ui->SelectRespTable->selectedItems();
    QList<QTableWidgetItem*> Recep2 = ui->tableEntreprise->selectedItems();
    QList<QTableWidgetItem*> Recep3 = ui->SelectTeamTable->selectedItems();

    if(Recep.isEmpty()==false && Recep2.isEmpty()==false && Recep3.isEmpty()==false)
    {
        RespoProjet = Recep.value(1)->text().toStdString();

            Ent = Recep2.value(1)->text().toStdString();
            //ui->StatutLabel->setText( Recep.value(0)->text()); // test d'affichage
            // Stockage de l'équipe du projet
             // faire gaffe nombre de valeurs


                for (int i=1;i<Recep3.length();i+=3)
                {
                    TeamProjet.push_back(Recep3.value(i)->text().toStdString());
                }
                // Gestion des Id
                int nbIdConv;
                int nbIdProj;
                query.exec("SELECT max(idConvention) FROM Convention");
                if (query.next())
                {
                    nbIdConv = query.value(0).toInt() + 1;
                }
                else
                {
                    nbIdConv = 1 ;
                }
                query.exec("SELECT max(idProjet) FROM Projet");
                if (query.next())
                {
                    nbIdProj = query.value(0).toInt() + 1;
                }
                else
                {
                    nbIdProj = 1 ;
                }
                int nbIdFact;
                query.exec("SELECT max(numFacture)) FROM Travail");
                if (query.next()){
                    nbIdFact = query.value(0).toInt() + 1;
                }
                else{
                    nbIdFact = 1 ;
                }
                //Facture
                double taux=9.5;
                double tva=3.16; // pas oublier heure
                PdfFacture *pdfFact = new PdfFacture(nbIdConv,nbIdFact,ui->lineProjectName->text().toStdString(),nbIdConv,taux,ui->lineProjectPrix->text().toInt(),tva);
                if(!pdfFact->validerDocument()){
                    QMessageBox::question(this,"Probleme de Template","Le template de la convention est invalide, il va ainsi être regénéré.");
                    pdfFact->reecrireTemplate();
                    pdfFact->pdfbaseTemplate();
                }
                pdfFact->initCreat();
                // Finalité
                QString nomProjet = ui->lineProjectName->text();
                QDate dateProj = ui->dateProject->date();
                QString heure = ui->lineProjectPrix->text();

                if(nomProjet.contains(QRegExp("^[A-Za-z]+$")) && parseDate(dateProj) && heure.contains(QRegExp("^[0-9]+$")))
                {

                    Convention *newConv = new Convention(nbIdConv, nbIdProj,
                                                         ui->lineProjectName->text().toStdString(),
                                                        Ent,
                                                         RespoProjet,
                                                        TeamProjet.size(),
                                                         ui->dateProject->date().toString().toStdString(),
                                                        TeamProjet,
                                                         pdfFact->getPrixTTC());


                    if(!newConv->validerDocument())
                    {
                        QMessageBox::question(this,"Probleme de Template","Le template de la convention est invalide, il va ainsi être regénéré.");
                        newConv->reecrireTemplate();
                        newConv->pdfbaseTemplate();
                    }
                    newConv->initCreat();
                    // Ouverture des PDF
                    QDesktopServices::openUrl(QUrl::fromLocalFile(QString::fromStdString(pdfFact->CreateNom())));
                    QDesktopServices::openUrl(QUrl::fromLocalFile(QString::fromStdString(newConv->CreateNom())));
                    //traitement de la date
                    std::string datou= ui->dateProject->text().toStdString();
                    datou = datou.substr(6,4)+"-"+datou.substr(3,2)+"-"+datou.substr(0,2);
                    AddConvToBDD(QString::number(nbIdConv),QString::number(nbIdProj),"NON VALIDE",QString::number(pdfFact->getPrixTTC()),nbIdProj,QString::fromStdString(datou));

                }
                else if(parseDate(dateProj)==false)
                {
                    QMessageBox::information(this, "Problème de date", "Veuillez entrer une date supérieur à la date actuelle");
                }
                else if(!nomProjet.contains(QRegExp("^[A-Za-z]+$")))
                {
                    QMessageBox::information(this, "Nom de Projet vide", "Veuillez entrer un nom de projet(le nom ne doit pas commencer par un espace)");
                }
                else
                {
                    QMessageBox::information(this, "Champ heure estimée vide", "Veullez entrez un nombre d'heure de travail");
                }
          }
    else
    {
        QMessageBox::information(this, "Champ non Selectionnés !", "Vous n'avez pas selectionné tous les champs requis");
    }
    /*QSqlQuery query;
    std::vector<std::string> TeamProjet;
    std::string RespoProjet;
    std::string Ent;
    int montant=0;
    // Stockage de la selection du responsable
    QList<QTableWidgetItem*> Recep = ui->SelectRespTable->selectedItems();
    RespoProjet = Recep.value(1)->text().toStdString(); // REspo projet
    Recep = ui->tableEntreprise->selectedItems();
    Ent = Recep.value(1)->text().toStdString(); // Entreprise
    //ui->StatutLabel->setText( Recep.value(0)->text()); // test d'affichage
    // Stockage de l'équipe du projet
    Recep = ui->SelectTeamTable->selectedItems(); // faire gaffe nombre de valeurs fdp
    for (int i=1;i<Recep.length();i+=3){
        TeamProjet.push_back(Recep.value(i)->text().toStdString());
    }
    // Gestion des Id
    int nbIdConv;
    int nbIdProj;
    query.exec("SELECT max(idConvention) FROM Convention");
    if (query.next()){
        nbIdConv = query.value(0).toInt() + 1;
    }
    else{
        nbIdConv = 1 ;
    }
    query.exec("SELECT max(idProjet) FROM Projet");
    if (query.next()){
        nbIdProj = query.value(0).toInt() + 1;
    }
    else{
        nbIdProj = 1 ;
    }
    // FActure
    int nbIdFact;
    query.exec("SELECT max(numFacture)) FROM Travail");
    if (query.next()){
        nbIdFact = query.value(0).toInt() + 1;
    }
    else{
        nbIdFact = 1 ;
    }
    double taux=5.0;
    double tva=6.0; // pas oublier heure
    PdfFacture *pdfFact = new PdfFacture(nbIdConv,nbIdFact,ui->lineProjectName->text().toStdString(),nbIdConv,taux,45,tva);
    if(!pdfFact->validerDocument()){
        QMessageBox::question(this,"Probleme de Template","Le template de la convention est invalide, il va ainsi être regénéré.");
        pdfFact->reecrireTemplate();
        pdfFact->pdfbaseTemplate();
    }
    pdfFact->initCreat();


    // Finalité
    Convention *newConv = new Convention(nbIdConv, nbIdProj,
                                         ui->lineProjectName->text().toStdString(),
                                        Ent,
                                         RespoProjet,
                                        TeamProjet.size(),
                                         ui->dateProject->date().toString().toStdString(),
                                        TeamProjet,
                                         pdfFact->getPrixTTC());


    if(!newConv->validerDocument()){
        QMessageBox::question(this,"Probleme de Template","Le template de la convention est invalide, il va ainsi être regénéré.");
        newConv->reecrireTemplate();
        newConv->pdfbaseTemplate();
    }
    newConv->initCreat();
    // Ouverture des PDF
    QDesktopServices::openUrl(QUrl::fromLocalFile(QString::fromStdString(pdfFact->CreateNom())));
    QDesktopServices::openUrl(QUrl::fromLocalFile(QString::fromStdString(newConv->CreateNom())));
    //traitement de la date
    std::string datou= ui->dateProject->text().toStdString();
    datou = datou.substr(6,4)+"-"+datou.substr(3,2)+"-"+datou.substr(0,2);
    AddConvToBDD(QString::number(nbIdConv),QString::number(nbIdProj),"NON VALIDE",QString::number(montant),nbIdProj,QString::fromStdString(datou));*/

}

// Ajout de la conv / projet à la BDD
void TheNewConv::AddConvToBDD(QString idConv,QString idProjet,QString Statut,QString montant,int nbIdProj,QString date)
{
    QSqlQuery query;
    // Projet
    QList<QTableWidgetItem*> Recep = ui->tableEntreprise->selectedItems();
    QString idEnt = Recep.value(0)->text();
    QString idRespo = Recep.value(0)->text();
    // Traitement sur la date à faire
    if(query.exec("INSERT INTO Projet VALUES("+idProjet+","+idEnt+",\""+ui->lineProjectName->text()+"\","+idRespo+","+montant+",\"En cours\",\""+date+"\",NULL,NULL)"))
    {
        QMessageBox::information(this,"TITRE","AJOUT Projet IS GOOD");
    }
    ui->AdressLabel->setText(montant);
    // Convention
    if(query.exec("INSERT INTO Convention VALUES("+idConv+","+idProjet+",\""+Statut+"\",NULL,NULL,"+montant+")"))
    {

        QMessageBox::information(this,"TITRE","AJOUT CONV IS GOOD");
    }

    // Travail
    int nbIdFact;
    query.exec("SELECT max(numFacture)) FROM Travail");
    if (query.next()){
        nbIdFact = query.value(0).toInt() + 1;
    }
    else{
        nbIdFact = 1 ;
    }
    Recep = ui->SelectTeamTable->selectedItems(); // faire gaffe nombre de valeurs
    // Nb facture en parametre checker bdd Clement
    for (int i=0;i<Recep.length();i+=3)
    {
        query.exec("INSERT INTO Travail VALUES("+ Recep.value(i)->text() +","+idProjet+",\"Commencement\","+QString::number(nbIdFact)+")");
    }
    // Convention . Projet . Travail
}

void TheNewConv::LoadInfo(){
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

bool TheNewConv::parseDate(QDate dateconv)
{
    if(dateconv < QDate::currentDate())
    {
        return false;
    }
    else
    {
        return true;
    }


}
