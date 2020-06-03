#ifndef HELPRULEWINDOW_H
#define HELPRULEWINDOW_H

#include "gameelement.h"

class HelpRuleWindow : public GameElement
{
    Q_OBJECT

public:
    explicit HelpRuleWindow(QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
};


#endif // HELPRULEWINDOW_H
