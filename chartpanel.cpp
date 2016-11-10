#include "chartpanel.h"
#include "ui_chartpanel.h"

chartPanel::chartPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chartPanel)
{
    ui->setupUi(this);
    setLayout(&layout);
}

chartPanel::~chartPanel()
{
    delete ui;
}

void chartPanel::addChart(Planet *p)
{
    myChart *temp = new myChart(this);
    temp->setTitle(p->getName());
    temp->setXText("Time");
    temp->setYText("Velocity");
    temp->addData(0, sqrt(pow(p->getVx(),2)+pow(p->getVy(),2)));
    temp->setYNumbers(sqrt(pow(p->getVx(),2)+pow(p->getVy(),2)));
    temp->setXNumbers(p->getXNumbers());
    temp->setMaxDataPoint(p->getShownDataPoints());
    list<<temp;
    layOutChart(temp);
}

void chartPanel::layOutChart(myChart *p)
{
    layout.addWidget(p);
    setFixedHeight(p->geometry().height()*list.count());
}

void chartPanel::addData(QVector<double> data)
{
    if(!list.isEmpty()){
        for(int i=0; i<list.count(); ++i){
            list.at(i)->addData(data.at(0), data.at(i+1));
        }
    }
//    update();
}

void chartPanel::removeLayout()
{
    while(!list.isEmpty()){
        layout.removeWidget(list.first());
        list.first()->deleteLater();
        list.removeFirst();
    }
}
