#include "myscene.h"

MyScene::MyScene(QObject *parent):QGraphicsScene(parent)
{
    QBrush brush(Qt::gray);
    setBackgroundBrush(brush);
    runningTime = 0;
}

void MyScene::calculate(BasicSettingsData *settings)
{
    double gConstant = settings->gravitationConstant;
    double h = settings->timePerStep;
    runningTime+=h;
    int counts = items().count();//number of items

    //m , x, Vx, y, Vy
    //0, m
    //1, x
    //2, Vx
    //3, y
    //4, Vy
    QVector<QVector <double>> arguments(counts+1, QVector<double>(5));
    //vart(x, Vx, y, Vy), temp data
    QVector<QVector <double>> vart(counts+1, QVector<double>(5));
    //Function
    QVector<QVector <double>> function(counts+1, QVector<double>(5));
    //planet's distance
    QVector<QVector <double>> distance(counts+1, QVector<double>(counts+1));

    //k1, k2, k3, k4
    QVector<QVector <double>> k1(counts+1, QVector<double>(5));
    QVector<QVector <double>> k2(counts+1, QVector<double>(5));
    QVector<QVector <double>> k3(counts+1, QVector<double>(5));
    QVector<QVector <double>> k4(counts+1, QVector<double>(5));

    //fill arguments
    for(int i=1; i<=counts; ++i){
        Planet *p = dynamic_cast<Planet *> (items().at(i-1));
        arguments[i][0]=p->getMass();
        arguments[i][1]=p->pos().x();
        arguments[i][2]=p->getVx();
        arguments[i][3]=-p->pos().y();
        arguments[i][4]=p->getVy();
    }

    //vart=arguments
    for(int i=1; i<=counts; ++i){
        for(int j=1; j<=4; ++j)
        vart[i][j] = arguments[i][j];
    }
    //calculate distance
    calculateDistance(distance, vart, counts);

    //reset function
    resetToZero(function, counts, 4);
    //f
    comp_f(function, vart, arguments, distance, gConstant, counts);

    //k1
    hkValue(k1, function, h, counts, 4);

    //vart = argument + 0.5 * k1
    vartAddFunction(vart, arguments, k1, 0.5, counts, 4);

    //calculate distance
    calculateDistance(distance, vart, counts);

    //reset function
    resetToZero(function, counts, 4);
    //f
    comp_f(function, vart, arguments, distance, gConstant, counts);

    //k2
    hkValue(k2, function, h, counts, 4);
    //vart = argument + 0.5 * k2
    vartAddFunction(vart, arguments, k2, 0.5, counts, 4);

    //calculate distance
    calculateDistance(distance, vart, counts);

    //reset function
    resetToZero(function, counts, 4);
    //f
    comp_f(function, vart, arguments, distance, gConstant, counts);

    //k3
    hkValue(k3, function, h, counts, 4);
    //vart = argument +  k3
    vartAddFunction(vart, arguments, k3, 1, counts, 4);


    //calculate distance
    calculateDistance(distance, vart, counts);

    //reset function
    resetToZero(function, counts, 4);
    //f
    comp_f(function, vart, arguments, distance, gConstant, counts);
    //k4
    hkValue(k4, function, h, counts, 4);

    //final arguments
    for(int i=1; i<=counts; ++i){
        for(int j=1; j<=4; ++j)
            arguments[i][j] = arguments[i][j]+(k1[i][j]+2*(k2[i][j]+k3[i][j])+k4[i][j])/6;
    }
    //set results
    for(int i=1; i<=counts; ++i){
        Planet *p = dynamic_cast<Planet *> (items().at(i-1));
        if(!p->getFixedPosition()){
            p->setPos(arguments[i][1],-arguments[i][3]);
            p->setVx(arguments[i][2]);
            p->setVy(arguments[i][4]);
        }
    }
}

QVector<double> MyScene::transferData()
{
    QVector<double>result;
    result<<runningTime;
    for(int i=0; i<items().count();++i){
        Planet *temp = dynamic_cast<Planet *>(items().at(i));
        if(temp->getShowVelocityCurve()){
            double V = sqrt(pow(temp->getVx(),2)+pow(temp->getVy(),2));
            result<<V;
        }
    }
    return result;
}

void MyScene::setRunningTimeToZero()
{
    runningTime = 0;
}

void MyScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseEvent->button() == Qt::LeftButton){
        if(!selectedItems().isEmpty()){
            tempSelectedItem = selectedItems().at(0);
            Planet *temp = dynamic_cast<Planet *>(tempSelectedItem);
            PlanetEdit editPlanet;
            editPlanet.setPlanet(temp);
            editPlanet.readValue();
            editPlanet.exec();
        }
    }
    else  QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

void MyScene::toEditItem()
{
    if(!selectedItems().isEmpty()){
        tempSelectedItem = selectedItems().at(0);
        Planet *temp = dynamic_cast<Planet *>(tempSelectedItem);
        PlanetEdit editPlanet;
        editPlanet.setPlanet(temp);
        editPlanet.readValue();
        editPlanet.exec();
    }
}

void MyScene::rebberbandSeletion(QRect rubberSeletion, QPointF startPosition, QPointF endPosition)
{
     if(!startPosition.isNull() && !endPosition.isNull()){
        QPoint SP;
        QPoint EP;
        SP.setX(startPosition.x());
        SP.setY(startPosition.y());
        EP.setX(endPosition.x());
        EP.setY(endPosition.y());

        QRect selectArea;
        selectArea.setTopLeft(SP);
        selectArea.setBottomRight(EP);

        QPainterPath path;
        path.addRect(selectArea);
        setSelectionArea(path);
     }
}

void MyScene::toAddItem()
{
    PlanetEdit editPlanet;
    Planet *temp = new Planet;
    editPlanet.setPlanet(temp);
    if(editPlanet.exec())
        addItem(temp);
}

void MyScene::toAddItem(Planet *add)
{
    Planet *temp = new Planet();

    temp->setName(add->getName());
    temp->setRadius(add->getRadius());
    temp->setMass(add->getMass());
    temp->setColor(add->getColor());
    temp->setFixedPosition(add->getFixedPosition());
    temp->setShowPath(add->getShowPath());
    temp->setShowVelocityCurve(add->getShowVelocityCurve());
    temp->setPos(add->pos());
    temp->setVx(add->getVx());
    temp->setVy(add->getVy());
    temp->setXNumbers(add->getXNumbers());
    temp->setShownDataPoints(add->getShownDataPoints());

    addItem(temp);
}

void MyScene::toDeleteItem()
{
    QList<QGraphicsItem *> temp = selectedItems();
    if(!temp.isEmpty()){
        for(int i=0; i<temp.count(); ++i)
            removeItem(temp.at(i));
    }
}

void MyScene::resetToZero(QVector<QVector<double> > &fun, int row, int column)
{
    for(int i=1; i<=row; ++i)
        for(int j=1; j<=column; ++j)
            fun[i][j]=0;
}

void MyScene::hkValue(QVector<QVector<double> > &k_value, QVector<QVector<double> > &fun, double h, int row, int column)
{
    for(int i=1; i<=row; ++i){
        for(int j=1; j<=column; ++j)
            k_value[i][j] = h*fun[i][j];
    }
}

void MyScene::vartAddFunction(QVector<QVector<double> > &vart, QVector<QVector<double> > &arguments, QVector<QVector<double> > &k_value, double num, int row, int column)
{
    for(int i=1; i<=row; ++i){
        for(int j=1; j<=column; ++j)
            vart[i][j]= arguments[i][j]+num*k_value[i][j];
    }
}

void MyScene::calculateDistance(QVector<QVector<double> > &distance, QVector<QVector<double> > &vart, int row)
{
    for(int i=1; i<=row; ++i){
        for(int j=1; j<=row; ++j){
            distance[i][j] = qSqrt( pow(vart[i][1]-vart[j][1],2) + pow(vart[i][3]-vart[j][3],2) );
        }
    }
}

void MyScene::comp_f(QVector<QVector<double> > &function, QVector<QVector<double> > &vart, QVector<QVector<double> > &arguments, QVector<QVector<double> > &distance, double gConstant, int row)
{
    for(int i=1; i<=row; ++i){
        function[i][1] = vart[i][2];//Vx
        function[i][3] = vart[i][4];//Vy
        for(int j=1; j<=row; ++j){
            if(i!=j){
                function[i][2] += -gConstant*arguments[j][0]/pow(distance[i][j],3)*(vart[i][1]-vart[j][1]);//x
                function[i][4] += -gConstant*arguments[j][0]/pow(distance[i][j],3)*(vart[i][3]-vart[j][3]);//y
            }
        }
    }
}





