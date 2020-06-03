
#include "player.h"
#include <iostream>
#include <ctime>

using namespace std;


Player::Player(QObject *parent) :
    GameElement(parent)
{
    this->num = 0;
    this->state = RUN;
    this->init();
    this->hasShield = 0;
    connect(&timer,SIGNAL(timeout()),this,SLOT(updateFrame()));
    connect(&timer,SIGNAL(timeout()),this,SLOT(detectState()));
}

void Player::init()
{
    this->loadFrame();
    this->currentFrame = 1;
    this->hasShield = 0;
    this->jumpTime = 0;
    this->speedX = 7.0;
    this->speedY = 0;
    this->increaseY = 1.2;
    this->bindRect.setRect(200, 562, 80.0, 120.0);
    this->timer.start(90);
}

void Player::logic()
{
    if( !this->enabledLogic )
    {
        return;
    }

    //Y
    this->speedY += this->increaseY;
    if(this->speedY > 14.0)
    {
        this->speedY = 14.0;
    }
        this->bindRect.translate(0,this->speedY);

    //limit
    if(this->bindRect.top() < -this->bindRect.height() && this->state != FALLDOWN)
        this->bindRect.moveTop(-this->bindRect.height());


    if(isCloud && this->bindRect.bottom() < 440)
    {
        if(this->bindRect.bottom() > 425.0 && this->speedY >= 0)    // the height of cloud
        {
            this->bindRect.moveBottom(425.0);
            jumpTime = 0;
            this->speedY = 0;
        }
    }

    else
    {
        if(this->state != FALLDOWN && this->bindRect.bottom() > 682.0)
        {
            this->bindRect.moveBottom(682.0);
            jumpTime = 0;
            this->speedY = 0;
        }
    }
    return;
}


void Player::leftMove()
{
   this->bindRect.translate(3, 0);
}



void Player::draw(QPainter *painter)
{
    if( !this->enabledDraw )
        return;

    painter->save();
    painter->translate(this->bindRect.center());
    painter->translate(-this->bindRect.center());

    if (this->state == DOWN && this->num == 1)
    {
        painter->drawPixmap(static_cast <int> (this->bindRect.x()),
                            static_cast <int> (this->bindRect.y()),
                            static_cast <int> (this->bindRect.width()),
                            static_cast <int> (this->bindRect.height()),
                            QPixmap(":/image/player1_down.png"));
    }

    else if (this->state == DOWN && this->num == 2)
    {
        painter->drawPixmap(static_cast <int> (this->bindRect.x()),
                            static_cast <int> (this->bindRect.y()),
                            static_cast <int> (this->bindRect.width()),
                            static_cast <int> (this->bindRect.height()),
                            QPixmap(":/image/player2_down.png"));
    }

    else
    {
        painter->drawPixmap(static_cast <int> (this->bindRect.x()),
                            static_cast <int> (this->bindRect.y()),
                            static_cast <int> (this->bindRect.width()),
                            static_cast <int> (this->bindRect.height()),
                            this->pixmapList[this->currentFrame]);
    }

    painter->restore();
}

void Player::loadFrame()
{
    switch(this->num)
    {
    case 1:
        this->clearAllFrame();
        this->addFrame(QPixmap(":/image/player1_1.png"));
        this->addFrame(QPixmap(":/image/player1_2.png"));
        this->addFrame(QPixmap(":/image/player1_3.png"));
        this->addFrame(QPixmap(":/image/player1_4.png"));
        this->addFrame(QPixmap(":/image/player1_5.png"));
        this->addFrame(QPixmap(":/image/player1_6.png"));
        this->addFrame(QPixmap(":/image/player1_7.png"));
        this->addFrame(QPixmap(":/image/player1_8.png"));
        this->addFrame(QPixmap(":/image/player1_9.png"));
        this->addFrame(QPixmap(":/image/player1_10.png"));
        this->addFrame(QPixmap(":/image/player1_11.png"));
        this->addFrame(QPixmap(":/image/player1_12.png"));
        break;
    case 2:
        this->clearAllFrame();
        this->addFrame(QPixmap(":/image/player2_1.png"));
        this->addFrame(QPixmap(":/image/player2_2.png"));
        this->addFrame(QPixmap(":/image/player2_3.png"));
        this->addFrame(QPixmap(":/image/player2_4.png"));
        this->addFrame(QPixmap(":/image/player2_5.png"));
        this->addFrame(QPixmap(":/image/player2_6.png"));
        this->addFrame(QPixmap(":/image/player2_7.png"));
        this->addFrame(QPixmap(":/image/player2_8.png"));
        this->addFrame(QPixmap(":/image/player2_9.png"));
        this->addFrame(QPixmap(":/image/player2_10.png"));
        this->addFrame(QPixmap(":/image/player2_11.png"));
        break;
    }
}

void Player::jump()
{
    if (jumpTime < 2){
        this->jumpTime ++;
        this->speedY = -20.2;
    }
    this->state = JUMP;
}

void Player::updateFrame()
{
    if( !this->enabledDraw )
        return;


    this->currentFrame++;

    if (this->currentFrame >= this->pixmapList.length())
    {
        this->currentFrame = 0;
    }
}


void Player::detectState()
{
   if (this->state != FALLDOWN && this->state != DOWN)
   {
        if (this->bindRect.bottom() >= 680)
        {
            this->state = RUN;
        }

        else
        {
            this->state = JUMP;
        }
    }
}


PlayerStatus Player::getState()
{
    return  this->state;
}

void Player::setNum(int num)
{
    this->num = num;
}

void Player::fallDown()
{
    this->state = FALLDOWN;
}

void Player::setState(PlayerStatus state)
{
    this->state = state;
}

void Player::setIsCloud(bool x)
{
    this->isCloud = x;
}

int Player::getJumpTime()
{
    return this->jumpTime;
}

void Player::setSpeedY(int v)
{
    this->speedY = v;
}

void Player::getShield()
{
    if (hasShield == 1)
    {
        shieldTimer->stop();
        shieldTimer->start(5000);
        hasShield = 1;
    }
    connect(shieldTimer, SIGNAL(timeout()), this, SLOT(loseShield()));
    shieldTimer->start(5000);
    hasShield = 1;
    QTimer::singleShot(5000, this, SLOT(loseShield()));
}

void Player::loseShield()
{
    hasShield = 0;
}


void Player::playerDown()
{
    this->state = DOWN;
    this->bindRect.setRect(200, 600, 120, 80);
    QTimer::singleShot(600, this, SLOT(downToUp()));
}

void Player::downToUp()
{
    this->state = RUN;
    this->bindRect.setRect(200, 562, 80, 120);
}
