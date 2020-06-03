#ifndef THUNDER_H
#define THUNDER_H

#include <QTimer>
#include <string>
#include "gameelement.h"

using namespace std;

class Thunder: public GameElement
{
    Q_OBJECT

public:
    explicit Thunder(QObject * parent = 0);
    void init();
    void logic();
    void draw(QPainter *);
    QRectF & getRect();
    void hit();
    void hitThunder();
    void setDifficulty(string difficulty);

signals:

public slots:
    void updateFrame();
    void hitFinish();

private:
    int lastFrame;
    int currentFrame;
    int frequency;
    int limitFrequency;
    int increaseFrequency;
    double speedX;
    double increaseX;
    bool hited;
    QTimer timer;
    QRectF thunderRect;

    void loadFrame();

};

#endif // THUNDER_H
