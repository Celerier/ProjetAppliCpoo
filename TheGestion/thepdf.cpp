#include "thepdf.h"
#include <QString>
#include <QtCore>
#include <QPrinter>
#include <QPdfWriter>
#include <QPainter>

ThePdf::ThePdf(QString filename/*,int numConvention, int numProjet, QString nomProjet, QString nomEntreprise, QString Etudiant[], QString Commentaire*/ )
{
    QPdfWriter writer(filename);
    writer.setPageSize(QPagedPaintDevice::A4);
    writer.setPageMargins(QMargins(30, 30, 30, 30));


    QPainter painter(&writer);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Times", 10));


    QRect r = painter.viewport();

    QString citydate = "City, ";
    citydate += currDate();

    painter.drawText(r, Qt::AlignRight, citydate);


    QString sender = "COMPANY XYZ\n";
    sender += "Random Street of Shambahla 12/314A\n";
    sender += "123-1232 City\n";

    painter.drawText(r, Qt::AlignLeft, sender);
    painter.end();

}

QString ThePdf::currDate()
{
    QDate date = QDate::currentDate();
    return date.toString("dd.MM.yyyy");
}
