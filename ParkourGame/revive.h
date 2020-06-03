#ifndef REVIVE_H
#define REVIVE_H

#include "gameelement.h"
#include <string>

using namespace std;

class Revive: public GameElement
{
    Q_OBJECT

public:
    explicit Revive(int, QObject * parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
    void hit();
    QRectF & getRect();
    void setDifficulty(string difficulty);

private:
    QRectF reviveRect;
    int startPosition;
    int frequency;
    void loadframe();
};

#endif // REVIVE_H
