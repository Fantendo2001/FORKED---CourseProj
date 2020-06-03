#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "gameelement.h"

class Background : public GameElement
{
    Q_OBJECT

public:
    explicit Background(QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();

private:
    int currentFrame;
    void loadFrame();
};

#endif // BACKGROUND_H
