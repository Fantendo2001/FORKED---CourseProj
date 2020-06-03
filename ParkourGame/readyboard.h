#ifndef READYBOARD_H
#define READYBOARD_H

#include "gameelement.h"

class ReadyBoard : public GameElement
{
    Q_OBJECT
public:
    explicit ReadyBoard(QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
signals:

public slots:

};

#endif // READYBOARD_H
