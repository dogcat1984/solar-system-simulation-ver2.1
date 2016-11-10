#include "basicsettings.h"
#include "ui_basicsettings.h"

BasicSettings::BasicSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BasicSettings)
{
    ui->setupUi(this);
    setFixedWidth(320);
    setFixedHeight(283);
}

BasicSettings::~BasicSettings()
{
    delete ui;
}

void BasicSettings::readSettings(BasicSettingsData *settings)
{
    ui->gravitationConstant->setValue(settings->gravitationConstant);
    ui->simulationStep->setValue(settings->simulationStep);
    ui->timePerStep->setValue(settings->timePerStep);
    ui->timer->setValue(settings->timer);
    ui->chartUpdateTime->setValue(settings->chartUpdateTime);
    ui->sceneWidth->setValue(settings->sceneWidth);
    ui->sceneHeight->setValue(settings->sceneHeight);
}

void BasicSettings::changeSettings(BasicSettingsData *settings)
{
    settings->gravitationConstant = ui->gravitationConstant->value();
    settings->simulationStep = ui->simulationStep->value();
    settings->timePerStep = ui->timePerStep->value();
    settings->timer = ui->timer->value();
    settings->chartUpdateTime = ui->chartUpdateTime->value();
    settings->sceneWidth = ui->sceneWidth->value();
    settings->sceneHeight = ui->sceneHeight->value();
}
