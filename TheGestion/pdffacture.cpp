#include "pdffacture.h"
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
using namespace std;


     PdfFacture::PdfFacture(int numProjet, int numFacture,std::string nomProjet,int numConv, double tauxHauraire, int nbHeure,double TVA)
       {
         f_numProjet=numProjet;
         f_numFacture=numFacture;
         f_numConv=numConv;
         f_nomProjet=nomProjet;
         f_tauxHauraire=tauxHauraire;
         f_nbHeure=nbHeure;
         f_TVA=TVA;


         f_prixHT=nbHeure*tauxHauraire;
         int y = 100*f_prixHT;
         f_prixHT= (double)y/100;

         f_prixTTC=f_prixHT+f_prixHT*f_TVA/100;
         y = 100*f_prixTTC;
         f_prixTTC= (double)y/100;


     }






    void PdfFacture::reecrireTemplate()
    {
       /*nous commencon par supprimer le fichier, si il n'existe pas alors rien ne se passe*/
        if( remove( "./templateFacture.txt" ) != 0 )
            perror( "Error deleting file" );
          else
            puts( "File successfully deleted" );

        /*creation du projet*/
          FILE * pFile;
           pFile = fopen ( "templateFacture.txt" ,"w");
           if (pFile!=NULL)
           {
             fputs ("Facture numero :  <numFacture>\n\nProjet : <numProjet> <nomProjet>\nNumero de conventon : <numConv>\nmontant de la TVA : <TVA>\ntaux hauraire : <tauxHauraire>\nnombre d\'heure : <nbHeure>\nprix HT : <prixHT>\nprix TTC : <prixTTC> ",pFile);
             fclose (pFile);
           }




    }


       void PdfFacture::pdf(QString filename)
       {
           QPdfWriter writer(filename);
           writer.setPageSize(QPagedPaintDevice::A4);
           writer.setPageMargins(QMargins(30, 30, 30, 30));


           QPainter painter(&writer);
           painter.setPen(Qt::black);

           painter.setFont(QFont("Times", 10,QFont::Bold));


           QRect r = painter.viewport();


           QString pdfFacture = QString::fromStdString(f_strFacture);

           painter.setFont(QFont("Times", 10));
           painter.drawText(r, Qt::AlignLeft, pdfFacture);

           painter.end();
       }




      void PdfFacture::pdfbaseTemplate()
       {
           //string const nomFichier("C:\\Users\\clem\\Documents\\AS\\gpoo\\git\\CpooJuniorEntreprise\\templateFacture.txt");
          string const nomFichier("./templateFacture.txt");
          ifstream monFlux(nomFichier.c_str());
           if(monFlux)
           {
               string ligne2;
                getline(monFlux, ligne2);
                 f_strFacture=ligne2;

               while(getline(monFlux, ligne2)) //Tant qu'on n'est pas à la fin, on lit
               {
                   f_strFacture=f_strFacture+"\n"+ligne2;
               }
               //return true;


           }
           else
           {
               std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
               //return false

           }
       }

       bool PdfFacture::validerDocument()
       {
           pdfbaseTemplate();
           if(f_strFacture.find("<numConv>") == string::npos)return false;

           if(f_strFacture.find("<numProjet>") == string::npos) return false;
           if(f_strFacture.find("<numFacture>") == string::npos)return false;
           if(f_strFacture.find("<nomProjet>") == string::npos)return false;
           if(f_strFacture.find("<TVA>") == string::npos)return false;
           if(f_strFacture.find("<tauxHauraire>") == string::npos)return false;
           if(f_strFacture.find("<nbHeure>") == string::npos)return false;

           if(f_strFacture.find("<prixHT>") == string::npos)return false;

           if(f_strFacture.find("<prixTTC>") == string::npos)return false;
            std::cout<<"ok"<<std::endl;
           return true;
       }


       string PdfFacture::to_string(int aStringer)
       {
           ostringstream convert;
           convert << aStringer;
           return convert.str();
       }



      void PdfFacture::preparerPdfFactureStr()
       {
          f_strFacture.replace(f_strFacture.find("<TVA>"),5,to_string(f_TVA));
          f_strFacture.replace(f_strFacture.find("<tauxHauraire>"),14,to_string( f_tauxHauraire));
          f_strFacture.replace(f_strFacture.find("<nbHeure>"),9,to_string(f_nbHeure));
          f_strFacture.replace(f_strFacture.find("<prixHT>"),8,to_string(f_prixHT));
          f_strFacture.replace(f_strFacture.find("<numFacture>"),12,to_string(f_numFacture));
          f_strFacture.replace(f_strFacture.find("<prixTTC>"),9,to_string(f_prixTTC));
          f_strFacture.replace(f_strFacture.find("<numProjet>"),11,to_string(f_numProjet));
          f_strFacture.replace(f_strFacture.find("<nomProjet>"),11,f_nomProjet);
          f_strFacture.replace(f_strFacture.find("<numConv>"),9,to_string(f_numConv));

       }

      string PdfFacture::CreateNom()
      {
          return "Facture"+to_string(f_numConv)+"_"+to_string(f_numFacture)+".pdf";
      }

      string PdfFacture::getStrFacture()
      {
          return f_strFacture;
      }

      void PdfFacture::initCreat()
      {
          if(validerDocument())
          {
                preparerPdfFactureStr();
                pdf(QString::fromStdString(CreateNom()));
          }
          else std::cout<<"problem : document inexistant ou invalide"<<std::endl;

      }

      double PdfFacture::getPrixTTC(){ return f_prixTTC;}
