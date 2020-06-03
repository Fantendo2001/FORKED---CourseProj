
#include "coin.h"

Coin::Coin(int pos, QObject * parent): GameElement (parent)
{
    this->startPosition = pos;
    this->loadFrame();
    this->init();
}

void Coin::init(){
    enabledLogic = 1;
    this->coinRect.setRect(3000 + this->startPosition * 175.6 + qrand() % 3000, qrand() % 520 + 80, 50, 50);
    this->speedX = 10;
    this->increaseX = 0.01;
}

void Coin::logic(){
    if (!this->enabledLogic){
        return;
    }

    this->speedX += this->increaseX;
    if (this->speedX > 14.0){
        this->speedX = 14.0;
    }
    this->coinRect.translate(-this->speedX,0);

    if (this->coinRect.right() < 0){
        this->coinRect.moveTo(1500 + qrand() % 3000, qrand() % 520 + 80);
    }
}

void Coin::draw(QPainter * painter){
    if (!this->enabledDraw){
        return;
    }

    painter->drawPixmap(static_cast <int> (this->coinRect.x()),
                        static_cast <int> (this->coinRect.y()),
                        static_cast <int> (this->coinRect.width()),
                        static_cast <int> (this->coinRect.height()),
                        this->pixmapList[0]);
}

QRectF & Coin::getRect(){
    return this->coinRect;
}

void Coin::hit(){
    this->coinRect.moveTo(1500 + qrand() % 3000, qrand() % 520 + 80);
}

void Coin::loadFrame(){
    this->clearAllFrame();
    this->addFrame(QPixmap(":/image/coin.png"));
}
