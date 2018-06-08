#include "infoprojet.h"
#include "ui_infoprojet.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>

InfoProjet::InfoProjet(QString Nom, QString Prenom, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoProjet)
{
    ui->setupUi(this);
    this->Prenom = Prenom;
    this->Nom = Nom;
    LoadInfo();
    QSqlQuery query;

    query.exec("SELECT count(*) FROM Projet");
    query.next();

    ui->tableProjet->setRowCount((query.value(0).toInt()));

    m_tableHeader <<"Numero"<<"Nom Entreprise"<<"Titre"<<"Statut"<<"prix";

    int NbColonne = 5;

    ui->tableProjet->setColumnCount(NbColonne);

    query.exec("SELECT idProjet, nomEntreprise, titreProjet, P.statut, prix FROM Projet P, Entreprise E WHERE P.idEntre=E.idEntreprise");

    int i(0);

    while (query.next())
    {
        for (int j(0); j<NbColonne;j++)
        {
            ui->tableProjet->setItem(i,j, new QTableWidgetItem(query.value(j).toString()));

        }
        i++;
    }

    ui->tableProjet->setHorizontalHeaderLabels(m_tableHeader);
    ui->tableProjet->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableProjet->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(ui->valideProjetButton, SIGNAL(clicked(bool)), this, SLOT(valideProjet()));
 }

void InfoProjet::infoProjetPreci(QString idProjet)
{
    QSqlQuery query;

    query.exec("SELECT count(idEtudiant) FROM travail WHERE idProj ="+idProjet);
    query.next();

    ui->tableProjetPreci->setRowCount(query.value(0).toInt());

    m_tableHeaderProjetPreci<<"Numero Etudiant"<<"Nom Etudiant"<<"Prenom Etudiant"<<"Statut du Travail";

    int NbColonne(4);

    ui->tableProjetPreci->setColumnCount(NbColonne);

    query.exec("SELECT idEtu, nomEtu, prenomEtu, statut FROM Etudiant E, Travail T WHERE E.idEtu = T.idEtudiant AND idProj ="+idProjet);

    int i(0);

    while(query.next())
    {
        for(int j(0); j<NbColonne;j++)
        {
            ui->tableProjetPreci->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
        }
        i++;
    }

    ui->tableProjetPreci->setHorizontalHeaderLabels(m_tableHeaderProjetPreci);
    ui->tableProjetPreci->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableProjetPreci->setSelectionMode(QAbstractItemView::SingleSelection);
}

void InfoProjet::valideProjet()
{
    QList<QTableWidgetItem*> recept = ui->tableProjet->selectedItems();

    if(recept.isEmpty()==false)
    {
        infoProjetPreci(recept.value(0)->text());

    }
    else
    {
        QMessageBox::information(this, "Pas de projet séléctionné ! ", "Veuillez selectionner un projet");
    }
}

void InfoProjet::LoadInfo(){
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

InfoProjet::~InfoProjet()
{
    delete ui;
}
