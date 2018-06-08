#ifndef THEFENETRE_H
#define THEFENETRE_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLCDNumber>
#include <QSlider>
#include <QProgressBar>
#include <QMessageBox>

class TheFenetre : public QDialog // herite de QWidget
{
    // Pour creer slot
    Q_OBJECT

    public :
    TheFenetre();

    public slots:
    void changerLargeur(int largeur);
    void changerHauteur(int hauteur);
    void ouvrirDialogue();

    signals :
    void agrandMax();

    private :
    QLCDNumber *m_lcd;
    QSlider *m_slider;
    QProgressBar *m_progress;
    QPushButton *m_bouton;
    QSlider *m_slider_hauteur;
    QPushButton *m_boutonDialogue;
};


#endif // THEFENETRE_H
