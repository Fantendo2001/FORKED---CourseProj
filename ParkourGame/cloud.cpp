

#include "cloud.h"
#include <istream>
#include <iostream>

using namespace std;

Cloud::Cloud(int pos, QObject *parent) :
    GameElement(parent)
{
    this->startPosition = pos;
    this->addFrame(QPixmap(":/image/cloud.png"));
    this->init();
}

void Cloud::init()
{
    this->currentFrame = 0;
    this->frequency = 6;
    this->speedX = 50;
    this->show = 0;
    this->increaseX = 0.01;
    this->cloudRect.setRect(0 + startPosition * 120,
                           380, 180, 90);
}

void Cloud::logic()
{
    if( !this->enabledLogic )
        return;

    this->speedX += this->increaseX;
    if(this->speedX > 14.0)
    {
        this->speedX = 14.0;
    }

    this->cloudRect.translate(-speedX, 0);

    if(this->cloudRect.right() <= 0)
    {
        this->cloudRect.moveTo(1440 + cloudRect.right(), 380);
        //************************************************//
        if (!isPreviousShow1 && isPreviousShow2){    // Let the clouds appear at least two together
            show = 1;
        }else{
        this->show = !randomPro();
        }
    }

    if (this->cloudRect.left() <= 240 && this->cloudRect.right() >= 240 && this->show ){    // Let player stand on the cloud
        this->isPlayerPosition = 1;
    }else{
        this->isPlayerPosition = 0;
    }
}


void Cloud::draw(QPainter *painter)
{
    if( !this->enabledDraw || !this->show)
        return;

    painter->drawPixmap(static_cast <int> (this->cloudRect.x()),
                        static_cast <int> (this->cloudRect.y()),
                        static_cast <int> (this->cloudRect.width()),
                        static_cast <int> (this->cloudRect.height()),
                        this->pixmapList[this->currentFrame]);
}

bool Cloud::randomPro()
{
    int num = qrand() % this->frequency;  // The frequency of the appearance of clouds
    if (num == 0)
        return false;
    return true;
}

bool Cloud::isShow()
{
    return this->show;
}

void Cloud::setPreviousShow1(bool x)
{
    this->isPreviousShow1 = x;
    return;
}

void Cloud::setPreviousShow2(bool x)
{
    this->isPreviousShow2 = x;
    return;
}

bool Cloud::isOverPlayer(){
    return this->isPlayerPosition;
}


void Cloud::setDifficulty(string difficulty)
{
    if (difficulty == "EASY")
    {
        this->frequency = 5;
    }
    else if (difficulty == "MEDIUM")
    {
        this->frequency = 6;
    }
    else
    {
        this->frequency = 7;
    }
}
