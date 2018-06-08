#ifndef INFOETUDIANT_H
#define INFOETUDIANT_H

#include <QDialog>
#include <string>

namespace Ui {
class infoEtudiant;
}

class infoEtudiant : public QDialog
{
    Q_OBJECT

public:
    explicit infoEtudiant(QString Nom, QString Prenom,QWidget *parent = 0);
    ~infoEtudiant();
    void infoProjetEtudiant(QString idEtudiant);
    void LoadInfo();
    void infoEtudiantPreci(QString idEtu);

public slots:

    void valideEtudiant();

private:
    Ui::infoEtudiant *ui;
    QStringList m_tableHeader;
    QStringList m_tableHeaderProjEtudiant;
    QString Nom;
    QString Prenom;

};

#endif // INFOETUDIANT_H
