#ifndef CHOOSEPLAYER_H
#define CHOOSEPLAYER_H

#include <QTimer>
#include"gameelement.h"

class ChoosePlayer : public GameElement
{
    Q_OBJECT

public:
    explicit ChoosePlayer(int num, QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();

signals:
public slots:
    void updateFrame();

private:
    QTimer timer;
    int lastFrame;
    int currentFrame;
    int num;
    void loadFrame();
};


#endif // CHOOSEPLAYER_H
