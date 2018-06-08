#ifndef THENEWENTREPRISE_H
#define THENEWENTREPRISE_H

#include <QDialog>

namespace Ui {
class TheNewEntreprise;
}

class TheNewEntreprise : public QDialog
{
    Q_OBJECT

public:
    explicit TheNewEntreprise(QString Nom,QString Prenom,QWidget *parent = 0);
    ~TheNewEntreprise();
    void LoadInfo();

public slots:
    void addEnt();

private:
    Ui::TheNewEntreprise *ui;
    QString Nom;
    QString Prenom;
};

#endif // THENEWENTREPRISE_H
