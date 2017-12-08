#include "mychart.h"
#include "ui_mychart.h"



myChart::myChart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myChart)
{
    ui->setupUi(this);

    yNumMax=0;
    yNumMin=10000000000000000;

    chart = new QChart();
    chart->legend()->hide();
    chart->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    view = new QChartView(this);

//    view->setRenderHint(QPainter::Antialiasing);

    layout = new QVBoxLayout(this);
    mySeries= new QLineSeries();
    mySeries->setUseOpenGL(true);

    chart->addSeries(mySeries);
    x = new QValueAxis;
    y = new QValueAxis;
    x->setRange(0,xNumbers);
    y->applyNiceNumbers();
    chart->setAxisX(x, mySeries);
    chart->setAxisY(y, mySeries);
    view->setChart(chart);
    layout->addWidget(view);
//    view->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    setLayout(layout);

    creatAction();
    creatContextMenu();

    setFixedHeight(300);
}

myChart::~myChart()
{
    delete ui;
    delete chart;
}

void myChart::setTitle(QString str)
{
    chart->setTitle(str);
}

void myChart::addData(double t, double data)
{
    mySeries->append(t, data);
    if(y->max()<data) yNumMax=data;
    else yNumMax=y->max();
    if(y->min()>data) yNumMin=data;
    else yNumMin=y->min();
    y->setRange(yNumMin,yNumMax);
    double scrollNum = chart->plotArea().width()/(x->max()-x->min());
    if(t>x->max()){
        chart->scroll((t-x->max())*scrollNum, 0);
    }
    if(mySeries->count()>maxDataPoints)
        mySeries->remove(0);
}

void myChart::setXText(QString str)
{
    chart->axisX()->setTitleText(str);
}

void myChart::setYText(QString str)
{
    chart->axisY()->setTitleText(str);
}

void myChart::setXNumbers(double num)
{
    x->setRange(0, num);
}

void myChart::setYNumbers(double num)
{
    y->setRange(0.999999*num, 1.000001*num);
}

void myChart::setMaxDataPoint(double num)
{
    maxDataPoints = num;
}

void myChart::setYRange()
{
    double min = QInputDialog::getDouble(this, "Please input Y minimum value", "Y axis min", y->min(), -2147483647,2147483647,6);
    double max = QInputDialog::getDouble(this, "Please input Y maximum value", "Y axis max", y->max(),-2147483647,2147483647,6);

    y->setRange(min,max);
}

void myChart::setXRange()
{
    double temp = QInputDialog::getInt(this, "Please input X range", "X range", x->max()-x->min());
    double xFirst = mySeries->at(0).x();
    double xLast = mySeries->at(mySeries->count()-1).x();
    if(xFirst + temp > xLast)
        x->setRange(xFirst, xFirst + temp);
    else{
        if(xLast-temp>0)
            x->setRange( xLast-temp, xLast);
        else x->setRange(0, temp);
    }
}

void myChart::setShownDataPoint()
{
    int temp = QInputDialog::getInt(this, "Please input shown data number", "Shown data number", maxDataPoints);
    if(temp){
        int num = mySeries->count();
        if(temp<num)
            mySeries->removePoints(0, num-temp);
        maxDataPoints = temp;
    }
}

void myChart::creatAction()
{
    changeYRange = new QAction("Change Y Axis Range", this);
    changeYRange->setToolTip("Change Y Axis Range");
    connect(changeYRange, SIGNAL(triggered(bool)), this, SLOT(setYRange()));

    changeXRange = new QAction("Change X Axis Range", this);
    changeYRange->setToolTip("Change X Axis Range");
    connect(changeXRange, SIGNAL(triggered(bool)), this, SLOT(setXRange()));

    changeShownData = new QAction("Change Shown Data Number", this);
    changeYRange->setToolTip("Change Shown Data Number");
    connect(changeShownData, SIGNAL(triggered(bool)), this, SLOT(setShownDataPoint()));
}

void myChart::creatContextMenu()
{
    addAction(changeXRange);
    addAction(changeYRange);    
    addAction(changeShownData);
    setContextMenuPolicy(Qt::ActionsContextMenu);
}
