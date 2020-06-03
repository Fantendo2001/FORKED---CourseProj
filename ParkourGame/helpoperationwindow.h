#ifndef HELPOPERATIONWINDOW_H
#define HELPOPERATIONWINDOW_H

#include "gameelement.h"

class HelpOperaionWindow : public GameElement
{
    Q_OBJECT

public:
    explicit HelpOperaionWindow(QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
};


#endif // HELPOPERATIONWINDOW_H
