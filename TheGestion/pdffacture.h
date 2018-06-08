#ifndef PdfFacture_H
#define PdfFacture_H
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

class PdfFacture : public QObject
{

private:
    int f_numProjet;
    std::string f_nomProjet;
    int f_numFacture;
    int f_numConv;
    double f_tauxHauraire;
    int f_nbHeure;
    double f_TVA;
    double f_prixHT;
    double f_prixTTC;


    std::string f_strFacture;


public:

    PdfFacture(int numProjet,  int numFacture, std::string nomProjet, int numConv, double tauxHauraire, int nbHeure , double TVA);
       double getPrixTTC();
       QString currDate();
       /*cree le pdf*/
       void pdf(QString filename);
       /*cree la string pour le pdf*/
       void pdfbaseTemplate();
       /*s'assure que le template est valide en cas de modification*/
       bool validerDocument();
       string to_string(int aStringer);
       /*transformae la string avec les valeurs voulues*/
       void preparerPdfFactureStr();

       string getStrFacture();
       void reecrireTemplate();

       void initCreat();

       string CreateNom();
};

#endif // PdfFacture_H
