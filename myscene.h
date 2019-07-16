#ifndef MYSCENE_H
#define MYSCENE_H

#include <QObject>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

#include "planet.h"
#include "planetedit.h"
#include "basicsettingsdata.h"

class MyScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit MyScene(QObject *parent = nullptr);
    void calculate(BasicSettingsData *settings);
    QVector<double> transferData();
    void setRunningTimeToZero();

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);

public slots:
    void toEditItem();
    void rebberbandSeletion(QRect rubberSeletion, QPointF startPosition, QPointF endPosition);
    void toAddItem();
    void toAddItem(Planet *add);
    void toDeleteItem();

signals:
    void toTransferData(QVector<double> );

private:
    QGraphicsItem *tempSelectedItem;

    double runningTime;

    void resetToZero(QVector<QVector<double>> &fun, int row, int column);
    void hkValue(QVector<QVector<double>> &k_value, QVector<QVector<double>> &fun, double h, int row, int column);
    void vartAddFunction(QVector<QVector<double>> &vart, QVector<QVector<double>> &arguments, QVector<QVector<double>> &k_value, double num, int row, int column);
    void calculateDistance(QVector<QVector<double>> &distance,QVector<QVector<double>> &vart, int row);
    void comp_f(QVector<QVector<double>> &function, QVector<QVector<double>> &vart,QVector<QVector<double>> &arguments,QVector<QVector<double>> &distance, double gConstant, int row);
};

#endif // MYSCENE_H
