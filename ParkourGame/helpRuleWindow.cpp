
#include "helpRuleWindow.h"
#include <iostream>

using namespace std;

HelpRuleWindow::HelpRuleWindow(QObject *parent) :
    GameElement(parent)
{
    this->init();
}

void HelpRuleWindow::init()
{
    enabledLogic = 0;
    enabledDraw = 0;
}

void HelpRuleWindow::logic()
{
    if(!this->enabledLogic)
        return;
}

void HelpRuleWindow::draw(QPainter *painter)
{
    if(!this->enabledDraw)
        return;

    painter->drawPixmap(0, 0, 1440, 800, QPixmap(":/image/background1.png"));

    painter->drawPixmap(120, 85, 1140, 325, QPixmap(":/image/rules_blank.png"));

    painter->drawPixmap(150, 100, 1140, 700, QPixmap(":/image/back.png"));

    painter->drawPixmap(470, 240, 500, 450, QPixmap(":/image/rules.png"));
}

