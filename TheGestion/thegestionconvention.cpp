#include "thegestionconvention.h"
#include "ui_thegestionconvention.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>

TheGestionConvention::TheGestionConvention(QString Nom, QString Prenom, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TheGestionConvention)
{
    ui->setupUi(this);
    this->Nom=Nom;
    this->Prenom=Prenom;
    LoadInfo();
    QSqlQuery query;

    query.exec("SELECT count(*) FROM Convention");
    query.next();
    ui->tableConvention->setRowCount(query.value(0).toInt());
    m_tableHeader<<"numero convention"<<"titre projet"<<"nom entreprise"<<"statut"<<"date debut";
    int NbColonne = 5; // rentrer ici le nombre de colonne
    ui->tableConvention->setColumnCount(NbColonne);

    query.exec("SELECT idConvention, titreProjet, nomEntreprise, C.statut, dateDebut FROM Convention C, Projet P, Entreprise E WHERE P.idProjet = C.numProjet AND P.idEntre = E.idEntreprise");
    int i(0);
    while (query.next())
    {
        for(int j(0); j<NbColonne;j++)
        {
            ui->tableConvention->setItem(i,j, new QTableWidgetItem(query.value(j).toString()));
        }
        i++;
    }
   ui->tableConvention->setHorizontalHeaderLabels(m_tableHeader);
   ui->tableConvention->setSelectionBehavior(QAbstractItemView::SelectRows);
   ui->tableConvention->setSelectionMode(QAbstractItemView::SingleSelection);

   connect(ui->buttonValiderConv,SIGNAL(clicked(bool)),this,SLOT(ValidConvention()));
}

TheGestionConvention::~TheGestionConvention()
{
    delete ui;
}

void TheGestionConvention::ValidConvention(){
    QList<QTableWidgetItem*> Recep = ui->tableConvention->selectedItems();
    if(Recep.isEmpty()==false)
    {
        QString idConv = Recep.value(0)->text();
        QSqlQuery query;
        if(query.exec("UPDATE Convention SET Statut=\"VALIDE\" WHERE idConvention="+idConv))
        {
            QMessageBox::information(this,"Convention","CONVENTION VALIDEE !");
        }

    }
    else
    {
        QMessageBox::information(this, "Pas de convention selectionnée ", "Veuillez selectionner une convention");
    }

}

void TheGestionConvention::LoadInfo(){
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
