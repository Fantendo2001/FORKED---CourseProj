
#include "reviveeffect.h"
#include <iostream>
#include <ctime>

using namespace std;


ReviveEffect::ReviveEffect(QObject *parent) :
    GameElement(parent)
{
    this->init();
    this->display = 0;
    this->currentFrame = 0;
    this->lastingTime = 20;
    this->addFrame(QPixmap(":/image/reviveeffect.png"));
}

void ReviveEffect::init()
{
    this->bindRect.setRect(190, 562, 100.0, 100);
}

void ReviveEffect::logic()
{
    if( !this->enabledLogic || !this->display)
    {
        return;
    }

    this->bindRect.moveBottom(this->positionY - 300 + this->lastingTime * 10);

}



void ReviveEffect::draw(QPainter *painter)
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
        this->lastingTime = 20;
    }
}

void ReviveEffect::setPositionY(double pos)
{
    this->positionY = pos;
}

void ReviveEffect::setDisplay(bool isGPAIncrease)
{
    this->display = isGPAIncrease;
}
