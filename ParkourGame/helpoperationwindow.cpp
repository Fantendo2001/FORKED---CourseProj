
#include "helpoperationwindow.h"
#include <iostream>

using namespace std;

HelpOperaionWindow::HelpOperaionWindow(QObject *parent) :
    GameElement(parent)
{
    this->init();
}

void HelpOperaionWindow::init()
{
    enabledLogic = 0;
    enabledDraw = 0;
}

void HelpOperaionWindow::logic()
{
    if(!this->enabledLogic)
        return;
}

void HelpOperaionWindow::draw(QPainter *painter)
{
    if(!this->enabledDraw)
        return;

    painter->drawPixmap(0, 0, 1440, 800, QPixmap(":/image/background4.png"));

    painter->drawPixmap(200, 0, 1040, 200, QPixmap(":/image/operationENG.png"));

    painter->drawPixmap(150, 100, 1140, 700, QPixmap(":/image/back.png"));

    painter->drawPixmap(450, 300, 60, 60, QPixmap(":/image/w.png"));

    painter->drawPixmap(520, 310, 500, 80, QPixmap(":/image/help_w.png"));

    painter->drawPixmap(450, 500, 60, 60, QPixmap(":/image/s.png"));

    painter->drawPixmap(520, 510, 500, 80, QPixmap(":/image/help_s.png"));

}

