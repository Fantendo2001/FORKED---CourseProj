#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QMouseEvent>
#include <QTimer>
#include <QTime>
#include <QPixmap>
#include <QSound>
#include <QKeyEvent>

#include "background.h"
#include "gamebackground.h"
#include "player.h"
#include "scorboard.h"
#include "readyboard.h"
#include "overboard.h"
#include "midterm.h"
#include "gpa.h"
#include "soil.h"
#include "cloud.h"
#include "chooseplayer.h"
#include "helpwindowbackground.h"
#include "helpRuleWindow.h"
#include "helpitemswindow.h"
#include "helpoperationwindow.h"
#include "excalibur.h"
#include "revive.h"
#include "shield.h"
#include "coin.h"
#include "shieldeffect.h"
#include "jumpfire.h"
#include "reviveeffect.h"
#include "cry.h"
#include "finalfire.h"
#include "thunder.h"
#include "allclear.h"
#include "dizzy.h"
#include "schorch.h"
#include "choosedifficulty.h"

enum GameStatus{GAMETITLE,
                HELPSTATE,
                HELPRULE,
                HELPTOOL,
                HELPOPERATION,
                CHOOSEDIFFICULTY,
                CHOOSEPLAYER,
                GAMEREADY,
                GAMEPLAY,
                GAMEOVER};




class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    /*
     * Function: MainWindow
     * Usage: usage MainWindow w;
     * --------------------------
     * Generate a main window.
     */
    MainWindow(QWidget *parent = 0);

    /*
     * Function: ~MainWindow
     * Usage: implicitly
     * --------------------------
     * delete all the game elements in this main window.
     */
    ~MainWindow();

    /*
     * Function: paintEvent
     * Usage: implicitly
     * --------------------------
     * Control the painting of this main window.
     */
    void paintEvent(QPaintEvent *);

    /*
     * Function: mousePressEvent
     * Usage: implicitly
     * --------------------------
     * Detect the input of the mouse.
     */
    void mousePressEvent(QMouseEvent *);

    /*
     * Function: keyPressEvent
     * Usage: implicitly
     * --------------------------
     * Detect the input of the keyboard.
     */
    void keyPressEvent(QKeyEvent *);

    /*
     * Function: resizeEvent
     * Usage: implicitly
     * --------------------------
     * Resize the buttons.
     */
    void resizeEvent(QResizeEvent *);

public slots:
    /*
     * Function: decreaseGpa
     * Usage: decreaseGpa()
     * --------------------------
     * decrease Gpa.
     */
    void decreaseGpa(double num);

    /*
     * Function: getScore
     * Usage: getScore()
     * --------------------------
     * increse the score.
     */
    void getScore();

    /*
     * Function: difficultyWindow
     * Usage: difficultyWindow()
     * --------------------------
     * Open the difficulty window.
     */
    void difficultyWindow();

    /*
     * Function: choiceWindow
     * Usage: choiceWindow()
     * --------------------------
     * Initilize the objects when the user click the Start Button.
     */
    void choiceWindow();

    /*
     * Function: Return
     * Usage: Return()
     * --------------------------
     * Excute the implementations when the users click the Return Button.
     */
    void Return();

    /*
     * Function: ruleHelp
     * Usage: ruleHelp()
     * --------------------------
     * Excute the implementations when the users click the rule Button.
     */
    void ruleHelp();

    /*
     * Function: toolHelp
     * Usage: toolHelp()
     * --------------------------
     * Excute the implementations when the users click the character Button.
     */
    void toolHelp();

    /*
     * Function: operationHelp
     * Usage: operationHelp()
     * --------------------------
     * Excute the implementations when the users click the character Button.
     */
    void operationHelp();

    /*
     * Function: choosePlayer1
     * Usage: choosePlayer1()
     * --------------------------
     * Initilize the objects when the user click the player1 Button.
     */
    void choosePlayer1();

    /*
     * Function: choosePlayer2
     * Usage: choosePlayer2()
     * --------------------------
     * Initilize the objects when the users click the player2 Button.
     */
    void choosePlayer2();

    /*
     * Function: easyGame
     * Usage: easyGame()
     * --------------------------
     * Excute the implementations when the users click the easyGame Button.
     */
    void easyGame();

    /*
     * Function: mediumGame
     * Usage: mediumGame()
     * --------------------------
     * Excute the implementations when the users click the medium Button.
     */
    void mediumGame();

    /*
     * Function: difficultGame
     * Usage: difficultGame()
     * --------------------------
     * Excute the implementations when the users click the difficultGame Button.
     */
    void difficultGame();

    /*
     * Function: closeGame
     * Usage: closeGame()
     * --------------------------
     * Excute the implementations when the users click the close Button.
     */
    void closeGame();

    /*
     * Function: help
     * Usage: help()
     * --------------------------
     * Excute the implementations when the users click the help Button.
     */
    void help();

    /*
     * Function: playerDowm
     * Usage: playerDown()
     * --------------------------
     * change the state and the rectange of player when he is down.
     */
    void playerDown();

    /*
     * Function: setButtonVisible
     * Usage: setButtonVisible()
     * --------------------------
     * Set the visibility of buttons.
     */
    void setButtonVisible(bool, bool, bool, bool, bool, bool, bool, bool, bool, bool, bool, bool);

private:
    QPixmap *bufferPixmap;

    /* Buttons on the start panel. */
    QPushButton *startButton;
    QPushButton *closeButton;
    QPushButton *helpButton;
    QPushButton *ruleButton;
    QPushButton *itemButton;
    QPushButton *operationButton;
    QPushButton *returnButton;
    QPushButton *player1Button;
    QPushButton *player2Button;
    QPushButton *easyButton;
    QPushButton *mediumButton;
    QPushButton *difficultButton;


    /* Elements need to draw */
    Gpa *gpa;
    Cry *cry;
    Dizzy *dizzy;
    Schorch *schorch;
    Player *player;
    Midterm *midterm;
    Soil *soil[13];
    Cloud *cloud[13];
    Coin *coin[10];
    Revive *revive;
    Shield *shield;
    Thunder *thunder;
    AllClear *allClear;
    JumpFire *jumpFire;
    FinalFire *finalFire;
    Excalibur *excalibur;
    Background *background;
    ScoreBoard *scoreboard;
    ReadyBoard *readyboard;
    OverBoard *overboard;
    ChoosePlayer *choice[2];
    ShieldEffect *shieldEffect;
    ReviveEffect *reviveEffect;
    ChooseDifficulty *difficulty;
    GameBackground *gameBackground;
    HelpRuleWindow *helpRuleWindow;
    HelpItemsWindow *helpItemsWindow;
    HelpOperaionWindow *helpOperaitonWindow;
    HelpWindowBackground *helpWindowBackground;


    /* Sound */
    QSound *soundDunpai;
    QSound *soundDie;
    QSound *soundHit;
    QSound *soundPoint;
    QSound *soundSwooshing;
    QSound *soundJump;
    QSound *soundExcalibur;
    QSound *soundRevive;
    QSound *soundQuiz;
    QSound *soundFinal;
    QSound *soundClear;
    QSound *soundClick;

    int score;  // Game score
    QRectF impactPlayerRect;
    QRectF impactSoilRect[13];
    GameStatus status;
    QTimer timer;

    /*
     * Function: gameTitle
     * Usage: gameTitle()
     * --------------------------
     * Control the logic and painting of the objects when the state is gameTitle.
     */
    void gameTitle();

    /*
     * Function: gameReady
     * Usage: gameReady()
     * --------------------------
     * Control the logic and painting of the objects when the state is gameReady.
     */
    void gameReady();

    /*
     * Function: chooseDifficulty
     * Usage: chooseDifficulty()
     * --------------------------
     * Control the logic and painting of the objects when the state is chooseDifficulty.
     */
    void chooseDifficulty();

    /*
     * Function: helpWindow
     * Usage: helpWindow()
     * --------------------------
     * Control the logic and painting of the objects when the state is helpWindow.
     */
    void helpWindow();

    /*
     * Function: helpRule
     * Usage: helpRule()
     * --------------------------
     * Control the logic and painting of the objects when the state is helpRule.
     */
    void helpRule();

    /*
     * Function: helpTool
     * Usage: helpTool()
     * --------------------------
     * Control the logic and painting of the objects when the state is helpTool.
     */
    void helpTool();

    /*
     * Function: helpOperation
     * Usage: helpOperation()
     * --------------------------
     * Control the logic and painting of the objects when the state is helpOperation.
     */
    void helpOperation();

    /*
     * Function: gamePlay
     * Usage: gamePlay()
     * --------------------------
     * Control the logic and painting of the objects when the state is gamePlay.
     */
    void gamePlay();

    /*
     * Function: gameOver
     * Usage: gameOver()
     * --------------------------
     * Control the logic and painting of the objects when the state is gameOver.
     */
    void gameOver();

    /*
     * Function: choosePlayer1
     * Usage: choosePlayer1()
     * --------------------------
     * Initilize the objects when the user click the player1 Button.
     */
    void choosePlayer();

};

#endif // MAINWINDOW_H
