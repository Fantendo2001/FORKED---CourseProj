#ifndef ALLCLEAR_H
#define ALLCLEAR_H

#include <QTimer>
#include <qmath.h>
#include "gameelement.h"

class AllClear : public GameElement
{
    Q_OBJECT

public:
    explicit AllClear(QObject *parent = 0);
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
    int circle;
    QTimer timer;
    void loadFrame();

};

#endif // ALLCLEAR_H
