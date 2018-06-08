#include "convention.h"
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
#include <QMessageBox>

using namespace std;


     Convention::Convention(int numConvention, int numProjet, string titrePtojet, string nomEntreprise, string nomResponsable, int nombreEtudiant, string dateDeb,std::vector<std::string> listeEtudiant,int prix)
         {

         c_numConvention=numConvention;
         c_numProjet=numProjet;
         c_titrePtojet=titrePtojet;
         c_nomEntreprise=nomEntreprise;
         c_nomResponsable=nomResponsable;
          c_prix=prix;
          c_nombreEtudiant=nombreEtudiant;
          c_listeEtudiant=listeEtudiant;

           c_dateDeb=dateDeb;


       }

       QString Convention::currDate()
       {
           QDate date = QDate::currentDate();
           return date.toString("dd.MM.yyyy");
       }

       void Convention::pdf(QString filename)
       {
           QPdfWriter writer(filename);
           writer.setPageSize(QPagedPaintDevice::A4);
           writer.setPageMargins(QMargins(30, 30, 30, 30));


           QPainter painter(&writer);
           painter.setPen(Qt::black);

           painter.setFont(QFont("Times", 10,QFont::Bold));


           QRect r = painter.viewport();



           string titre(strConv,0,strConv.find("<T>"));
           QString qtitre = QString::fromStdString(titre);

           string corps(strConv,strConv.find("<T>")+3,strConv.size()-1);
           QString qcorps = QString::fromStdString(corps);

           painter.drawText(r, Qt::AlignHCenter, qtitre);
           painter.setFont(QFont("Times", 10));
           painter.drawText(r, Qt::AlignLeft, qcorps);

           painter.end();
       }

       void Convention::reecrireTemplate()
       {



           if( remove( "D:\\Cours\\IUT_info_Lyon_ASPE\\Programmation\\C++\\AppliSynthese\\template.txt" ) != 0 )
               perror( "Error deleting file" );
             else
               puts( "File successfully deleted" );
             FILE * pFile;

              pFile = fopen ( "D:\\Cours\\IUT_info_Lyon_ASPE\\Programmation\\C++\\AppliSynthese\\template.txt" ,"w");
              if (pFile!=NULL)
              {
                fputs ("Convention numero <numConv>\nrelative au projet numero <numProjet> : <titreProjet>\n\n\n\n<T>\n\n\n\n\nEntreprise : <nomEntreprise>\nResponsable de la junior entreprise : <nomResponsable>\n Dates debut du projet : <debutProjet>\nPrix du projet :<prix>\nLes etudiants sont\n<listeEtudiant> \n\n\n\n\n\n Commentaires :\n\n\n\nSignature et date\n\n Junior	                                         		entreprise",pFile);
                fclose (pFile);
              }




       }



      void Convention::pdfbaseTemplate()
       {
           string const nomFichier("D:\\Cours\\IUT_info_Lyon_ASPE\\Programmation\\C++\\AppliSynthese\\template.txt");

          ifstream monFlux(nomFichier.c_str());
           if(monFlux)
           {

               //string ligne;
               string ligne2;
               getline(monFlux, ligne2);
               strConv=ligne2;

               while(getline(monFlux, ligne2)) //Tant qu'on n'est pas à la fin, on lit
               {
                   strConv=strConv+"\n"+ligne2;
               }


           }
           else
           {
               std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;

           }
       }

       bool Convention::validerDocument()
       {
           pdfbaseTemplate();
           if(strConv.find("<numConv>") == string::npos)return false;

           if(strConv.find("<T>") == string::npos)return false;

           if(strConv.find("<numProjet>") == string::npos) return false;
           if(strConv.find("<titreProjet>") == string::npos) return false;
           if(strConv.find("<nomEntreprise>") == string::npos) return false;
           if(strConv.find("<debutProjet>") == string::npos)return false;
           if(strConv.find("<prix>") == string::npos)return false;
           if(strConv.find("<listeEtudiant>") == string::npos)return false;
           if(strConv.find("<nomResponsable>") == string::npos)return false;
           std::cout<<"bonjusque ici"<<std::endl;

            std::cout<<"bonjusque la"<<std::endl;
           //if(DocAValider.find("<commentaires>") == string::npos)return false;
           return true;
       }


       string Convention::to_string(int aStringer)
       {
           ostringstream convert;
           convert << aStringer;
           return convert.str();
       }



      void Convention::preparerConventionStr()
       {

           strConv.replace(strConv.find("<numConv>"),9,to_string(c_numConvention));
           strConv.replace(strConv.find("<numProjet>"),11,to_string(c_numProjet));
           strConv.replace(strConv.find("<titreProjet>"),13,c_titrePtojet);
           strConv.replace(strConv.find("<debutProjet>"),13,c_dateDeb);
           strConv.replace(strConv.find("<nomEntreprise>"),15,c_nomEntreprise);
           strConv.replace(strConv.find("<nomResponsable>"),16,c_nomResponsable);
           strConv.replace(strConv.find("<prix>"),6,to_string(c_prix));

           int positionEtd=strConv.find("<listeEtudiant>");
           strConv.replace(strConv.find("<listeEtudiant>"),15,"");
           for(int i=0; i<c_nombreEtudiant;i++)
           {
               strConv.insert(positionEtd ,"\n -"+c_listeEtudiant[i]);
           }
       }
      string Convention::CreateNom()
            {
                return "Convention"+to_string(c_numConvention)+"_"+to_string(c_numProjet)+".pdf";
            }


      string Convention::getStrConv()
      {
          return strConv;
      }

      void Convention::initCreat()
      {

          if(validerDocument())
          {

                preparerConventionStr();
                pdf(QString::fromStdString(CreateNom()));
          }
          else std::cout<<"problem : document inexistant ou invalide"<<std::endl;

      }
