#include "chooseplayer.h"
#include <iostream>

using namespace std;

ChoosePlayer::ChoosePlayer(int num, QObject *parent) :
    GameElement(parent)
{
    this->num = num;
    this->loadFrame();
    this->init();
    connect(&timer,SIGNAL(timeout()),this,SLOT(updateFrame()));
    timer.start(90);
}

void ChoosePlayer::init()
{
    this->lastFrame = 0;
    this->currentFrame = 1;

}

void ChoosePlayer::logic()
{
    if(!this->enabledLogic)
        return;
}

void ChoosePlayer::draw(QPainter *painter)
{
    if(!this->enabledDraw)
        return;
    if (num == 0)
    {
        painter->drawPixmap(350,
                            200,
                            300,
                            250,
                            this->pixmapList[this->currentFrame]);
    }

    if (num == 1)
    {
        painter->drawPixmap(790,
                            200,
                            300,
                            250,
                            this->pixmapList[this->currentFrame]);
    }

}

void ChoosePlayer::updateFrame()
{
    if( !this->enabledDraw )
        return;

    this->currentFrame++;

    if (this->currentFrame >= this->pixmapList.length())
    {
        this->currentFrame = 0;
    }
}

void ChoosePlayer::loadFrame()
{
    switch(this->num)
    {
    case 0:      
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
    case 1:
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
