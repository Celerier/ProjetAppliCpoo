#ifndef INFOENTREPRISE_H
#define INFOENTREPRISE_H

#include <QDialog>
#include <QtSql>
#include <string>

namespace Ui {
class InfoEntreprise;
}

class InfoEntreprise : public QDialog
{
    Q_OBJECT

public:
    explicit InfoEntreprise(QString Nom, QString Prenom,QWidget *parent = 0);
    ~InfoEntreprise();
    void infoProjetEntreprise(QString idEntreprise);
    void LoadInfo();

public slots:

    void valideEntreprise();
    void startNewEnt();

private:
    Ui::InfoEntreprise *ui;
    QStringList m_tableHeader;
    QStringList m_tableHeaderProjEntre;
    QString Nom;
    QString Prenom;
};

#endif // INFOENTREPRISE_H
