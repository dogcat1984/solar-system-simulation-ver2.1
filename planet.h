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
    void setRadius(double num);
    void setMass(double num);
    void setColor(QColor color);
    void setFixedPosition(bool fixed);
    void setShowPath(bool show);
    void setShowVelocityCurve(bool show);
    void setVx(double num);
    void setVy(double num);
    void setXNumbers(double num);
    void setShownDataPoints(int num);

    QString getName();
    double getRadius();
    double getMass();
    QColor getColor();
    bool getFixedPosition();
    bool getShowPath();
    bool getShowVelocityCurve();
    double getVx();
    double getVy();
    double getXNumbers();
    int getShownDataPoints();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);
    QPainterPath shape() const;
    void doCollision(Planet *collision);

private:
    QString name;
    double radius;
    double mass;
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
