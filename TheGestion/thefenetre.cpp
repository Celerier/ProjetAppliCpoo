#include "thefenetre.h"

// Constructeur de fenetre
TheFenetre::TheFenetre() : QDialog()
{
    setFixedSize(300, 300);

    m_bouton = new QPushButton("The Reset", this);
    m_boutonDialogue = new QPushButton("Ouvrir la boite de pandore",this);

    m_bouton->setFont(QFont("Comic Sans MS",13));
    m_bouton->setCursor(Qt::PointingHandCursor);
    m_bouton->setIcon(QIcon("perso.png"));
    m_bouton->move(180,50);

    m_boutonDialogue->move(140,50);

    //QObject::connect(m_bouton,SIGNAL(clicked()),m_slider,SLOT());
   // QObject::connect(m_bouton, SIGNAL(clicked()), qApp,SLOT(quit()));

    m_lcd = new QLCDNumber(this);
    m_lcd->setSegmentStyle(QLCDNumber::Flat);
    m_lcd->move(50,20);

    m_slider = new QSlider(Qt::Horizontal, this);
    m_slider->setRange(200,600);
    m_slider->setGeometry(10,60,150,20);

    m_progress = new QProgressBar(this);
    m_progress->setGeometry(10,60,150,20);
    m_progress->move(50,90);
    m_progress->setValue(20);

    m_slider_hauteur = new QSlider(Qt::Vertical, this);
    m_slider_hauteur->setRange(200,600);
    m_slider_hauteur->setGeometry(200,75,20,150);

    // Connection des signal et slot
    QObject::connect(m_slider, SIGNAL(valueChanged(int)),m_progress,SLOT(setValue(int)));
    QObject::connect(m_slider, SIGNAL(valueChanged(int)),this,SLOT(changerLargeur(int))); // Change largeur
    QObject::connect(m_slider_hauteur,SIGNAL(valueChanged(int)),this,SLOT(changerHauteur(int)));
    QObject::connect(m_bouton,SIGNAL(clicked()),m_progress,SLOT(reset())); // remet à 0
    QObject::connect(m_slider, SIGNAL(valueChanged(int)),m_lcd,SLOT(display(int)));
    QObject::connect(this,SIGNAL(agrandMax()),qApp,SLOT(quit())); // ferme si largeur == 600
    QObject::connect(m_boutonDialogue,SIGNAL(clicked()),this,SLOT(ouvrirDialogue()));
}

// SLOT
void TheFenetre::changerLargeur(int largeur){
    setFixedSize(largeur,this->height());
    if (largeur==600){
        emit agrandMax();
    }
}

void TheFenetre::changerHauteur(int hauteur){
    setFixedSize(this->width(),hauteur);
}

void TheFenetre::ouvrirDialogue(){
    // warning / critical / question
    int reponse = QMessageBox::information(this,"Ce genre de Titre","Ce genre de boite, mamene ?", QMessageBox::Yes | QMessageBox::No);

    if (reponse==QMessageBox::Yes){
        QMessageBox::warning(this,"Waaaalah","t\'es un mamene toi");
    }
}
