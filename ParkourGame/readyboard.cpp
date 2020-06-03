
#include "readyboard.h"

ReadyBoard::ReadyBoard(QObject *parent) :
    GameElement(parent)
{
    this->addFrame(QPixmap(":/image/game_ready.png"));
    this->addFrame(QPixmap(":/image/begin.png"));
    this->init();
}

void ReadyBoard::init()
{
}

void ReadyBoard::logic()
{
    if(!this->enabledLogic)
        return;
}

void ReadyBoard::draw(QPainter *painter)
{
    if(!this->enabledDraw)
        return;
    painter->drawPixmap(625, 200.0, 200.0, 100.0,
                        this->pixmapList[0]);

    painter->drawPixmap(520, 570.0, 400.0, 130.0,
                        this->pixmapList[1]);

}
