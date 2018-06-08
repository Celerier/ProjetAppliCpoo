#ifndef THECHOOSE_H
#define THECHOOSE_H

#include <QDialog>

namespace Ui {
class TheChoose;
}

class TheChoose : public QDialog
{
    Q_OBJECT

public:
    explicit TheChoose(QString Nom, QString Prenom,QWidget *parent = 0);
    ~TheChoose();
    void LoadInfo();

public slots:
    void startNewProjet();
    void affichageEntreprise();
    void startInfoEtu();
    void startInfoProjet();
    void startGeneral();
    void startGestionConv();

private:
    Ui::TheChoose *ui;
    QString Nom;
    QString Prenom;

};

#endif // THECHOOSE_H
