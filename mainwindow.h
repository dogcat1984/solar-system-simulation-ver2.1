#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QSplitter>
#include <QMessageBox>
#include <QFileDialog>
#include <QLabel>

#include "planet.h"
#include "myscene.h"
#include "myview.h"
#include "basicsettingsdata.h"
#include "basicsettings.h"
#include "chartpanel.h"
#include "mychart.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

     ~MainWindow();

public slots:
    void calculateForce();

    void startFuntion();
    void stopFuntion();
    void zoomInFuntion();
    void zoomOutFuntion();
    void modifyBasicSettings();
    void creatNewFile();
    void saveToFile();
    void saveAs();
    void readFromFile();

signals:
    void calculated();

private:
    Ui::MainWindow *ui;
    MyView *view;
    MyScene *scene;
    BasicSettings *basic;

    QTimer *timer;
    QTimer *chartUpdateTime;
    BasicSettingsData *mySettings;

    QString filename;

    QLabel *statusLabel;
    chartPanel *myRightPanel;
    QScrollArea *sA;
    QSplitter *mySplitter;

    QList<QAction*> actionList;

    QAction *newFile;
    QAction *saveFile;
    QAction *saveFileAs;
    QAction *openFile;
    QAction *addPlanet;
    QAction *deletePlanet;
    QAction *editPlanet;
    QAction *center;
    QAction *changeSceneColor;
    QAction *start;
    QAction *pause;
    QAction *simulationConstant;
    QAction *myDrag;
    QAction *mySelect;
    QAction *zoomIn;
    QAction *zoomOut;
    QAction *about;

    void creatToolBar();
    void creatStatusBar();
    void creatContextMenu();
    void creatChartPanel();

private slots:
    void setMyDrat(bool ok);
    void setMySelect(bool ok);
    void showAbout();
    void changeMySceneColor();
    void centerTheView();
    void updateChart();
};

#endif // MAINWINDOW_H
