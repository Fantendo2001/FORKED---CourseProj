#ifndef FINALFIRE_H
#define FINALFIRE_H

#include <QTimer>
#include <string>
#include "gameelement.h"

using namespace std;

class FinalFire: public GameElement
{
    Q_OBJECT
public:
    explicit FinalFire(QObject * parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
    void hit();
    QRectF & getRect();
    void hitFire();
    void setDifficulty(string difficulty);

signals:

public slots:
    void hitFinish();

private:
    double speedX;
    double increaseX;
    bool hited;
    int frequency;
    int increaseFrequency;
    int limitFrequency;

    QRectF finalFireRect;

    void loadFrame();
};

#endif // FINALFIRE_H
