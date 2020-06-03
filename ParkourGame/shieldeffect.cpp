

#include "shieldeffect.h"
#include <iostream>
#include <ctime>

using namespace std;


ShieldEffect::ShieldEffect(QObject *parent) :
    GameElement(parent)
{
    this->init();
    this->display = 0;
    this->currentFrame = 0;
    this->circle = 0;
    this->addFrame(QPixmap(":/image/shieldeffect.png"));;
}

void ShieldEffect::init()
{
    this->bindRect.setRect(200, 562, 80.0, 120.0);
}

void ShieldEffect::logic()
{
    if( !this->enabledLogic || !this->display )
    {
        return;
    }

    if (this->circle == 10) this->circle = 0;
    this->circle ++;
    this->bindRect.setRect(200-circle, 562-circle, 80 + 2*circle, 120 + 2*circle );

    this->bindRect.moveBottom(this->positionY);
}



void ShieldEffect::draw(QPainter *painter)
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

}

void ShieldEffect::setPositionY(double pos)
{
    this->positionY = pos;
}

void ShieldEffect::setDisplay(bool hasShield)
{
    this->display = hasShield;
}
