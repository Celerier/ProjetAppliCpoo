#ifndef THEGESTIONCONVENTION_H
#define THEGESTIONCONVENTION_H

#include <QDialog>

namespace Ui {
class TheGestionConvention;
}

class TheGestionConvention : public QDialog
{
    Q_OBJECT

public:
    explicit TheGestionConvention(QString Nom, QString Prenom,QWidget *parent = 0);
    ~TheGestionConvention();

    void LoadInfo();
public slots:

     void ValidConvention();

private:
    Ui::TheGestionConvention *ui;
    QStringList m_tableHeader;
    QString Nom;
    QString Prenom;
};

#endif // THEGESTIONCONVENTION_H
