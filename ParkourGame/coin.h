#ifndef COIN_H
#define COIN_H

#include "gameelement.h"
#include <QTime>
#include <QtGlobal>

class Coin: public GameElement
{
    Q_OBJECT

public:
    explicit Coin(int pos, QObject * parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
    void hit();
    QRectF &getRect();

private:
    double speedX;
    double increaseX;
    int startPosition;
    QRectF coinRect;

    void loadFrame();
};

#endif // COIN_H
