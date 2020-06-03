
#include "jumpfire.h"
#include <iostream>
#include <ctime>

using namespace std;


JumpFire::JumpFire(QObject *parent) :
    GameElement(parent)
{
    this->init();
    this->display = 0;
    this->currentFrame = 0;
    this->lastingTime = 5;
    this->addFrame(QPixmap(":/image/fire.png"));
}

void JumpFire::init()
{
    this->bindRect.setRect(200, 562, 100.0, 80.0);
}

void JumpFire::logic()
{
    if( !this->enabledLogic )
    {
        return;
    }

    this->bindRect.moveTop(this->positionY - 20);

}



void JumpFire::draw(QPainter *painter)
{
    if( !this->enabledDraw || !this->display)
        return;

    painter->drawPixmap(static_cast <int> (this->bindRect.x()),
                        static_cast <int> (this->bindRect.y()),
                        static_cast <int> (this->bindRect.width()),
                        static_cast <int> (this->bindRect.height()),
                        this->pixmapList[this->currentFrame]);

    this->lastingTime --;
    if (this->lastingTime == 0){
        this->display = false;
        this->lastingTime = 5;
    }
}

void JumpFire::setPositionY(double pos)
{
    this->positionY = pos;
}

void JumpFire::setDisplay(bool isSecondJump)
{
    this->display = isSecondJump;
}
