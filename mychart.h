#ifndef MYCHART_H
#define MYCHART_H

#include <QWidget>
#include <QtCharts>

using namespace QtCharts;

namespace Ui {
class myChart;
}

class myChart : public QWidget
{
    Q_OBJECT

public:
    explicit myChart(QWidget *parent = nullptr);
    ~myChart();

    void setTitle(QString str);
    void addData(double t, double data);
    void setXText(QString str);
    void setYText(QString str);
    void initialYRange(double num);

    void setXNumbers(double num);
    void setYNumbers(double num);
    void setMaxDataPoint(int num);

private slots:
    void setYRange();
    void setXRange();
    void setShownDataPoint();

private:
    Ui::myChart *ui;

    QChart *chart;
    QChartView *view;
    QVBoxLayout *layout;
    QValueAxis *x;
    QValueAxis *y;
    QLineSeries *mySeries;

    int xNumbers;
    int yNumbers;
    int maxDataPoints;

    double yNumMax;
    double yNumMin;

    QAction *changeYRange;
    QAction *changeXRange;
    QAction *changeShownData;

    void creatAction();
    void creatContextMenu();
};

#endif // MYCHART_H
