
#ifndef SHIELD_H
#define SHIELD_H

#include "gameelement.h"
#include <string>

using namespace std;

class Shield: public GameElement
{
    Q_OBJECT

public:
    explicit Shield(int, QObject * parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
    void hit();
    void setDifficulty(string difficulty);
    QRectF & getRect();

private:
    QRectF shieldRect;
    int startPosition;
    int frequency;
    void loadframe();
};

#endif // SHIELD_H
