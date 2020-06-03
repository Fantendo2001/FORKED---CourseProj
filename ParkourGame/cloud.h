#ifndef CLOUD_H
#define CLOUD_H

#include <string>
#include "gameelement.h"

using namespace std;

class Cloud : public GameElement
{
    Q_OBJECT

public:
    explicit Cloud(int pos, QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
    bool isShow();
    void setPreviousShow1(bool x);
    void setPreviousShow2(bool x);
    bool isOverPlayer();
    void setDifficulty(string difficulty);
    QRectF &getRect();

private:
    int currentFrame;
    int startPosition;

    int frequency;

    double positionX;
    double speedX;
    double increaseX;

    bool randomPro();
    bool show;
    bool isPreviousShow1;   // whether the second cloud before this cloud show
    bool isPreviousShow2;
    bool isPlayerPosition; // determine whether this cloud is at player's Xposition
    QRectF cloudRect;

};

#endif // CLOUD_H

