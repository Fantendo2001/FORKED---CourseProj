#ifndef ELEGROUND_H
#define ELEGROUND_H

#include <QTimer>
#include "gameelement.h"

class GameBackground : public GameElement
{
    Q_OBJECT

public:
    explicit GameBackground(QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();

signals:

public slots:
    void updateFrame();

private:
    int currentFrame;
    int lastFrame;
    int positionX;
    double speedX;
    double increaseX;
    QTimer timer;

    void loadFrame();
};

#endif // ELEGROUND_H
