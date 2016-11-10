#ifndef BASICSETTINGS_H
#define BASICSETTINGS_H

#include <QDialog>
#include "basicsettingsdata.h"

namespace Ui {
class BasicSettings;
}

class BasicSettings : public QDialog
{
    Q_OBJECT

public:
    explicit BasicSettings(QWidget *parent = 0);
    ~BasicSettings();
    void readSettings(BasicSettingsData *settings);
    void changeSettings(BasicSettingsData *settings);

private:
    Ui::BasicSettings *ui;
};

#endif // BASICSETTINGS_H
