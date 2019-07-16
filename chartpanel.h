#ifndef CHARTPANEL_H
#define CHARTPANEL_H

#include <QWidget>

#include "planet.h"
#include "mychart.h"

namespace Ui {
class chartPanel;
}

class chartPanel : public QWidget
{
    Q_OBJECT

public:
    explicit chartPanel(QWidget *parent = nullptr);
    ~chartPanel();

    void addChart(Planet *p);
    void layOutChart(myChart *p);
    void addData(QVector<double> data);
    void removeLayout();

private:
    Ui::chartPanel *ui;
    QVBoxLayout *layout;
    QList <myChart *> list;
};

#endif // CHARTPANEL_H
