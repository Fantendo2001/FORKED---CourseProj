#ifndef PLAY_H
#define PLAY_H

#include <QTimer>
#include <qmath.h>
#include "gameelement.h"

enum PlayerStatus{RUN,
                  JUMP,
                  DOWN,
                  FALLDOWN};

class Player : public GameElement
{
    Q_OBJECT

public:

    bool hasShield;

    explicit Player(QObject *parent = 0);
    void setNum(int num);
    void leftMove();
    void init();
    void logic();
    void draw(QPainter *);
    void jump();
    void setIsCloud(bool x);
    int getJumpTime();
    void setSpeedY(int v);
    void fallDown();
    void getShield();
    void playerDown();
    void setState(PlayerStatus state);
    PlayerStatus getState();

signals:

public slots:
    void updateFrame();
    void detectState();
    void loseShield();
    void downToUp();


private:
    int num;
    int lastFrame;
    int currentFrame;
    int jumpTime;
    double speedY;
    double increaseY;
    double speedX;
    bool isCloud;
    QTimer *shieldTimer = new QTimer(this);
    QTimer timer;
    PlayerStatus state;

    void loadFrame();
};

#endif // PLAY_H
