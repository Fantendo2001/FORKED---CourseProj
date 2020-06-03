
#include "gpa.h"

Gpa::Gpa(QObject *parent) :
    GameElement(parent)
{
    this->loadFrame();
    this->init();
}

void Gpa::init()
{
    this->bindRect.setRect(200.0, 34, 22.0, 38.0);
    this->gpa = 4.00;
    this->gpaChange = new QSound(":/sounds/gpachange.wav");
    this->tempFirst = 0;
    this->tempSecond = 0;
    this->tempThird = 0;
}

void Gpa::logic()
{
    if(!this->enabledLogic)
    {
        return;
    }
    else
    {
        this->tempFirst = static_cast <int> (this->gpa);
        this->tempSecond = static_cast <int> (this->gpa * 10) % 10;
        this->tempThird = static_cast <int> (this->gpa * 100) % 10;
    }
}

void Gpa::draw(QPainter *painter)
{
    if(!this->enabledDraw)
    {
        return;
    }
    else
    {
            painter->drawPixmap(30,
                                0,
                                240,
                                100,
                                QPixmap(":/image/gpa.png"));

            painter->drawPixmap(static_cast <int> (this->bindRect.x() - 40.0),
                                static_cast <int> (this->bindRect.y()),
                                static_cast <int> (this->bindRect.width()),
                                static_cast <int> (this->bindRect.height()),
                                this->pixmapList[this->tempFirst]);

            painter->drawPixmap(static_cast <int> (this->bindRect.x() - 15),
                                static_cast <int> (this->bindRect.y()),
                                static_cast <int> (this->bindRect.width()),
                                static_cast <int> (this->bindRect.height()),
                                QPixmap(":/image/dot.png"));

            painter->drawPixmap(static_cast <int> (this->bindRect.x() - 5),
                                static_cast <int> (this->bindRect.y()),
                                static_cast <int> (this->bindRect.width()),
                                static_cast <int> (this->bindRect.height()),
                                this->pixmapList[this->tempSecond]);

            painter->drawPixmap(static_cast <int> (this->bindRect.x() + 20.0),
                                static_cast <int> (this->bindRect.y()),
                                static_cast <int> (this->bindRect.width()),
                                static_cast <int> (this->bindRect.height()),
                                this->pixmapList[this->tempThird]);

    }
}

void Gpa::loadFrame()
{
    this->clearAllFrame();
    this->addFrame(QPixmap(":/image/0.png"));
    this->addFrame(QPixmap(":/image/1.png"));
    this->addFrame(QPixmap(":/image/2.png"));
    this->addFrame(QPixmap(":/image/3.png"));
    this->addFrame(QPixmap(":/image/4.png"));
    this->addFrame(QPixmap(":/image/5.png"));
    this->addFrame(QPixmap(":/image/6.png"));
    this->addFrame(QPixmap(":/image/7.png"));
    this->addFrame(QPixmap(":/image/8.png"));
    this->addFrame(QPixmap(":/image/9.png"));
}

void Gpa::decreaseGpa(double num)
{
    this->gpa -= num;
    this->gpaChange->play();
}

void Gpa::increaseGpa(double num)
{
    this->gpaChange->play();
    if (getGpa() < 4.00 - num)
    {
        this->gpa += num;
    }
    else
    {
        this->gpa = 4.0;
    }
}

double Gpa::getGpa()
{
    return this->gpa;
}

