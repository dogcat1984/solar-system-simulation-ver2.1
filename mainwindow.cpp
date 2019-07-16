#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icon/mainIcon"));

    timer = new QTimer(this);
    chartUpdateTime = new QTimer(this);
    filename = "temp";    

    view = new MyView(this);
    view->setRenderHints(QPainter::Antialiasing);
    scene = new MyScene(this);
    scene->setSceneRect(-mySettings->sceneWidth/2, -mySettings->sceneHeight/2, mySettings->sceneWidth, mySettings->sceneHeight);
    view->setScene(scene);
    view->centerOn(0,0);

    creatToolBar();
    creatStatusBar();
    creatContextMenu();
    myRightPanel = new chartPanel(this);

    sA = new QScrollArea(this);
    sA->setWidget(myRightPanel);

    mySplitter = new QSplitter(this);
    mySplitter->setOrientation(Qt::Horizontal);    
    mySplitter->addWidget(view);
    mySplitter->addWidget(sA);
    mySplitter->setStretchFactor(0,1);

    setCentralWidget(mySplitter);

    connect(view, SIGNAL(rubberBandChanged(QRect,QPointF,QPointF)), scene, SLOT(rebberbandSeletion(QRect,QPointF,QPointF)));

    mySettings = new BasicSettingsData;

    connect(timer, SIGNAL(timeout()), this, SLOT(calculateForce()));
    connect(chartUpdateTime, SIGNAL(timeout()), this, SLOT(updateChart()));
    connect(this, SIGNAL(calculated()), scene, SLOT(advance()));
}

void MainWindow::creatToolBar()
{
       newFile = new QAction("New", this);
       actionList<<newFile;
       actionList.at(0)->setIcon(QIcon(":/icon/newIcon"));
       actionList.at(0)->setToolTip("Creat a new file");
       connect(actionList.at(0), SIGNAL(triggered(bool)), this, SLOT(creatNewFile()));

       openFile = new QAction("Open", this);
       actionList<<openFile;
       actionList.at(1)->setIcon(QIcon(":/icon/openIcon"));
       actionList.at(1)->setToolTip("Open a file");
       connect(actionList.at(1), SIGNAL(triggered(bool)), this, SLOT(readFromFile()));

       saveFile = new QAction("Save", this);
       actionList<<saveFile;
       actionList.at(2)->setIcon(QIcon(":/icon/saveIcon"));
       actionList.at(2)->setToolTip("Save current file");
       connect(actionList.at(2), SIGNAL(triggered(bool)), this, SLOT(saveToFile()));

       saveFileAs = new QAction("Save as", this);
       saveFileAs->setIcon(QIcon(":/icon/saveAsIcon"));
       saveFileAs->setToolTip("Save file as");
       connect(saveFileAs, SIGNAL(triggered(bool)), this, SLOT(saveAs()));

       addPlanet = new QAction("Add a planet", this);
       addPlanet->setIcon(QIcon(":/icon/addPlanetIcon"));
       addPlanet->setToolTip("Add a new planet");
       connect(addPlanet, SIGNAL(triggered(bool)), scene, SLOT(toAddItem()));

       deletePlanet = new QAction("Delete planets", this);
       deletePlanet->setIcon(QIcon(":/icon/deletePlanetIcon"));
       deletePlanet->setToolTip("Delete the selected planets");
       connect(deletePlanet, SIGNAL(triggered(bool)), scene, SLOT(toDeleteItem()));

       editPlanet = new QAction("Edit a planet", this);
       editPlanet->setIcon(QIcon(":/icon/editIcon"));
       editPlanet->setToolTip("Edit a planet");
       connect(editPlanet, SIGNAL(triggered(bool)), scene, SLOT(toEditItem()));

       center = new QAction("Center the view", this);
       center->setIcon(QIcon(":/icon/centerIcon"));
       center->setToolTip("Center the view");
       connect(center, SIGNAL(triggered(bool)), this, SLOT(centerTheView()));

       changeSceneColor = new QAction("Scene background", this);
       changeSceneColor->setIcon(QIcon(":/icon/sceneColorIcon"));
       changeSceneColor->setToolTip("Change ths scene background color");
       connect(changeSceneColor, SIGNAL(triggered(bool)), this, SLOT(changeMySceneColor()));

       start = new QAction("Start simulations", this);
       start->setIcon(QIcon(":/icon/startIcon"));
       start->setToolTip("Start the simulation");
       connect(start, SIGNAL(triggered(bool)), this, SLOT(startFuntion()));

       pause = new QAction("Pause simulations", this);
       pause->setIcon(QIcon(":/icon/pauseIcon"));
       pause->setEnabled(false);
       pause->setToolTip("Pause the simulation");
       connect(pause, SIGNAL(triggered(bool)), this, SLOT(stopFuntion()));

       simulationConstant = new QAction("Change simulation constant", this);
       simulationConstant->setIcon(QIcon(":/icon/settingIcon"));
       simulationConstant->setToolTip("Change simulation constant");
       connect(simulationConstant, SIGNAL(triggered(bool)), this, SLOT(modifyBasicSettings()));

       myDrag = new QAction("Move the view", this);
       myDrag->setIcon(QIcon(":/icon/dragIcon"));
       myDrag->setToolTip("Move the view");
       myDrag->setCheckable(true);
       connect(myDrag, SIGNAL(triggered(bool)), view, SLOT(setMyDragMode(bool)));

       mySelect = new QAction("Select by a rectangle", this);
       mySelect->setIcon(QIcon(":/icon/selectIcon"));
       mySelect->setToolTip("Select by a rectangle");
       mySelect->setCheckable(true);
       connect(mySelect, SIGNAL(triggered(bool)), view, SLOT(setMySelectMode(bool)));

       connect(myDrag, SIGNAL(triggered(bool)), this, SLOT(setMySelect(bool)));
       connect(mySelect, SIGNAL(triggered(bool)), this, SLOT(setMyDrat(bool)));

       zoomIn = new QAction("Zoom in", this);
       zoomIn->setIcon(QIcon(":/icon/zoomInIcon"));
       zoomIn->setToolTip("Zoom In");
       connect(zoomIn, SIGNAL(triggered(bool)), this, SLOT(zoomInFuntion()));

       zoomOut = new QAction("Zoom out", this);
       zoomOut->setIcon(QIcon(":/icon/zoomOutIcon"));
       zoomOut->setToolTip("Zoom out");
       connect(zoomOut, SIGNAL(triggered(bool)), this, SLOT(zoomOutFuntion()));

       about = new QAction("About this software", this);
       about->setToolTip("About this software");
       connect(about, SIGNAL(triggered(bool)), this, SLOT(showAbout()));

       ui->mainToolBar->addAction(actionList.at(0));
       ui->mainToolBar->addAction(actionList.at(1));
       ui->mainToolBar->addAction(actionList.at(2));
       ui->mainToolBar->addAction(saveFileAs);

       ui->mainToolBar->addSeparator();
       ui->mainToolBar->addAction(editPlanet);
       ui->mainToolBar->addAction(addPlanet);
       ui->mainToolBar->addAction(deletePlanet);

       ui->mainToolBar->addSeparator();
       ui->mainToolBar->addAction(start);
       ui->mainToolBar->addAction(pause);
       ui->mainToolBar->addAction(simulationConstant);
       ui->mainToolBar->addSeparator();

       ui->mainToolBar->addAction(myDrag);
       ui->mainToolBar->addAction(mySelect);

       ui->mainToolBar->addSeparator();
       ui->mainToolBar->addAction(zoomIn);
       ui->mainToolBar->addAction(zoomOut);
       ui->mainToolBar->addAction(center);
       ui->mainToolBar->addAction(changeSceneColor);

       ui->menuFile->addAction(actionList.at(0));
       ui->menuFile->addAction(actionList.at(1));
       ui->menuFile->addAction(actionList.at(2));
       ui->menuFile->addAction(saveFileAs);

       ui->menuEdit->addAction(editPlanet);
       ui->menuEdit->addAction(addPlanet);
       ui->menuEdit->addAction(deletePlanet);

       ui->menuSimulation->addAction(start);
       ui->menuSimulation->addAction(pause);
       ui->menuSimulation->addAction(simulationConstant);

       ui->menuOperation->addAction(myDrag);
       ui->menuOperation->addAction(mySelect);
       ui->menuOperation->addAction(zoomIn);
       ui->menuOperation->addAction(zoomOut);
       ui->menuOperation->addAction(center);
       ui->menuOperation->addAction(changeSceneColor);

       ui->menuAbout->addAction(about);
}

void MainWindow::creatStatusBar()
{
    statusLabel = new QLabel(this);
    statusLabel->setText("Software started");
    ui->statusBar->addWidget(statusLabel);
}

void MainWindow::creatContextMenu()
{
    view->addAction(editPlanet);
    view->addAction(deletePlanet);
    view->addAction(addPlanet);
    view->addAction(myDrag);
    view->addAction(mySelect);
    view->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::creatChartPanel()
{
    myRightPanel->removeLayout();
    if(scene->items().count()!=0){
        for(int i=0; i<scene->items().count(); ++i){
            Planet *temp = dynamic_cast<Planet *>(scene->items().at(i));
            if(temp->getShowVelocityCurve()) myRightPanel->addChart(temp);
        }
    }
}

void MainWindow::setMyDrat(bool ok)
{
    if(myDrag->isChecked())
        myDrag->setChecked(!ok);
}

void MainWindow::setMySelect(bool ok)
{
    if(mySelect->isChecked())
        mySelect->setChecked(!ok);
}

void MainWindow::showAbout()
{
    QMessageBox::about(this, "Gravitation simulation system ver1.0", "Copy rights reserved by laws.\n\nAny question, please contact dogcat1984@qq.com");
}

void MainWindow::changeMySceneColor()
{
    QColor myColor = QColorDialog::getColor(Qt::gray, this, "Please select a color");

    if (myColor.isValid()){
        QBrush brush(myColor);
        scene->setBackgroundBrush(brush);
    }
}

void MainWindow::centerTheView()
{
    QRectF rect = scene->itemsBoundingRect();
    QPointF point;
    point.setX(rect.center().x());
    point.setY(rect.center().y());
    view->centerOn(point);
    view->fitInView(rect, Qt::KeepAspectRatio);
}

void MainWindow::updateChart()
{
    timer->stop();
    myRightPanel->addData(scene->transferData());
    timer->start();
}

void MainWindow::calculateForce()
{
    for (int t=0; t<mySettings->simulationStep; ++t){
        scene->calculate(mySettings);
    }
    emit calculated();
}

void MainWindow::startFuntion()
{    
    start->setEnabled(false);
    pause->setEnabled(true);
    simulationConstant->setEnabled(false);
    statusLabel->setText("Running simulation.");
    scene->setRunningTimeToZero();
    creatChartPanel();
    timer->start(mySettings->timer);
    chartUpdateTime->start(mySettings->chartUpdateTime);
}

void MainWindow::stopFuntion()
{
    chartUpdateTime->stop();
    timer->stop();
    start->setEnabled(true);
    pause->setEnabled(false);
    simulationConstant->setEnabled(true);
    statusLabel->setText("Simulation has been stopped.");    
}

void MainWindow::zoomInFuntion()
{
    view->scale(1.2, 1.2);
}

void MainWindow::zoomOutFuntion()
{
    view->scale(1/1.2, 1/1.2);
}

void MainWindow::modifyBasicSettings()
{
    basic = new BasicSettings(this);
    basic->readSettings(mySettings);
    if(basic->exec()){
        basic->changeSettings(mySettings);
        scene->setSceneRect(-mySettings->sceneWidth/2, -mySettings->sceneHeight/2, mySettings->sceneWidth, mySettings->sceneHeight);
        scene->update();
        QMessageBox::warning(this, "Note", "Setting has been saved!", QMessageBox::Yes);
    }
}

void MainWindow::creatNewFile()
{
    scene->clear();
    filename = "temp";
}

void MainWindow::saveToFile()
{
    if(filename == "temp")
        filename = QFileDialog::getSaveFileName(this,"Save File", "/", "file(*.csv)");
    QFile savedFile(filename);
    if(savedFile.open(QIODevice::WriteOnly)){
        QTextStream data(&savedFile);

        data<<"Gravitiaon Constant, Simulation Step, Time Per Steop, Timer, Chart Update Time, Scene Width, Scene Height\n";
        data<<QString::number(mySettings->gravitationConstant)<<","<<QString::number(mySettings->simulationStep)<<","
            <<QString::number(mySettings->timePerStep)<<","<<QString::number(mySettings->timer)<<","<<QString::number(mySettings->chartUpdateTime)<<","
            <<QString::number(mySettings->sceneWidth)<<","<<QString::number(mySettings->sceneHeight)<<"\n"<<"\n";

        data<<"Name,Radius,Mass,Red,Green,Blue,FixedPosition,Path,VelocityCurve,PositionX,PositionY,VelocityX,VelocityY,XAxisRange,ShownDataPoints\n";

        for(int i=0; i<scene->items().count(); ++i){
            Planet *temp = dynamic_cast<Planet *>(scene->items().at(i));

            QString pName = temp->getName();
            QString pRadius = QString::number(temp->getRadius());
            QString pMass = QString::number(temp->getMass());            

            QColor myColor = temp->getColor();
            QString red = QString::number(myColor.red());
            QString green = QString::number(myColor.green());
            QString blue = QString::number(myColor.blue());

            QString pFixedPosiiton =QString::number(temp->getFixedPosition());
            QString pShowPath = QString::number(temp->getShowPath());
            QString pShowVelocityCurve = QString::number(temp->getShowVelocityCurve());

            QString pPx = QString::number(temp->pos().x());
            QString pPy = QString::number(-temp->pos().y());
            QString pVx = QString::number(temp->getVx());
            QString pVy = QString::number(temp->getVy());

            QString PXN = QString::number(temp->getXNumbers());
            QString PSDP = QString::number(temp->getShownDataPoints());

            data<<pName<<","<<pRadius<<","<<pMass<<","<<red<<","<<green<<","<<blue<<","
               <<pFixedPosiiton<<","<<pShowPath<<","<<pShowVelocityCurve<<","
               <<pPx<<","<<pPy<<","<<pVx<<","<<pVy<<","<<PXN<<","<<PSDP<<"\n";
        }
        QMessageBox::information(this, "Save file", "Save file succesfully!");
    }
}

void MainWindow::saveAs()
{
    filename = QFileDialog::getSaveFileName(this,"Save File As", "/", "file(*.csv)");
    QFile savedFile(filename);
    if(savedFile.open(QIODevice::WriteOnly)){
        QTextStream data(&savedFile);

        data<<"Gravitiaon Constant, Simulation Step, Time Per Steop, Timer, ChartUpdatTime, Scene Width, Scene Height\n";
        data<<QString::number(mySettings->gravitationConstant)<<","<<QString::number(mySettings->simulationStep)<<","
            <<QString::number(mySettings->timePerStep)<<","<<QString::number(mySettings->timer)<<","<<QString::number(mySettings->chartUpdateTime)<<","
            <<QString::number(mySettings->sceneWidth)<<","<<QString::number(mySettings->sceneHeight)<<"\n"<<"\n";

         data<<"Name,Radius,Mass,Red,Green,Blue,FixedPosition,Path,VelocityCurve,PositionX,PositionY,VelocityX,VelocityY,XAxisRange,ShownDataPoints\n";

        for(int i=0; i<scene->items().count(); ++i){
            Planet *temp = dynamic_cast<Planet *>(scene->items().at(i));

            QString pName = temp->getName();
            QString pRadius = QString::number(temp->getRadius());
            QString pMass = QString::number(temp->getMass());

            QColor myColor = temp->getColor();
            QString red = QString::number(myColor.red());
            QString green = QString::number(myColor.green());
            QString blue = QString::number(myColor.blue());

            QString pFixedPosiiton =QString::number(temp->getFixedPosition());
            QString pShowPath = QString::number(temp->getShowPath());
            QString pShowVelocityCurve = QString::number(temp->getShowVelocityCurve());

            QString pPx = QString::number(temp->pos().x());
            QString pPy = QString::number(-temp->pos().y());
            QString pVx = QString::number(temp->getVx());
            QString pVy = QString::number(temp->getVy());

            QString PXN = QString::number(temp->getXNumbers());
            QString PSDP = QString::number(temp->getShownDataPoints());

            data<<pName<<","<<pRadius<<","<<pMass<<","<<red<<","<<green<<","<<blue<<","
               <<pFixedPosiiton<<","<<pShowPath<<","<<pShowVelocityCurve<<","
               <<pPx<<","<<pPy<<","<<pVx<<","<<pVy<<","<<PXN<<","<<PSDP<<"\n";
        }
        QMessageBox::information(this, "Save file", "Save file succesfully!");
    }
}

void MainWindow::readFromFile()
{
   if(filename != "temp")
        filename = QFileDialog::getOpenFileName(this, "Load a file", filename,"file(*.csv)");
    else
        filename = QFileDialog::getOpenFileName(this, "Load a file", "/Solar Sim/samples/", "file(*.csv)");
    QFile readedFile(filename);
    QStringList results;
    if(readedFile.open(QIODevice::ReadOnly)){
        scene->clear();
        QTextStream data(&readedFile);
        while(!data.atEnd()) results<<data.readLine();
        results.removeFirst();
        QString basic = results.at(0);
        QStringList basicSettings = basic.split(",");
        QString constant = basicSettings.at(0);
        QString tempStep = basicSettings.at(1);
        QString tempTimePerStep = basicSettings.at(2);
        QString tempTimer = basicSettings.at(3);
        QString tempChartUpdateTime = basicSettings.at(4);
        QString tempSceneWidth = basicSettings.at(5);
        QString tempSceneHeight = basicSettings.at(6);

        mySettings->gravitationConstant = constant.toDouble();
        mySettings->simulationStep = tempStep.toInt();
        mySettings->timePerStep = tempTimePerStep.toDouble();
        mySettings->timer = tempTimer.toInt();
        mySettings->chartUpdateTime = tempChartUpdateTime.toInt();
        mySettings->sceneWidth = tempSceneWidth.toDouble();
        mySettings->sceneHeight = tempSceneHeight.toDouble();
        scene->setSceneRect(-mySettings->sceneWidth/2, -mySettings->sceneHeight/2, mySettings->sceneWidth, mySettings->sceneHeight);

        results.removeFirst();
        results.removeFirst();
        results.removeFirst();

        for(int i=0; i<results.count(); ++i){
            QString temp = results.at(i);
            QStringList finalResults = temp.split(",");

            QString pName = finalResults.at(0);

            QString tempRadius = finalResults.at(1);
            QString tempMass = finalResults.at(2);
            QString red = finalResults.at(3);
            QString green = finalResults.at(4);
            QString blue = finalResults.at(5);
            QString tempFixedPosition = finalResults.at(6);
            QString tempShowPath = finalResults.at(7);
            QString tempShowVelocityCurve = finalResults.at(8);
            QString temppx = finalResults.at(9);
            QString temppy = finalResults.at(10);
            QString tempvx = finalResults.at(11);
            QString tempvy = finalResults.at(12);
            QString tempXN = finalResults.at(13);
            QString tempSDP = finalResults.at(14);

            int pRadius = tempRadius.toInt();
            int pMass = tempMass.toInt();
            int pRed = red.toInt();
            int pGreen = green.toInt();
            int pBlue = blue.toInt();
            int pFixedPosition = tempFixedPosition.toInt();
            int pShowPath = tempShowPath.toInt();
            int pShowVelocityCurve = tempShowVelocityCurve.toInt();

            QColor myColor;
            myColor.setRed(pRed); myColor.setGreen(pGreen); myColor.setBlue(pBlue);

            double ppx = temppx.toDouble();
            double ppy = temppy.toDouble();
            double pvx = tempvx.toDouble();
            double pvy = tempvy.toDouble();
            int pXN = tempXN.toInt();
            int pSDP = tempSDP.toInt();

            Planet *tempPlanet = new Planet;
            tempPlanet->setName(pName);
            tempPlanet->setRadius(pRadius);
            tempPlanet->setMass(pMass);
            tempPlanet->setColor(myColor);
            tempPlanet->setFixedPosition(bool(pFixedPosition));
            tempPlanet->setShowPath(bool(pShowPath));
            tempPlanet->setShowVelocityCurve(bool(pShowVelocityCurve));
            tempPlanet->setPos(ppx,-ppy);
            tempPlanet->setVx(pvx);
            tempPlanet->setVy(pvy);
            tempPlanet->setXNumbers(pXN);
            tempPlanet->setShownDataPoints(pSDP);
            scene->toAddItem(tempPlanet);
            delete tempPlanet;
        }
        centerTheView();
    }    
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mySettings;
}
