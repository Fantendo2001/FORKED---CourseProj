#ifndef JUMPFIRE_H
#define JUMPFIRE_H

#include <QTimer>
#include <qmath.h>
#include "gameelement.h"

class JumpFire : public GameElement
{
    Q_OBJECT

public:
    explicit JumpFire(QObject *parent = 0);
    void init();
    void logic();
    void draw(QPainter *);
    void setDisplay(bool isSecondJump);
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

#endif // JUMPFIRE_H
