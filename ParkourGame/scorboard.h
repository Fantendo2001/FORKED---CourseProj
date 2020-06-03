
#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "gameelement.h"

class ScoreBoard : public GameElement
{
    Q_OBJECT

public:
    explicit ScoreBoard(QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
    void setScore(int);

private:
    int score;
    int tempUnit;
    int tempDecade;
    int tempHundred;
    void loadFrame();

signals:

public slots:

};

#endif // SCOREBOARD_H
