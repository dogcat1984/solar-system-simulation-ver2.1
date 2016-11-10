#include "planet.h"
#include <QtMath>

Planet::Planet()
{
    radius = 15;
    mass = 700;
    color = Qt::green;
    Vx=0;
    Vy=0;
    setPos(0, 0);
    setFlags(ItemIsMovable|ItemIsSelectable);
}

QRectF Planet::boundingRect() const
{
    return QRectF(-radius, -radius, 2*radius, 2*radius);
}

void Planet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    QPen pen(Qt::blue);
    QBrush colorBrush(color);
    QBrush redBrush(Qt::red);
    painter->setPen(pen);  

    QList<QGraphicsItem *>collision = scene()->collidingItems(this);
    if(!collision.isEmpty()){
        for(int i=0; i<collision.count(); ++i){
            QGraphicsItem *temp = collision.at(i);
            Planet *collisionIt = dynamic_cast<Planet *>(temp);
            doCollision(collisionIt);
        }
        painter->setBrush(redBrush);
    }
    else {
        painter->setBrush(colorBrush);
    }  

    if(isSelected()){
        QBrush selectedBrush(Qt::blue);
        painter->setBrush(selectedBrush);
    }

    painter->drawEllipse(boundingRect());
    painter->restore();
}

void Planet::advance(int phase)
{
    if (phase == 0){

    }
    else {
        update();
    }
}

QPainterPath Planet::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Planet::doCollision(Planet *collision)
{
    double V1x = getVx();
    double V1y = getVy();
    double m1= getMass();
    double V2x = collision->getVx();
    double V2y = collision->getVy();
    double m2 = collision->getMass();
    double finalV1x = ((m1-m2)*V1x+2*m2*V2x)/(m1+m2);
    double finalV1y = ((m1-m2)*V1y+2*m2*V2y)/(m1+m2);
    double finalV2x = ((m2-m1)*V2x+2*m1*V1x)/(m1+m2);
    double finalV2y = ((m2-m1)*V2y+2*m1*V1y)/(m1+m2);
    setVx(finalV1x);
    setVy(finalV1y);
    collision->setVx(finalV2x);
    collision->setVy(finalV2y);
}

void Planet::setName(QString word)
{
    name = word;
}

void Planet::setRadius(double num)
{
    radius = num;
}

void Planet::setMass(double num)
{
    mass = num;
}

void Planet::setColor(QColor color)
{
    this->color = color;
}

void Planet::setFixedPosition(bool fixed)
{
    fixedPosition = fixed;
}

void Planet::setShowPath(bool show)
{
    showPath = show;
}

void Planet::setShowVelocityCurve(bool show)
{
    showVelocityCurve = show;
}

void Planet::setVx(double num)
{
    Vx = num;
}

void Planet::setVy(double num)
{
    Vy = num;
}

void Planet::setXNumbers(double num)
{
    xNumbers = num;
}

void Planet::setShownDataPoints(int num)
{
    shownDataPoints = num;
}

QString Planet::getName()
{
    return name;
}

double Planet::getRadius()
{
    return radius;
}

double Planet::getMass()
{
    return mass;
}

QColor Planet::getColor()
{
    return color;
}

bool Planet::getFixedPosition()
{
    return fixedPosition;
}

bool Planet::getShowPath()
{
    return showPath;
}

bool Planet::getShowVelocityCurve()
{
    return showVelocityCurve;
}

double Planet::getVx()
{
    return Vx;
}

double Planet::getVy()
{
    return Vy;
}

double Planet::getXNumbers()
{
    return xNumbers;
}

int Planet::getShownDataPoints()
{
    return shownDataPoints;
}
