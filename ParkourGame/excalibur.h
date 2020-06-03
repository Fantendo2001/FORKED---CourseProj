#ifndef EXCALIBUR_H
#define EXCALIBUR_H

#include "gameelement.h"
#include <string>

using namespace std;

class Excalibur: public GameElement
{
    Q_OBJECT

public:
    explicit Excalibur(int, QObject * parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
    void hit();
    QRectF & getRect();
    void setDifficulty(string difficulty);

private:
    QRectF excaliburRect;
    int startPosition;
    int frequency;
    void loadframe();
};
#endif // EXCALIBUR_H
