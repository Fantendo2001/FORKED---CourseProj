#ifndef GPA_H
#define GPA_H

#include "gameelement.h"
#include <QSound>

class Gpa : public GameElement
{
    Q_OBJECT

public:
    explicit Gpa(QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
    void decreaseGpa(double num);
    void increaseGpa(double num);
    double getGpa();

private:
    QSound *gpaChange;
    double gpa;
    int tempFirst;
    int tempSecond;
    int tempThird;
    void loadFrame();

};

#endif // GPA_H
