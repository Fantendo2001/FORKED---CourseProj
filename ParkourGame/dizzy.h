#ifndef DIZZY_H
#define DIZZY_H

#include <QTimer>
#include <qmath.h>
#include "gameelement.h"

class Dizzy : public GameElement
{
    Q_OBJECT

public:
    explicit Dizzy(QObject *parent = 0);
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

#endif // DIZZY_H
