
# include "midterm.h"
#include <iostream>
#include <istream>
#include <ctime>
using namespace std;

Midterm::Midterm(int pos, QObject *parent) :
    GameElement(parent)
{
    this->startPosition = pos;
    this->loadFrame();
    this->init();
}

void Midterm::init()
{
    enabledLogic = true;
    this->angle = 0;
    this->frequency = 5000;
    this->limitFrequency = 3000;
    this->increaseFrequency = 1;
    this->currentFrame = 0;
    this->midtermPassEmited = false;
    this->midtermRect.setRect(3000 + this->startPosition * 175.6 + qrand() % this->frequency,  qrand() % 520 + 80,   90,   100);
    this->speedX = 15;
}

void Midterm::logic()
{

    if(!this->enabledLogic)
        return;

    this->angle += -4;
    this->midtermRect.translate(-this->speedX,0);

    if(this->midtermRect.right() < 0)
    {
        this->midtermRect.moveTo(3000 + qrand() % this->frequency, qrand() % 520 + 80);
    }

    this->frequency -= this->increaseFrequency;
    if (this->frequency < this->limitFrequency)
    {
        this->frequency = this->limitFrequency;
    }
}

void Midterm::draw(QPainter *painter)
{
    if (! this->enabledDraw)
        return;

    painter->save();
    painter->translate(this->midtermRect.center());
    painter->rotate(this->angle);
    painter->translate(-this->midtermRect.center());
    painter->drawPixmap(static_cast <int> (this->midtermRect.x()),
                        static_cast <int> (this->midtermRect.y()),
                        static_cast <int> (this->midtermRect.width()),
                        static_cast <int> (this->midtermRect.height()),
                        this->pixmapList[0]);
    painter->restore();
}

void Midterm::loadFrame()
{
    this->clearAllFrame();
    this->addFrame(QPixmap(":/image/midterm2.png"));
}

QRectF& Midterm::getRect()
{
        return this->midtermRect;
}

void Midterm::hit()
{
    this->midtermRect.moveTo(3000 + qrand() % this->frequency, qrand() % 520 + 80);
}

void Midterm::setDifficulty(string difficulty)
{
    if (difficulty == "EASY")
    {
        this->speedX = 15;
        this->frequency = 6000;
        this->limitFrequency = 3000;
    }
    else if (difficulty == "MEDIUM")
    {
        this->speedX = 20;
        this->frequency = 5500;
        this->limitFrequency = 2500;
    }
    else
    {
        this->speedX = 25;
        this->frequency = 5000;
        this->limitFrequency = 2000;
    }
}
