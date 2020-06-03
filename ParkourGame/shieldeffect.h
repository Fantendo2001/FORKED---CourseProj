

#ifndef SHIELDEFFECT_H
#define SHIELDEFFECT_H

#include <QTimer>
#include <qmath.h>
#include "gameelement.h"

class ShieldEffect : public GameElement
{
    Q_OBJECT

public:
    explicit ShieldEffect(QObject *parent = 0);
    void init();
    void logic();
    void draw(QPainter *);
    void setDisplay(bool hasShield);
    void setPositionY(double pos);

signals:

private:

    bool display;
    int currentFrame;
    int circle;
    double positionY;
    QTimer timer;

    void loadFrame();

};


#endif // SHIELDEFFECT_H
