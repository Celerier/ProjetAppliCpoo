#ifndef CONVENTION_H
#define CONVENTION_H

#include <QApplication>

#include <string>

#include <QPushButton>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <QtCore>
#include <QPrinter>
#include <QPdfWriter>
#include <QPainter>
#include <sstream>
#include <vector>

using namespace std;

class Convention : public QObject
{

private:
    int c_numConvention;
    int c_numProjet;
    int c_prix;
    std::string c_titrePtojet;
    std::string c_nomEntreprise;
    std::string c_nomResponsable;
    int c_nombreEtudiant;
    //std::string c_listeEtudiant[10];
    std::vector<string> c_listeEtudiant;
    std::string c_dateDeb;
    std::string strConv;
   // std::vector<std::string> c_listeEtudiant;


public:
   // Convention();
       Convention( int numConvention, int numProjet, string titrePtojet, string nomEntreprise, string nomResponsable, int nombreEtudiant, string dateDeb, std::vector<std::string> listeEtudiant, int prix);

       QString currDate();
       /*cree le pdf*/
       void pdf(QString filename);

       /*cree la string pour le pdf*/
       void pdfbaseTemplate();

       /*s'assure que le template est valide en cas de modification*/
       bool validerDocument();


       string to_string(int aStringer);

       /*transformae la string avec les valeurs voulues*/
       void preparerConventionStr();


       string getStrConv();

       void initCreat();

       void reecrireTemplate();

       string CreateNom();

};

#endif // CONVENTION_H
