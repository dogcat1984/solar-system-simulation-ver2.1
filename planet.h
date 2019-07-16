#ifndef PLANET_H
#define PLANET_H

#include <QtCore>
#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsScene>

class Planet : public QGraphicsItem
{
public:    
    Planet();    

    void setName(QString word);
    void setRadius(int num);
    void setMass(int num);
    void setColor(QColor color);
    void setFixedPosition(bool fixed);
    void setShowPath(bool show);
    void setShowVelocityCurve(bool show);
    void setVx(double num);
    void setVy(double num);
    void setXNumbers(int num);
    void setShownDataPoints(int num);

    QString getName();
    int getRadius();
    int getMass();
    QColor getColor();
    bool getFixedPosition();
    bool getShowPath();
    bool getShowVelocityCurve();
    double getVx();
    double getVy();
    int getXNumbers();
    int getShownDataPoints();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);
    QPainterPath shape() const;
    void doCollision(Planet *collision);

private:
    QString name;
    int radius;
    int mass;
    QColor color;
    double Vx;
    double Vy;
    bool fixedPosition;
    bool showPath;
    bool showVelocityCurve;
    int xNumbers;
    int shownDataPoints;
};

#endif // PLANET_H
