#ifndef THEPDF_H
#define THEPDF_H

#include <QString>

class ThePdf
{
public:
    ThePdf(QString filename/*,int numConvention, int numProjet, QString nomProjet, QString nomEntreprise, QString Etudiant[], QString Commentaire*/ );
    QString currDate();
};

#endif // THEPDF_H
