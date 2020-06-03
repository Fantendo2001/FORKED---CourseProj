#include "allclear.h"
#include <iostream>
#include <ctime>

using namespace std;


AllClear::AllClear(QObject *parent) :
    GameElement(parent)
{
    this->init();
    this->display = 0;
    this->currentFrame = 0;
    this->lastingTime = 30;
    this->circle = 10;
    this->addFrame(QPixmap(":/image/allclear.png"));
}

void AllClear::init()
{
    this->bindRect.setRect(260, 150, 1000, 500);
}

void AllClear::logic()
{
    if( !this->enabledLogic || !this->display)
    {
        return;
    }

    if (this->circle == 10) this->circle = 0;
    this->circle ++;
    this->bindRect.setRect(260-5 * circle, 150- 5 * circle, 1000 + 10 * circle, 500 + 10 * circle );

}



void AllClear::draw(QPainter *painter)
{
    if( !this->enabledDraw || !this->display)
        return;

    painter->save();
    painter->translate(this->bindRect.center());
    painter->translate(-this->bindRect.center());

    painter->drawPixmap(static_cast <int> (this->bindRect.x()),
                        static_cast <int> (this->bindRect.y()),
                        static_cast <int> (this->bindRect.width()),
                        static_cast <int> (this->bindRect.height()),
                        this->pixmapList[this->currentFrame]);
    painter->restore();

    this->lastingTime --;
    if (this->lastingTime == 0){
        this->display = false;
        this->lastingTime = 30;
    }
}

void AllClear::setPositionY(double pos)
{
    this->positionY = pos;
}

void AllClear::setDisplay(bool isGPAdecrease)
{
    this->display = isGPAdecrease;
}
