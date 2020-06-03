#include "scorboard.h"

ScoreBoard::ScoreBoard(QObject *parent) :
    GameElement(parent)
{
    this->loadFrame();
    this->init();
}

void ScoreBoard::init()
{
    this->bindRect.setRect(700.0, 80.0, 60.0, 80.0);
    this->score = 0;

    this->tempUnit = 0;
    this->tempDecade = 0;
    this->tempHundred = 0;
}

void ScoreBoard::logic()
{
    if(!this->enabledLogic)
    {
        return;
    }
    else
    {
        this->tempUnit = this->score%10;
        this->tempDecade = (this->score%100)/10;
        this->tempHundred = (this->score%1000)/100;
    }
}

void ScoreBoard::draw(QPainter *painter)
{
    if(!this->enabledDraw)
    {
        return;
    }
    else
    {
        if(this->tempDecade == 0 && this->tempHundred == 0)
        {
            painter->drawPixmap(static_cast <int> (this->bindRect.x()),
                                static_cast <int> (this->bindRect.y()),
                                static_cast <int> (this->bindRect.width()),
                                static_cast <int> (this->bindRect.height()),
                                this->pixmapList[this->tempUnit]);
        }
        else if(this->tempHundred == 0)
        {
            painter->drawPixmap(static_cast <int> (this->bindRect.x()-20.0),
                                static_cast <int> (this->bindRect.y()),
                                static_cast <int> (this->bindRect.width()),
                                static_cast <int> (this->bindRect.height()),
                                this->pixmapList[this->tempDecade]);

            painter->drawPixmap(static_cast <int> (this->bindRect.x()+20.0),
                                static_cast <int> (this->bindRect.y()),
                                static_cast <int> (this->bindRect.width()),
                                static_cast <int> (this->bindRect.height()),
                                this->pixmapList[this->tempUnit]);
        }
        else
        {
            painter->drawPixmap(static_cast <int> (this->bindRect.x()-40.0),
                                static_cast <int> (this->bindRect.y()),
                                static_cast <int> (this->bindRect.width()),
                                static_cast <int> (this->bindRect.height()),
                                this->pixmapList[this->tempHundred]);

            painter->drawPixmap(static_cast <int> (this->bindRect.x()),
                                static_cast <int> (this->bindRect.y()),
                                static_cast <int> (this->bindRect.width()),
                                static_cast <int> (this->bindRect.height()),
                                this->pixmapList[this->tempDecade]);

            painter->drawPixmap(static_cast <int> (this->bindRect.x()+40.0),
                                static_cast <int> (this->bindRect.y()),
                                static_cast <int> (this->bindRect.width()),
                                static_cast <int> (this->bindRect.height()),
                                this->pixmapList[this->tempUnit]);
        }
    }
}

void ScoreBoard::loadFrame()
{
    this->clearAllFrame();
    this->addFrame(QPixmap(":/image/font_0.png"));
    this->addFrame(QPixmap(":/image/font_1.png"));
    this->addFrame(QPixmap(":/image/font_2.png"));
    this->addFrame(QPixmap(":/image/font_3.png"));
    this->addFrame(QPixmap(":/image/font_4.png"));
    this->addFrame(QPixmap(":/image/font_5.png"));
    this->addFrame(QPixmap(":/image/font_6.png"));
    this->addFrame(QPixmap(":/image/font_7.png"));
    this->addFrame(QPixmap(":/image/font_8.png"));
    this->addFrame(QPixmap(":/image/font_9.png"));
}

void ScoreBoard::setScore(int _score)
{
    this->score = _score;
}
