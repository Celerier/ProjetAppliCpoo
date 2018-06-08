#ifndef THEACCEUIL_H
#define THEACCEUIL_H

#include <QMainWindow>
#include <QtWidgets>

class TheAcceuil : public QMainWindow
{
    Q_OBJECT
public:
    TheAcceuil();
    bool BBD_Connexion();


public slots:
    void co_admin();
    void co_etu();

private :
    QWidget *zoneCentrale;
    // Formulaire admin
    QLineEdit *login_admin;
    QLineEdit *mdp_admin;
    QPushButton *valid_admin;
    QFormLayout *form_admin;
    // Formulaire etudiant
    QLineEdit *login_etu;
    QLineEdit *mdp_etu;
    QPushButton *valid_etu;
    QFormLayout *form_etu;

    // Layout et Widget de mise en page
    QGridLayout *globalForm;
    QLabel *msg;


};

#endif // THEACCEUIL_H
