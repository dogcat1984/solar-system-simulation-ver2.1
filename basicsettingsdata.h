#ifndef BASICSETTINGSDATA_H
#define BASICSETTINGSDATA_H


class BasicSettingsData
{
public:
    BasicSettingsData();
    double gravitationConstant;
    int simulationStep;
    double timePerStep;
    int timer;
    int chartUpdateTime;
    double sceneWidth;
    double sceneHeight;
};

#endif // BASICSETTINGSDATA_H
