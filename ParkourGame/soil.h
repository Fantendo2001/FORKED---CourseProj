#ifndef SOIL_H
#define SOIL_H

#include <string>
#include "gameelement.h"

using namespace std;

class Soil : public GameElement
{
    Q_OBJECT

public:
    explicit Soil(int pos, QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
    bool getShow();
    void setPreviousShow(bool x);
    void setDifficulty(string difficulty);
    void setProb(bool open);
    QRectF &getRect();

private:
    int currentFrame;
    int startPosition;
    int frequency;
    double positionX;
    double speedX;
    double increaseX;
    bool show;
    bool isPreviousShow;
    QRectF soilRect;
    bool probSwitch;

    bool randomPro();
};

#endif // SOIL_H
