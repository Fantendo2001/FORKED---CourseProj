
#include "overboard.h"

OverBoard::OverBoard(QObject *parent) :
    GameElement(parent)
{
    this->loadFrame();
    this->init();
}

void OverBoard::init()
{
    this->score = 0;
    this->highestScore = 0;
    this->medal = NONE;
    this->scoreLabelArrived = false;
    this->overTextRect.setRect(600, 120, 240.0, 55.0);
    this->scoreLabelRect.setRect(520.0, 300, 400.0, 200.0);
}

void OverBoard::logic()
{
    if(!this->enabledLogic)
        return;

    if(this->overTextRect.y() < 145.0)
        this->overTextRect.translate(0, 15.0);
    else
        this->overTextRect.setY(145.0);

    if(this->scoreLabelRect.y() > 204.0)
    {
        this->scoreLabelRect.translate(0,-20.0);
    }
    else
    {
        this->scoreLabelRect.setY(204.0);
        this->scoreLabelArrived = true;
    }
}

void OverBoard::draw(QPainter *painter)
{
    if(!this->enabledDraw)
        return;

    painter->drawPixmap(static_cast <int> (this->overTextRect.x()),
                            static_cast <int> (this->overTextRect.y()),
                            static_cast <int> (this->overTextRect.width()),
                            static_cast <int> (this->overTextRect.height()),
                            this->pixmapList[10]);

    painter->drawPixmap(static_cast <int> (this->scoreLabelRect.x()),
                        static_cast <int> (this->scoreLabelRect.y()),
                        static_cast <int> (this->scoreLabelRect.width()),
                        static_cast <int> (this->scoreLabelRect.height()),
                        this->pixmapList[11]);

    if( !this->scoreLabelArrived )
        return;

    if((this->score%1000)/100 != 0)
        {
            painter->drawPixmap(790.0, 260.0, 20.0, 25.0,
                                this->pixmapList[(this->score%1000)/100]);

            painter->drawPixmap(810.0, 260.0, 20.0, 25.0,
                                this->pixmapList[(this->score%100)/10]);
        }

        else if((this->score%100)/10 != 0)
        {
            painter->drawPixmap(810.0, 260.0, 20.0, 25.0,
                                this->pixmapList[(this->score%100)/10]);
        }

        painter->drawPixmap(830.0, 260.0, 20.0, 25.0,
                            this->pixmapList[this->score%10]);

        //best score

        if((this->highestScore%1000)/100 != 0)
        {
            painter->drawPixmap(790.0, 330.0, 20.0, 25.0,
                                this->pixmapList[(this->highestScore%1000)/100]);

            painter->drawPixmap(810.0, 330.0, 20.0, 25.0,
                                this->pixmapList[(this->highestScore%100)/10]);
        }
        else if((this->highestScore%100)/10 != 0)
        {
            painter->drawPixmap(810.0, 330.0, 20.0, 25.0,
                                this->pixmapList[(this->highestScore%100)/10]);
        }
        painter->drawPixmap(830.0, 330.0, 20.0, 25.0,
                            this->pixmapList[this->highestScore%10]);

    //Medal
    if(this->medal != NONE)
    {
        painter->drawPixmap(568.0,268.0,90.0,90.0,
                         this->pixmapList[this->medal]);
    }
    //Button
    emit this->buttonVisible(true, true, false, false, false, false, false, false, false, false, false, false);
}

void OverBoard::setScore(int _score)
{
    this->score = _score;
    this->highestScore = this->getHighestScore();
    switch(this->score / 50)
    {
    case    0:
        this->medal = COPPERMEDAL; break;
    case    1:
        this->medal = SILVERMEDAL;  break;
    default:
        this->medal = GOLDMEDAL;  break;
    }
}

int OverBoard::getHighestScore()
{
    int highestScore;
    if( !QFile::exists("./HighestScore.sc"))
    {
        QFile file;
        file.setFileName("./HighestScore.sc");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream txtStrm(&file);
        txtStrm << this->score <<endl;
        highestScore = this->score;
        file.close();
    }
    else
    {
        QFile file;
        file.setFileName("./HighestScore.sc");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream txtStrm(&file);
        txtStrm >> highestScore ;
        file.close();
        file.remove();

        file.open(QIODevice::WriteOnly | QIODevice::Text);
        if( this->score > highestScore)
        {
            txtStrm << this->score <<endl;
            highestScore = this->score;
        }
        else
        {
            txtStrm << highestScore << endl;
        }
        file.close();
    }
    return highestScore;
}

void OverBoard::loadFrame()
{
    this->clearAllFrame();

    this->addFrame(QPixmap(":/image/score_0.png"));
    this->addFrame(QPixmap(":/image/score_1.png"));
    this->addFrame(QPixmap(":/image/score_2.png"));
    this->addFrame(QPixmap(":/image/score_3.png"));
    this->addFrame(QPixmap(":/image/score_4.png"));
    this->addFrame(QPixmap(":/image/score_5.png"));
    this->addFrame(QPixmap(":/image/score_6.png"));
    this->addFrame(QPixmap(":/image/score_7.png"));
    this->addFrame(QPixmap(":/image/score_8.png"));
    this->addFrame(QPixmap(":/image/score_9.png"));

    this->addFrame(QPixmap(":/image/game_over.png"));
    this->addFrame(QPixmap(":/image/score.png"));

    this->addFrame(QPixmap(":/image/gold.png"));
    this->addFrame(QPixmap(":/image/silver.png"));
    this->addFrame(QPixmap(":/image/bronze.png"));
}
