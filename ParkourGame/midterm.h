#ifndef MIDTERM_H
#define MIDTERM_H

#include "gameelement.h"
#include <string>

using namespace std;

class Midterm : public GameElement
{
    Q_OBJECT

public:
    explicit Midterm(int pos,QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
    void hit();
    void setDifficulty(string difficulty);
    QRectF &getRect();

private:
    int frequency;
    int increaseFrequency;
    int limitFrequency;
    int currentFrame;
    double speedX;
    int startPosition;
    int angle;
    bool midtermPassEmited;
    QRectF midtermRect;

    void loadFrame();
};

#endif // MIDTERM_H
