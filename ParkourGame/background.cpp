
#include "background.h"


Background::Background(QObject *parent) :
    GameElement(parent)
{
    this->init();
}

void Background::init()
{
    this->loadFrame();
    this->currentFrame = 0;
    this->bindRect.setRect(0,0,1440, 800);
    this->enabledDraw = true;
}

void Background::logic()
{
    if(!this->enabledLogic)
        return;
}

void Background::draw(QPainter *painter)
{
    if(!this->enabledDraw)
        return;

    painter->drawPixmap(static_cast <int> (this->bindRect.x()),
                        static_cast <int> (this->bindRect.y()),
                        static_cast <int> (this->bindRect.width()),
                        static_cast <int> (this->bindRect.height()),
                        this->pixmapList[this->currentFrame]);
}

void Background::loadFrame()
{
    this->clearAllFrame();
    this->addFrame(QPixmap(":/image/start.png"));   //  The background of the start page

}

