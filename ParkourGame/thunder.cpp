#include "thunder.h"
#include <iostream>

Thunder::Thunder(QObject * parent): GameElement (parent)
{
    this->hited = 0;
    this->init();
    connect(&timer,SIGNAL(timeout()), this, SLOT(updateFrame()));
}

void Thunder::init()
{
    this->loadFrame();
    this->lastFrame = 0;
    this->frequency = 6000;
    this->increaseFrequency = 1;
    this->limitFrequency = 3000;
    this->currentFrame = 1;
    this->speedX = 10;
    this->increaseX = 0.01;
    this->thunderRect.setRect(2300 + qrand() % this->frequency, -20, 80, 250);
    this->timer.start(100);
}

void Thunder::logic(){
    if (!enabledLogic){
        return;
    }

    this->frequency -= this->increaseFrequency;
    if (this->frequency < this->limitFrequency)
    {
        this->frequency = this->limitFrequency;
    }

    this->speedX += this->increaseX;
    if (this->speedX > 14.0)
    {
        this->speedX = 14.0;
    }

    this->thunderRect.translate(-this->speedX,0);

    if (this->thunderRect.right() < 0)
    {
        this->thunderRect.moveTo(2300 + qrand() % this->frequency, -20);
    }
}

void Thunder::draw(QPainter * painter)
{
    if( !this->enabledDraw )
        return;

    painter->drawPixmap(static_cast <int> (this->thunderRect.x()),
                        static_cast <int> (this->thunderRect.y()),
                        static_cast <int> (this->thunderRect.width()),
                        static_cast <int> (this->thunderRect.height()),
                        this->pixmapList[this->currentFrame]);
}

void Thunder::loadFrame()
{
    this->clearAllFrame();
    this->addFrame(QPixmap(":/image/shandian1.png"));
    this->addFrame(QPixmap(":/image/shandian2.png"));
}

void Thunder::updateFrame()
{
    if( !this->enabledDraw )
        return;
    int swap = this->currentFrame;
    this->currentFrame = this->lastFrame;
    this->lastFrame = swap;
}

QRectF & Thunder::getRect()
{
    return this->thunderRect;
}

void Thunder::hit()
{
    this->thunderRect.moveTo(2300 + qrand() % this->frequency, -20);
}

void Thunder::hitThunder()
{
    this->hited = 1;
    QTimer::singleShot(300,this,SLOT(hitFinish()));
}

void Thunder::hitFinish()
{
    this->hited = 0;
}

void Thunder::setDifficulty(string difficulty)
{
    if (difficulty == "EASY")
    {
        this->frequency = 6500;
        this->limitFrequency = 3500;
    }
    else if (difficulty == "MEDIUM")
    {
        this->frequency = 6000;
        this->limitFrequency = 3000;
    }
    else
    {
        this->frequency = 5500;
        this->limitFrequency = 2500;
    }
}
