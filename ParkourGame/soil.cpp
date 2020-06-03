

#include "soil.h"
#include <istream>
#include <iostream>

using namespace std;

Soil::Soil(int pos, QObject *parent) :
    GameElement(parent)
{
    this->startPosition = pos;
    this->addFrame(QPixmap(":/image/tiles.png"));
    this->init();
}

void Soil::init()
{
    this->frequency = 5;
    this->currentFrame = 0;
    this->speedX = 10;
    this->show = 1;
    this->probSwitch = false;
    this->isPreviousShow = 1;
    this->increaseX = 0.01;
    this->soilRect.setRect(0 + startPosition * 120,
                           680, 120, 120);
}

void Soil::logic()
{
    if( !this->enabledLogic )
        return;

    this->speedX += this->increaseX;
    if(this->speedX > 30.0) // ********************//
    {
        this->speedX = 30.0;
    }

    this->soilRect.translate(-speedX, 0);

    if(this->soilRect.right() <= 0)
    {
        this->soilRect.moveTo(1440 + this->soilRect.right(), 680);
        if (! isPreviousShow)
        {
            show = 1;
        }
        else
        {
            if (probSwitch)
                this->show = randomPro();
        }

    }
}


void Soil::draw(QPainter *painter)
{
    if( !this->enabledDraw || !this->show)
        return;

    painter->drawPixmap(static_cast <int> (this->soilRect.x()),
                        static_cast <int> (this->soilRect.y()),
                        static_cast <int> (this->soilRect.width()),
                        static_cast <int> (this->soilRect.height()),
                        this->pixmapList[this->currentFrame]);
}

bool Soil::randomPro()
{
    int num = qrand() % this->frequency;
    if (num == 0)
        return false;
    return true;
}


QRectF& Soil::getRect()
{
        return this->soilRect;
}

bool Soil::getShow()
{
    return this->show;
}

void Soil::setPreviousShow(bool x)
{
    this->isPreviousShow = x;
    return;
}

void Soil::setDifficulty(string difficulty)
{
    if (difficulty == "EASY")
    {
        this->frequency = 100;
    }
    else if (difficulty == "MEDIUM")
    {
        this->frequency = 4;
    }
    else
    {
        this->frequency = 3;
    }
}

void Soil::setProb(bool open)
{
   this->probSwitch = open;
}
