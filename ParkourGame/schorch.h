#ifndef SCHORCH_H
#define SCHORCH_H

#include <QTimer>
#include <qmath.h>
#include "gameelement.h"

class Schorch : public GameElement
{
    Q_OBJECT

public:
    explicit Schorch(QObject *parent = 0);
    void init();
    void logic();
    void draw(QPainter *);
    void setDisplay(bool isGPAdecrease);
    void setPositionY(double pos);

signals:

private:

    bool display;
    int currentFrame;
    int lastingTime;
    double positionY;
    QTimer timer;

    void loadFrame();

};
#endif // SCHORCH_H
