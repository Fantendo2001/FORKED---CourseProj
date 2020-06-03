

#include "shield.h"

Shield::Shield(int pos, QObject * parent): GameElement(parent)
{
    this->startPosition = pos;
    this->loadframe();
    this->init();
}

void Shield::init()
{
    this->enabledLogic = 1;
    this->frequency = 20000;
    this->shieldRect.setRect(4000 + this->startPosition * 175.6 + qrand() % this->frequency, qrand() % 520 + 80, 95, 110);
}

void Shield::logic()
{
    if (!this->enabledLogic){
        return;
    }
    this->shieldRect.translate(-20,0);
    if (this->shieldRect.right() < 0) {
        this->shieldRect.moveTo(4000 + qrand() % this->frequency, qrand() % 520 + 80);
    }
}



void Shield::draw(QPainter * painter)
{
    if (!this->enabledDraw)
        return;

    painter->drawPixmap(static_cast <int> (this->shieldRect.x()),
                        static_cast <int> (this->shieldRect.y()),
                        static_cast <int> (this->shieldRect.width()),
                        static_cast <int> (this->shieldRect.height()),
                        this->pixmapList[0]);
}


void Shield::loadframe()
{
    this->clearAllFrame();
    this->addFrame(QPixmap(":/image/dunpai.png"));
}

QRectF & Shield::getRect()
{
    return this->shieldRect;
}

void Shield::hit(){
    this->shieldRect.moveTo(4000 + qrand() % this->frequency, qrand() % 520 + 80);
}

void Shield::setDifficulty(string difficulty)
{
    if (difficulty == "EASY")
    {
        this->frequency = 10000;
    }
    else if (difficulty == "MEDIUM")
    {
        this->frequency = 12000;
    }
    else
    {
        this->frequency = 14000;
    }
}
