#include "planetedit.h"
#include "ui_planetedit.h"

PlanetEdit::PlanetEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlanetEdit)
{
    ui->setupUi(this);
    setFixedWidth(261);
    setFixedHeight(518);
    myColor = Qt::yellow;
    setColorButtonColor(myColor);
}

PlanetEdit::~PlanetEdit()
{
    delete ui;
}

void PlanetEdit::setPlanet(Planet *temp)
{
    myPlanet = temp;
}

void PlanetEdit::setValue()
{
    myPlanet->setName(ui->name->text());
    myPlanet->setRadius(ui->radious->value());
    myPlanet->setMass(ui->mass->value());
    myPlanet->setColor(myColor);
    myPlanet->setFixedPosition(ui->setFixedPosition->isChecked());
    myPlanet->setShowPath(ui->showPath->isChecked());
    myPlanet->setShowVelocityCurve(ui->showVelocityCurve->isChecked());
    myPlanet->setPos(ui->Px->value(),-ui->Py->value());
    myPlanet->setVx(ui->Vx->value());
    myPlanet->setVy(ui->Vy->value());
    myPlanet->setXNumbers(ui->XNumbers->value());
    myPlanet->setShownDataPoints(ui->shownDataPoints->value());
}

void PlanetEdit::readValue()
{
    ui->name->setText(myPlanet->getName());
    ui->radious->setValue(myPlanet->getRadius());
    ui->mass->setValue(myPlanet->getMass());
    myColor = myPlanet->getColor();

    setColorButtonColor(myColor);

    ui->setFixedPosition->setChecked(myPlanet->getFixedPosition());
    ui->showPath->setChecked(myPlanet->getShowPath());
    ui->showVelocityCurve->setChecked(myPlanet->getShowVelocityCurve());
    ui->Px->setValue(myPlanet->pos().x());
    ui->Py->setValue(-myPlanet->pos().y());
    ui->Vx->setValue(myPlanet->getVx());
    ui->Vy->setValue(myPlanet->getVy());
    ui->XNumbers->setValue(myPlanet->getXNumbers());
    ui->shownDataPoints->setValue(myPlanet->getShownDataPoints());
}

void PlanetEdit::on_color_clicked()
{
    QColorDialog *colorDialog = new QColorDialog(this);
    if(colorDialog->exec()){
        if(colorDialog->selectedColor().isValid()){
            myColor = colorDialog->selectedColor();
            setColorButtonColor(myColor);
        }
    }
}

void PlanetEdit::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button->text()=="Apply"){
        setValue();
    }
    else if(button->text()=="OK"){
        setValue();
        close();
    }
    else close();
}

void PlanetEdit::setColorButtonColor(QColor &color)
{

    QString red = QString::number(color.red());
    QString green = QString::number(color.green());
    QString blue = QString::number(color.blue());
    ui->color->setStyleSheet("background-color: rgb("+red+","+green+","+blue+")");
}

void PlanetEdit::on_setFixedPosition_clicked(bool checked)
{
    ui->showPath->setEnabled(!checked);
    ui->showVelocityCurve->setEnabled(!checked);
    if(checked){
        ui->showPath->setChecked(false);
        ui->showVelocityCurve->setChecked(false);
    }
}
