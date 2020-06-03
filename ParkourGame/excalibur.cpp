

#include "excalibur.h"

Excalibur::Excalibur(int pos, QObject * parent): GameElement (parent)
{
    this->startPosition = pos;
    this->loadframe();
    this->init();
}

void Excalibur::init(){
    this->enabledLogic = 1;
    this->frequency = 20000;
    this->excaliburRect.setRect(5000 + this->startPosition * 175.6 + qrand() % frequency, qrand() % 520 + 80, 95, 110);
}

void Excalibur::logic()
{

    if (!this->enabledLogic){
        return;
    }
    this->excaliburRect.translate(-20,0);
    if (this->excaliburRect.right() < 0) {
        this->excaliburRect.moveTo(5000 + qrand() % frequency, qrand() % 520 + 80);
    }
}


void Excalibur::draw(QPainter * painter)
{
    if (!this->enabledDraw)
        return;

    painter->drawPixmap(static_cast <int> (this->excaliburRect.x()),
                        static_cast <int> (this->excaliburRect.y()),
                        static_cast <int> (this->excaliburRect.width()),
                        static_cast <int> (this->excaliburRect.height()),
                        this->pixmapList[0]);
}


void Excalibur::loadframe(){
    this->clearAllFrame();
    this->addFrame(QPixmap(":/image/recommend.png"));
}


QRectF & Excalibur::getRect(){
    return this->excaliburRect;
}


void Excalibur::hit()
{
    this->excaliburRect.moveTo(5000 + qrand() % frequency, qrand() % 520 + 80);
}

void Excalibur::setDifficulty(string difficulty)
{
    if (difficulty == "EASY")
    {
        this->frequency = 10000;
    }
    else if (difficulty == "MEDIUM")
    {
        this->frequency = 15000;
    }
    else
    {
        this->frequency = 20000;
    }
}


