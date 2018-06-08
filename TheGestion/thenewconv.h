#ifndef THENEWCONV_H
#define THENEWCONV_H

#include <QDialog>
#include <vector>
#include <iostream>
#include <string>

namespace Ui {
class TheNewConv;
}

class TheNewConv : public QDialog
{
    Q_OBJECT

public:
    explicit TheNewConv(QString Nom, QString Prenom,QWidget *parent = 0);
    ~TheNewConv();
    void LoadInfo();
    void AddConvToBDD(QString idConv,QString idProjet,QString Statut,QString montant,int nbIdProj,QString date);
    bool parseDate(QDate dateconv);


public slots :
    void CreateConvention();
private:
    Ui::TheNewConv *ui;
    QStringList m_tableHeader;
    QStringList m_tableHeaderEtu;
    QStringList m_tableHeaderEnt;
    QString Nom;
    QString Prenom;
};

#endif // THENEWCONV_H
