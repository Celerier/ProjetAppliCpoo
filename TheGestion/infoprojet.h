#ifndef INFOPROJET_H
#define INFOPROJET_H

#include <QDialog>


namespace Ui {
class InfoProjet;
}

class InfoProjet : public QDialog
{
    Q_OBJECT

public:
    explicit InfoProjet(QString Nom, QString Prenom,QWidget *parent = 0);
    ~InfoProjet();

    void infoProjetPreci(QString idProjet);
    void LoadInfo();
public slots:

    void valideProjet();
private:
    Ui::InfoProjet *ui;
    QStringList m_tableHeader;
    QStringList m_tableHeaderProjetPreci;
    QString Nom;
    QString Prenom;
};

#endif // INFOPROJET_H
