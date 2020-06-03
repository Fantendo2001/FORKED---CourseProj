#include <iostream>
#include "gamebackground.h"

using namespace std;

GameBackground::GameBackground(QObject *parent) :
    GameElement(parent)
{
    this->loadFrame();
    this->init();
    this->timer.start(5000);
    connect(&timer,SIGNAL(timeout()),this,SLOT(updateFrame()));
}

void GameBackground::init()
{
    this->bindRect.setRect(0,0,1440, 800);
    this->lastFrame = 0;
    this->currentFrame = 1;
    this->speedX = 2.5;
    this->increaseX = 0.01;
    this->positionX = 0;
}

void GameBackground::logic()
{
    if( !this->enabledLogic )
        return;
}

void GameBackground::draw(QPainter *painter)
{
    if( !this->enabledDraw )
        return;

    cout << this->currentFrame << endl;

    painter->drawPixmap(static_cast <int> (this->positionX),
                        static_cast <int> (this->bindRect.topLeft().y()),
                        static_cast <int> (this->bindRect.width()),
                        static_cast <int> (this->bindRect.height()),
                        this->pixmapList[this->currentFrame]);
}

void GameBackground::loadFrame()
{
        this->clearAllFrame();
        this->addFrame(QPixmap(":/image/ground1.png"));
        this->addFrame(QPixmap(":/image/ground6.png"));
        this->addFrame(QPixmap(":/image/ground2.png"));
        this->addFrame(QPixmap(":/image/ground3.png"));
        this->addFrame(QPixmap(":/image/ground5.png"));
}

void GameBackground::updateFrame()
{
    if( !this->enabledDraw )
        return;

    this->currentFrame++;

    if (this->currentFrame >= this->pixmapList.length())
    {
        this->currentFrame = 0;
    }
}
