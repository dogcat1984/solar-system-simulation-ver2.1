#ifndef PLANETEDIT_H
#define PLANETEDIT_H

#include <QDialog>
#include <QColor>
#include <QColorDialog>
#include <QAbstractButton>

#include "planet.h"

namespace Ui {
class PlanetEdit;
}

class PlanetEdit : public QDialog
{
    Q_OBJECT

public:
    explicit PlanetEdit(QWidget *parent = nullptr);
    ~PlanetEdit();
    void setPlanet(Planet *temp);
    void setValue();
    void readValue();

private slots:
    void on_color_clicked();

    void on_buttonBox_clicked(QAbstractButton *button);

    void on_setFixedPosition_clicked(bool checked);

private:
    Ui::PlanetEdit *ui;
    QColor myColor;
    Planet *myPlanet;

    void setColorButtonColor(QColor &color);
};

#endif // PLANETEDIT_H
