#include "finalfire.h"
#include "iostream"

FinalFire::FinalFire(QObject * parent): GameElement(parent)
{
    this->hited = 0;
    this->loadFrame();
    this->init();
}

void FinalFire::loadFrame(){
    this->clearAllFrame();
    this->addFrame(QPixmap(":/image/final.png"));
}

void FinalFire::init(){
    enabledLogic = 1;
    this->frequency = 6000;
    this->limitFrequency = 3000;
    this->increaseFrequency = 1;
    this->finalFireRect.setRect(1400 + qrand() % this->frequency, 580, 70, 250);
    this->speedX = 10;
    this->increaseX = 0.01;
}

void FinalFire::logic()
{
    if (!this->enabledLogic)
    {
        return;
    }

    this->speedX += this->increaseX;
    if (this->speedX > 14.0){
        this->speedX = 14.0;
    }
    this->finalFireRect.translate(-this->speedX,0);

    this->frequency -= this->increaseFrequency;
    if (this->frequency < this->limitFrequency){
        this->frequency = this->limitFrequency;
    }

    if (this->finalFireRect.right() < 0){
        this->finalFireRect.moveTo(1400 + qrand() % this->frequency, 580);
    }
}

void FinalFire::draw(QPainter * painter){
    if (!this->enabledDraw){
        return;
    }

    painter->drawPixmap(static_cast <int> (this->finalFireRect.x()),
                        static_cast <int> (this->finalFireRect.y()),
                        static_cast <int> (this->finalFireRect.width()),
                        static_cast <int> (this->finalFireRect.height()),
                        this->pixmapList[0]);
}

QRectF & FinalFire::getRect()
{
    return this->finalFireRect;
}

void FinalFire::hit()
{
    this->finalFireRect.moveTo(1400 + qrand() % this->frequency, 580);
}

void FinalFire::hitFire()
{
    this->hited = 1;
    QTimer::singleShot(400,this,SLOT(hitFinish()));
}

void FinalFire::hitFinish()
{
    this->hited = 0;
}

void FinalFire::setDifficulty(string difficulty)
{
    if (difficulty == "EASY")
    {
        this->frequency = 7000;
        this->limitFrequency = 4000;
    }
    else if (difficulty == "MEDIUM")
    {
        this->frequency = 6000;
        this->limitFrequency = 3000;
    }
    else
    {
        this->frequency = 5000;
        this->limitFrequency = 2000;
    }
}
