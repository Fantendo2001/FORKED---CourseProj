#ifndef CHOOSEDIFFICULTY_H
#define CHOOSEDIFFICULTY_H
#include"gameelement.h"

class ChooseDifficulty : public GameElement
{
    Q_OBJECT

public:
    explicit ChooseDifficulty(QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();

private:
    void loadFrame();
    int controlSignal;
};




#endif // CHOOSEDIFFICULTY_H
