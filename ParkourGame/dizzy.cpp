#include "dizzy.h"
#include <iostream>
#include <ctime>

using namespace std;


Dizzy::Dizzy(QObject *parent) :
    GameElement(parent)
{
    this->init();
    this->display = 0;
    this->currentFrame = 0;
    this->lastingTime = 30;
    this->addFrame(QPixmap(":/image/dizzy.png"));
}

void Dizzy::init()
{
    this->bindRect.setRect(190, 562, 280.0, 240);
}

void Dizzy::logic()
{
    if( !this->enabledLogic || !this->display)
    {
        return;
    }

    this->bindRect.moveBottom(this->positionY - 100);

}



void Dizzy::draw(QPainter *painter)
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

void Dizzy::setPositionY(double pos)
{
    this->positionY = pos;
}

void Dizzy::setDisplay(bool isGPAdecrease)
{
    this->display = isGPAdecrease;
}
