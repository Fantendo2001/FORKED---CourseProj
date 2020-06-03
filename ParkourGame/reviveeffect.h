#ifndef REVIVEEFFECT_H
#define REVIVEEFFECT_H


#include <QTimer>
#include <qmath.h>
#include "gameelement.h"

class ReviveEffect : public GameElement
{
    Q_OBJECT
public:
    explicit ReviveEffect(QObject *parent = 0);
    void init();
    void logic();
    void draw(QPainter *);
    void setDisplay(bool hasShield);
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
#endif // REVIVEEFFECT_H
