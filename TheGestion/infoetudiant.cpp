#include "infoetudiant.h"
#include "ui_infoetudiant.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>

infoEtudiant::infoEtudiant(QString Nom, QString Prenom, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::infoEtudiant)
{
    ui->setupUi(this);
    this->Prenom = Prenom;
    this->Nom = Nom;
    LoadInfo();
    QSqlQuery query;

    query.exec("SELECT count(*) FROM Etudiant");
    query.next();

    ui->tableEtudiant->setRowCount(query.value(0).toInt());

    m_tableHeader<<"Numero Etudiant"<<"Nom Etudiant"<<"Prenom Etudiant";

    int NbColonne = 3;

    ui->tableEtudiant->setColumnCount(NbColonne);

    query.exec("SELECT idEtu, nomEtu, prenomEtu FROM Etudiant");

    int i(0);
    while (query.next())
    {
        for(int j(0); j<NbColonne;j++)
        {
            ui->tableEtudiant->setItem(i,j ,new QTableWidgetItem(query.value(j).toString()));

        }
        i++;
    }

    ui->tableEtudiant->setHorizontalHeaderLabels(m_tableHeader);
    ui->tableEtudiant->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableEtudiant->setSelectionMode(QAbstractItemView::SingleSelection);

     connect(ui->validEtudiantButton, SIGNAL(clicked(bool)), this, SLOT(valideEtudiant()));
}

void infoEtudiant::valideEtudiant()
{
    QList<QTableWidgetItem*> recept = ui->tableEtudiant->selectedItems();
    if(recept.isEmpty()==false)
    {
        infoProjetEtudiant(recept.value(0)->text());
        infoEtudiantPreci(recept.value(0)->text());
    }
    else
    {
        QMessageBox::information(this, "Pas d'étudiant selectionné ! ", "Veuillez selectionner un étudiant");
    }

}


void infoEtudiant::infoProjetEtudiant(QString idEtudiant)
{
    QSqlQuery query;

    query.exec("SELECT count(idProjet) FROM Projet P, Travail T, Etudiant E WHERE P.idProjet = T.idProj AND T.idEtudiant = E.idEtu AND idEtu = "+idEtudiant);
    query.next();



    ui->tableDesProjEtudiant->setRowCount(query.value(0).toInt());

    m_tableHeaderProjEtudiant<<"Numero Projet"<<"Titre Projet"<<"Statut"<<"Nom Responsable"<<"Nom Entreprise"<<"Statut du Travail";

    int NbColonne = 6;

    ui->tableDesProjEtudiant->setColumnCount(NbColonne);

    query.exec("SELECT idProjet, titreProjet, P.statut, nomMembre , nomEntreprise, T.statut as Statut_du_Travail FROM Projet P, Travail T, Etudiant E, Entreprise EN, User U WHERE P.idProjet = T.idProj AND T.idEtudiant = E.idEtu AND U.idMembre = P.idResponsable AND P.idEntre = EN.idEntreprise AND E.idEtu="+idEtudiant);

    int i(0);

    while(query.next())
    {
        for(int j(0);j<NbColonne;j++)
        {
            ui->tableDesProjEtudiant->setItem(i,j, new QTableWidgetItem(query.value(j).toString()));
        }
        i++;
    }


    ui->tableDesProjEtudiant->setHorizontalHeaderLabels(m_tableHeaderProjEtudiant);
    ui->tableDesProjEtudiant->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableDesProjEtudiant->setSelectionMode(QAbstractItemView::SingleSelection);
}

void infoEtudiant::infoEtudiantPreci(QString idEtu)
{
    QSqlQuery query;

    query.exec("SELECT * FROM Etudiant WHERE idEtu ="+idEtu);

    int i(0);

    query.next();

    ui->numeroEtudiant->setText(query.value("idEtu").toString());
    ui->nomEtu->setText(query.value("nomEtu").toString());
    ui->prenomEtu->setText(query.value("prenomEtu").toString());
    ui->promoEtu->setText(query.value("promotion").toString());
    ui->telEtu->setText(query.value("telEtu").toString());
    ui->mailEtu->setText(query.value("mailEtu").toString());
    ui->adresseEtu->setText(query.value("adresseEtu").toString());


}

void infoEtudiant::LoadInfo(){
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

infoEtudiant::~infoEtudiant()
{
    delete ui;
}
