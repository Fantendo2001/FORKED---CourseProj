
#include "revive.h"
#include <iostream>

using namespace std;

Revive::Revive(int pos, QObject * parent): GameElement (parent)
{
    this->startPosition = pos;
    this->frequency = 20000;
    this->loadframe();
    this->init();
}

void Revive::init()
{
    enabledLogic = 1;
    this->reviveRect.setRect(6000 + this->startPosition * 175.6 + qrand() % this->frequency, qrand() % 520 + 80, 95, 110);
}

void Revive::logic()
{
    if (!this->enabledLogic){
        return;
    }
    this->reviveRect.translate(-20,0);
    if (this->reviveRect.right() < 0) {
        this->reviveRect.moveTo(6000 + qrand() % this->frequency, qrand() % 520 + 80);
    }
}


void Revive::draw(QPainter * painter)
{
    if (!this->enabledDraw)
        return;

    painter->drawPixmap(static_cast <int> (this->reviveRect.x()),
                        static_cast <int> (this->reviveRect.y()),
                        static_cast <int> (this->reviveRect.width()),
                        static_cast <int> (this->reviveRect.height()),
                        this->pixmapList[0]);
}

void Revive::loadframe(){
    this->clearAllFrame();
    this->addFrame(QPixmap(":/image/udisk.png"));
}

QRectF & Revive::getRect(){
    return this->reviveRect;
}

void Revive::hit(){
    this->reviveRect.moveTo(6000 + qrand() % this->frequency, qrand() % 520 + 80);
}


void Revive::setDifficulty(string difficulty)
{
    if (difficulty == "EASY")
    {
        this->frequency = 5000;
    }
    else if (difficulty == "MEDIUM")
    {
        this->frequency = 6000;
    }
    else
    {
        this->frequency = 7000;
    }
}
