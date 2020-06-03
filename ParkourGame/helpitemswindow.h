#ifndef HELPITEMSWINDOW_H
#define HELPITEMSWINDOW_H

#include <QTimer>
#include "gameelement.h"

class HelpItemsWindow : public GameElement
{
    Q_OBJECT

public:
    explicit HelpItemsWindow(QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();

signals:

public slots:
    void updateFrame();

private:
    int currentFrame;
    int lastFrame;
    int angle;
    void loadFrame();
    QTimer timer;
};

#endif // HELPITEMSWINDOW_H
