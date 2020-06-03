#include "choosedifficulty.h"
#include <iostream>

using namespace std;

ChooseDifficulty::ChooseDifficulty(QObject *parent) :
    GameElement(parent)
{
    this->loadFrame();
    this->init();
}

void ChooseDifficulty::init()
{
    this->bindRect.setRect(0,0,1440, 800);
    this->controlSignal = 0;
}

void ChooseDifficulty::logic()
{
    this->controlSignal++;

    if (this->controlSignal >= 20)
    {
        controlSignal = 0;
    }
}

void ChooseDifficulty::draw(QPainter *painter)
{
    if(!this->enabledDraw)
        return;

    painter->drawPixmap(static_cast <int> (this->bindRect.x()),
                        static_cast <int> (this->bindRect.y()),
                        static_cast <int> (this->bindRect.width()),
                        static_cast <int> (this->bindRect.height()),
                        this->pixmapList[0]);

    if (this->controlSignal < 10)
    {
        painter->drawPixmap(220, 50, 1000, 100,
                            this->pixmapList[1]);
    }

}

void ChooseDifficulty::loadFrame()
{
    this->addFrame(QPixmap(":/image/Bg.png"));
    this->addFrame(QPixmap(":/image/welcomeSlogen.png"));
}

