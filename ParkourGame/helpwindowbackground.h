#ifndef HELPWINDOW_H
#define HELPWINDOW_H


#include "gameelement.h"

class HelpWindowBackground : public GameElement
{
    Q_OBJECT
public:
    explicit HelpWindowBackground(QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();

private:
    int currentFrame;
    void loadFrame();
};



#endif // HELPWINDOW_H
