#ifndef OVERBOARD_H
#define OVERBOARD_H

#include <QTimer>
#include <QFile>
#include <QTextStream>
#include "gameelement.h"

enum Medal{GOLDMEDAL = 12,
           SILVERMEDAL = 13,
           COPPERMEDAL = 14,
          NONE = 0};

class OverBoard : public GameElement
{
    Q_OBJECT

public:
    explicit OverBoard(QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
    void setScore(int);

signals:
    void buttonVisible(bool, bool, bool, bool, bool, bool, bool, bool, bool, bool, bool, bool);
public slots:

private:
    int score;
    int highestScore;
    bool scoreLabelArrived;
    QRectF scoreLabelRect;
    QRectF overTextRect;
    Medal medal;
    void loadFrame();
    int getHighestScore();
};

#endif // OVERBOARD_H
