#ifndef THEGENERAL_H
#define THEGENERAL_H

#include <QDialog>
#include <math.h>

namespace Ui {
class TheGeneral;
}

class TheGeneral : public QDialog
{
    Q_OBJECT

public:
    explicit TheGeneral(QWidget *parent = 0);
    ~TheGeneral();

    static unsigned int hashage(std::string motDePasse);

public slots:
    void addUser();

private:
    Ui::TheGeneral *ui;
};

#endif // THEGENERAL_H
