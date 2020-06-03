#include "helpitemswindow.h"
#include <iostream>

using namespace std;

HelpItemsWindow::HelpItemsWindow(QObject *parent) :
    GameElement(parent)
{
    this->init();
    this->timer.start(200);
    connect(&timer,SIGNAL(timeout()),this,SLOT(updateFrame()));
}

void HelpItemsWindow::init()
{
    enabledLogic = 0;
    enabledDraw = 0;
    this->loadFrame();
    this->angle = 0;
    this->lastFrame = 0;
    this->currentFrame = 1;
}

void HelpItemsWindow::logic()
{
    if(!this->enabledLogic)
        return;

    this->angle += -20;
}

void HelpItemsWindow::draw(QPainter *painter)
{
    if(!this->enabledDraw)
        return;

    painter->drawPixmap(0, 0, 1440, 800, QPixmap(":/image/background3.png"));

    painter->drawPixmap(250, 80, 940, 50, QPixmap(":/image/items2.png"));

    painter->drawPixmap(150, 100, 1140, 700, QPixmap(":/image/back.png"));

    painter->drawPixmap(370, 210, 85, 85, QPixmap(":/image/dunpai.png"));

    painter->drawPixmap(440, 240, 640, 35, QPixmap(":/image/help_sheild.png"));

    painter->drawPixmap(370, 300, 85, 85, QPixmap(":/image/recommend.png"));

    painter->drawPixmap(440, 320, 640, 70, QPixmap(":/image/help_letter.png"));

    painter->drawPixmap(365, 400, 85, 85, QPixmap(":/image/udisk.png"));

    painter->drawPixmap(410, 440, 550, 30, QPixmap(":/image/help_udisk.png"));

    painter->drawPixmap(380, 480, 50, 160, QPixmap(":/image/final.png"));

    painter->drawPixmap(430, 540, 180, 50, QPixmap(":/image/help_final.png"));

    painter->save();
    painter->translate(650, 565);
    painter->rotate(this->angle);
    painter->translate(-650, -565);
    painter->drawPixmap(600, 530, 100, 70, QPixmap(":/image/midterm2.png"));
    painter->restore();

    painter->drawPixmap(690, 540, 200, 50, QPixmap(":/image/help_midterm.png"));

    painter->drawPixmap(860, 480, 60, 160, pixmapList[this->currentFrame]);

    painter->drawPixmap(910, 540, 180, 50, QPixmap(":/image/help_quiz.png"));

}


void HelpItemsWindow::updateFrame()
{
    if( !this->enabledDraw )
        return;

    if(this->currentFrame == 1)
    {
        this->currentFrame = 0;
    }

    else
    {
        this->currentFrame = 1;
    }
}


void HelpItemsWindow::loadFrame()
{
        this->clearAllFrame();
        this->addFrame(QPixmap(":/image/shandian1.png"));
        this->addFrame(QPixmap(":/image/shandian2.png"));
}
