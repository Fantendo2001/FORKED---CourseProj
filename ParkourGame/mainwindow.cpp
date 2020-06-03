#include "mainwindow.h"
#include <iostream>
#include <ctime>

using namespace std;


/*
 * Function: MainWindow
 * Usage: usage MainWindow w;
 * --------------------------
 * Generate a main window.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /* control the running of the game */
    qsrand(QTime::currentTime().second());

    /* create a pixmap */
    this->bufferPixmap = new QPixmap(1440,800);
    this->resize(1440,800);


    /* button */

    // the start button
    this->startButton = new QPushButton(this);
    this->startButton->setGeometry(QRect(static_cast <int> ((560.0 / 1440) * this->width()),
                                             static_cast <int> ((480.0 / 800) * this->height()),
                                             static_cast <int> ((140.0 / 1440) * this->width()),
                                             static_cast <int> ((70.0 / 800)  * this->height())));
    this->startButton->setStyleSheet("QPushButton{border-image:url(:/image/"
                                     "button_play.png);}"
                                     "QPushButton:pressed{margin: 2px 2px 2px 2px;}");


    // connect start button to the choiceWindow function
    connect(this->startButton,SIGNAL(clicked()),this,SLOT(difficultyWindow()));


    // the close button
    this->closeButton = new QPushButton(this);
    this->closeButton->setGeometry(QRect(static_cast <int> ((760.0 / 1440) * this->width()),
                                         static_cast <int> ((480.0 / 800) * this->height()),
                                         static_cast <int> ((140.0 / 1440) * this->width()),
                                         static_cast <int> ((70.0 / 800) * this->height())));
    this->closeButton->setStyleSheet("QPushButton{border-image:url(:/image/button_close.png);}"
                                     "QPushButton:pressed{margin: 2px 2px 2px 2px;}");

    // connect close button to the closeGame function
    connect(this->closeButton,SIGNAL(clicked()),this,SLOT(closeGame()));


    // the help button
    this->helpButton = new QPushButton(this);
    this->helpButton->setGeometry(QRect(static_cast <int> ((960.0 / 1440) * this->width()),
                                        static_cast <int> ((470.0 / 800) * this->height()),
                                        static_cast <int> ((150.0 / 1440) * this->width()),
                                        static_cast <int> ((75.0 / 800) * this->height())));
    this->helpButton->setStyleSheet("QPushButton{border-image:url(:/image/help.png);}"
                                 "QPushButton:pressed{margin: 2px 2px 2px 2px;}");

     // connect help button to the choiceWindow function
    connect(this->helpButton,SIGNAL(clicked()),this,SLOT(help()));

    // the character button
    this->ruleButton = new QPushButton(this);
    this->ruleButton->setGeometry(QRect(static_cast <int> ((495.0 / 1440) * this->width()),
                                            static_cast <int> ((130.0 / 800) * this->height()),
                                            static_cast <int> ((450.0 / 1440) * this->width()),
                                            static_cast <int> ((130.0 / 800) * this->height())));
    this->ruleButton->setStyleSheet("QPushButton{border-image:url(:/image/rulesButton.png);}"
                                 "QPushButton:pressed{margin: 2px 2px 2px 2px;}");

    // connect charcter button to the charHelp function
    connect(this->ruleButton,SIGNAL(clicked()),this,SLOT(ruleHelp()));

    // the tool button
    this->itemButton = new QPushButton(this);
    this->itemButton->setGeometry(QRect(static_cast <int> ((510.0 / 1440) * this->width()),
                                        static_cast <int> ((330.0 / 800) * this->height()),
                                        static_cast <int> ((410.0 / 1440) * this->width()),
                                        static_cast <int> ((120.0 / 800) * this->height())));
    this->itemButton->setStyleSheet("QPushButton{border-image:url(:/image/items.png);}"
                                 "QPushButton:pressed{margin: 2px 2px 2px 2px;}");

    // connect tool button to the toolHelp function
    connect(this->itemButton,SIGNAL(clicked()),this,SLOT(toolHelp()));

    // the operation button
    this->operationButton = new QPushButton(this);
    this->operationButton->setGeometry(QRect(static_cast <int> ((500.0 / 1440) * this->width()),
                                            static_cast <int> ((500.0 / 800) * this->height()),
                                            static_cast <int> ((450.0 / 1440) * this->width()),
                                            static_cast <int> ((150.0 / 800) * this->height())));
    this->operationButton->setStyleSheet("QPushButton{border-image:url(:/image/operations.png);}"
                                 "QPushButton:pressed{margin: 2px 2px 2px 2px;}");

    // connect tool button to the operationHelp function
    connect(this->operationButton,SIGNAL(clicked()),this,SLOT(operationHelp()));

    // the return button
    this->returnButton = new QPushButton(this);
    this->returnButton->setGeometry(QRect(static_cast <int> ((1300.0 / 1440) * this->width()),
                                        static_cast <int> ((700.0 / 800) * this->height()),
                                        static_cast <int> ((150.0 / 1440) * this->width()),
                                        static_cast <int> ((100.0 / 800) * this->height())));
    this->returnButton->setStyleSheet("QPushButton{border-image:url(:/image/return.png);}"
                                 "QPushButton:pressed{margin: 2px 2px 2px 2px;}");

    // connect return button to the Return function
    connect(this->returnButton,SIGNAL(clicked()),this,SLOT(Return()));

    // the player1 button
    this->player1Button = new QPushButton(this);
    this->player1Button->setGeometry(QRect(static_cast <int> ((420.0 / 1440) * this->width()),
                                         static_cast <int> ((500.0 / 800) * this->height()),
                                         static_cast <int> ((200.0 / 1440) * this->width()),
                                         static_cast <int> ((140.0 / 800) * this->height())));
    this->player1Button->setStyleSheet("QPushButton{border-image:url(:/image/choose.png);}"
                                     "QPushButton:pressed{margin: 2px 2px 2px 2px;}");

    // connect player1 button to the choosePlayer1 function
    connect(this->player1Button,SIGNAL(clicked()),this,SLOT(choosePlayer1()));

    // the player2 button
    this->player2Button = new QPushButton(this);
    this->player2Button->setGeometry(QRect(static_cast <int> ((820.0 / 1440) * this->width()),
                                         static_cast <int> ((500.0 / 800) * this->height()),
                                         static_cast <int> ((200.0 / 1440) * this->width()),
                                         static_cast <int> ((140.0 / 800) * this->height())));
    this->player2Button->setStyleSheet("QPushButton{border-image:url(:/image/choose.png);}"
                                     "QPushButton:pressed{margin: 2px 2px 2px 2px;}");

    // connect player2 button to the choosePlayer2 function
    connect(this->player2Button,SIGNAL(clicked()),this,SLOT(choosePlayer2()));

    // the easy button
    this->easyButton = new QPushButton(this);
    this->easyButton->setGeometry(QRect(static_cast <int> ((520.0 / 1440) * this->width()),
                                            static_cast <int> ((190.0 / 800) * this->height()),
                                            static_cast <int> ((400.0 / 1440) * this->width()),
                                            static_cast <int> ((125.0 / 800) * this->height())));
    this->easyButton->setStyleSheet("QPushButton{border-image:url(:/image/easy.png);}"
                                 "QPushButton:pressed{margin: 2px 2px 2px 2px;}");

    // connect easy button to the easyGame function
    connect(this->easyButton,SIGNAL(clicked()),this,SLOT(easyGame()));

    // the medium button
    this->mediumButton = new QPushButton(this);
    this->mediumButton->setGeometry(QRect(static_cast <int> ((520.0 / 1440) * this->width()),
                                        static_cast <int> ((410.0 / 800) * this->height()),
                                        static_cast <int> ((400.0 / 1440) * this->width()),
                                        static_cast <int> ((125.0 / 800) * this->height())));
    this->mediumButton->setStyleSheet("QPushButton{border-image:url(:/image/medium.png);}"
                                 "QPushButton:pressed{margin: 2px 2px 2px 2px;}");

    // connect medium button to the mediumGame function
    connect(this->mediumButton,SIGNAL(clicked()),this,SLOT(mediumGame()));

    // the difficult button
    this->difficultButton = new QPushButton(this);
    this->difficultButton->setGeometry(QRect(static_cast <int> ((520.0 / 1440) * this->width()),
                                            static_cast <int> ((630.0 / 800) * this->height()),
                                            static_cast <int> ((400.0 / 1440) * this->width()),
                                            static_cast <int> ((125.0 / 800) * this->height())));
    this->difficultButton->setStyleSheet("QPushButton{border-image:url(:/image/difficult.png);}"
                                 "QPushButton:pressed{margin: 2px 2px 2px 2px;}");

    // connect difficult button to the difficultGame function
    connect(this->difficultButton,SIGNAL(clicked()),this,SLOT(difficultGame()));


    /* add game elements into this main window */
    this->gpa = new Gpa();
    this->cry = new Cry();
    this->dizzy = new Dizzy();
    this->schorch = new Schorch();
    this->allClear = new AllClear();
    this->midterm = new Midterm(0);
    this->scoreboard = new ScoreBoard();
    this->readyboard = new ReadyBoard();
    this->overboard = new OverBoard();
    this->excalibur = new Excalibur(0);
    this->shield = new Shield(0);
    this->revive = new Revive(0);
    this->background = new Background();
    this->gameBackground = new GameBackground();
    this->player = new Player();
    this->finalFire = new FinalFire();
    this->thunder = new Thunder();
    this->shieldEffect = new ShieldEffect();
    this->jumpFire = new JumpFire();
    this->reviveEffect = new ReviveEffect();
    this->choice[0] = new ChoosePlayer(0);
    this->choice[1] = new ChoosePlayer(1);
    this->helpRuleWindow = new HelpRuleWindow();
    this->helpItemsWindow = new HelpItemsWindow();
    this->difficulty = new ChooseDifficulty;
    this->helpOperaitonWindow = new HelpOperaionWindow();
     this->helpWindowBackground = new HelpWindowBackground();

    for (int i = 0; i < 13; i++)
    {
        this->soil[i] = new Soil(i);
    }

    for (int i = 0; i < 13; i++)
    {
        this->cloud[i] = new Cloud(i);
    }

    for (int i = 0; i < 10; i++)
    {
        this->coin[i] = new Coin(i);
    }

    /* impactPlayerRect represents the location of the player object */
    this->impactPlayerRect.setRect(0, 0, this->player->getBindRect().width(), this->player->getBindRect().height());

    /* impactSoilRect represents the location of the soil objects */
    for (int j = 0; j < 13; j++)
    {
        this->impactSoilRect[j].setRect(0, 0, this->soil[j]->getBindRect().width() - 90, this->soil[j]->getBindRect().height());
    }

    /* sound of this game */
    this->soundDie = new QSound(":/sounds/die.wav");
    this->soundHit = new QSound(":/sounds/hit.wav");
    this->soundPoint = new QSound(":/sounds/point.wav");
    this->soundSwooshing = new QSound(":/sounds/swooshing.wav");
    this->soundJump = new QSound(":/sounds/jump.wav");
    this->soundExcalibur = new QSound(":/sounds/hudun.wav");
    this->soundRevive = new QSound(":/sounds/revive.wav");
    this->soundQuiz = new QSound(":/sounds/quiz.wav");
    this->soundFinal = new QSound(":/sounds/final.wav");
    this->soundClear = new QSound(":/sounds/clear.wav");
    this->soundClick = new QSound(":/sounds/click.wav");
    this->soundDunpai = new QSound(":/sounds/dunpai.wav");

    /* set up the timer and the frequency */
    connect(&timer,SIGNAL(timeout()),this,SLOT(update()));
    timer.start(20);

    /*
     * connect this two function to make the Start Button and the Close Button
     * will be shown when the game ends.
     */
    connect(this->overboard, SIGNAL(buttonVisible(bool, bool, bool, bool, bool, bool, bool, bool, bool, bool, bool, bool)),
            this, SLOT(setButtonVisible(bool, bool, bool, bool, bool, bool, bool, bool, bool, bool, bool, bool)));

    // begin the game
    this->gameTitle();
}


/*
 * Function: ~MainWindow
 * Usage: implicitly
 * --------------------------
 * delete all the game elements in this main window.
 */
MainWindow::~MainWindow()
{
    delete this->startButton;
    delete this->helpButton;
    delete this->closeButton;
    delete this->returnButton;
    delete this->ruleButton;
    delete this->itemButton;
    delete this->easyButton;
    delete this->mediumButton;
    delete this->difficultButton;

    delete this->revive;
    delete this->shield;
    delete this->operationButton;
    delete this->player1Button;
    delete this->player2Button;
    delete this->gpa;
    delete this->finalFire;
    delete this->excalibur;
    delete this->background;
    delete this->difficulty;
    delete this->helpWindowBackground;
    delete this->helpItemsWindow;
    delete this->helpRuleWindow;
    delete this->helpOperaitonWindow;
    delete this->gameBackground;
    delete this->player;
    delete this->shieldEffect;
    delete this->jumpFire;
    delete this->thunder;
    delete this->reviveEffect;
    delete this->cry;
    delete this->dizzy;
    delete this->schorch;
    delete this->allClear;
    delete this->scoreboard;
    delete this->readyboard;
    delete this->overboard;
    delete this->choice[0];
    delete this->choice[1];

    for (int i = 0; i < 13; i++)
    {
        delete this->soil[i];
    }

    for (int i = 0; i < 13; i++)
    {
        delete this->cloud[i];
    }

    for (int i = 0; i < 10; i++)
    {
        delete this->coin[i];
    }
}


/*
 * Function: mousePressEvent
 * Usage: implicitly
 * --------------------------
 * Detect the input of the mouse.
 */
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    /* press the left button to start the game */
    if( this->status == GAMEREADY && event->button() == Qt::LeftButton )
    {
        this->gamePlay();
    }
}

/*
 * Function: keyPressEvent
 * Usage: implicitly
 * --------------------------
 * Detect the input of the keyboard.
 */
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    /* press W to jump */
    if( this->status == GAMEPLAY && event->key() == Qt::Key_W && this->player->getState() != DOWN)
    {

        if(this->player->getJumpTime() < 2){
            if (this->player->getJumpTime() == 1)
            {
                this->jumpFire->setDisplay(true);
            }
            this->soundJump->play();
        }
        this->player->jump();
    }

    /* press S to go down the cloud if the player is on the cloud */
    if(this->status == GAMEPLAY && event->key() == Qt::Key_S && this->impactPlayerRect.bottom() < 580)
    {
        if(this->player->getBindRect().bottom() >= 420 && this->player->getBindRect().bottom() <= 430)
        {
            this->player->getBindRect().moveBottom(440);
            this->player->setSpeedY(5);
        }
    }

    /* press S to change the state of the player into down if the player is on the ground */
   if(this->status == GAMEPLAY && event->key() == Qt::Key_S &&
      this->impactPlayerRect.bottom() > 580 && this->player->getState() != DOWN)
   {
       this->player->setState(DOWN);
       impactPlayerRect.setRect(200, 600, 120, 80);
       this->player->playerDown();
       QTimer::singleShot(600, this, SLOT(playerDown()));
   }
}


/*
 * Function: paintEvent
 * Usage: implicitly
 * --------------------------
 * Control the painting of this main window.
 */
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this->bufferPixmap);

    /* Draw all the elements. */
    this->background->logic();
    this->background->draw(&painter);

    this->difficulty->logic();
    this->difficulty->draw(&painter);

    this->helpWindowBackground->logic();
    this->helpWindowBackground->draw(&painter);

    this->helpRuleWindow->logic();
    this->helpRuleWindow->draw(&painter);

    this->helpItemsWindow->logic();
    this->helpItemsWindow->draw(&painter);

    this->helpOperaitonWindow->logic();
    this->helpOperaitonWindow->draw(&painter);

    this->gameBackground->logic();
    this->gameBackground->draw(&painter);

    /* ensure that there are no more than three sequential soils are vanished*/
    for (int i = 0; i < 13; i++)
        {
            this->soil[i]->logic();
            if (i == 0){
                this->soil[i]->setPreviousShow(this->soil[11
                        ]->getShow());
            }
            else if(i == 1)
            {
                this->soil[i]->setPreviousShow(this->soil[12]->getShow());
            }
            else
            {
                this->soil[i]->setPreviousShow(this->soil[i-2]->getShow());
            }
            this->soil[i]->draw(&painter);
        }

    /* ensure that there are at least two sequential clouds */
    for (int i = 0; i < 13; i++)
        {
            this->cloud[i]->logic();
            if (i == 0)
            {
                this->cloud[i]->setPreviousShow1(this->cloud[11]->isShow());
            }
            else if(i == 1)
            {
                this->cloud[i]->setPreviousShow1(this->cloud[12]->isShow());
            }
            else
            {
                this->cloud[i]->setPreviousShow1(this->cloud[i-2]->isShow());
            }
            if (i == 0)
            {
                this->cloud[i]->setPreviousShow2(this->cloud[12]->isShow());
            }
            else
            {
                this->cloud[i]->setPreviousShow2(this->cloud[i-1]->isShow());
            }
            this->cloud[i]->draw(&painter);
        }

    for (int i = 0; i < 10; i++)
    {
        this->coin[i]->logic();
         this->coin[i]->draw(&painter);
    }

    this->midterm->logic();
    this->midterm->draw(&painter);

    this->choice[0]->logic();
    this->choice[0]->draw(&painter);

    this->choice[1]->logic();
    this->choice[1]->draw(&painter);

    // cloud
    this->player->setIsCloud(false);
    for(int i = 0; i < 13; i ++){
        if (this->cloud[i]->isOverPlayer()){
            this->player->setIsCloud(true);
        }
    }

    this->finalFire->logic();
    this->finalFire->draw(&painter);

    this->thunder->logic();
    this->thunder->draw(&painter);

    this->gpa->logic();
    this->gpa->draw(&painter);

    this->player->logic();
    this->player->draw(&painter);

    this->shieldEffect->setPositionY(this->player->getBindRect().bottom());
    this->shieldEffect->setDisplay(this->player->hasShield);
    this->shieldEffect->logic();
    this->shieldEffect->draw(&painter);

    this->jumpFire->setPositionY(this->player->getBindRect().bottom());
    this->jumpFire->logic();
    this->jumpFire->draw(&painter);

    this->reviveEffect->setPositionY(this->player->getBindRect().bottom());
    this->reviveEffect->logic();
    this->reviveEffect->draw(&painter);

    this->cry->setPositionY(this->player->getBindRect().bottom());
    this->cry->logic();
    this->cry->draw(&painter);

    this->schorch->setPositionY(this->player->getBindRect().bottom());
    this->schorch->logic();
    this->schorch->draw(&painter);

    this->dizzy->setPositionY(this->player->getBindRect().bottom());
    this->dizzy->logic();
    this->dizzy->draw(&painter);

    this->allClear->logic();
    this->allClear->draw(&painter);

    this->excalibur->logic();
    this->excalibur->draw(&painter);

    this->revive->logic();
    this->revive->draw(&painter);

    this->shield->logic();
    this->shield->draw(&painter);

    this->scoreboard->logic();
    this->scoreboard->draw(&painter);

    this->readyboard->logic();
    this->readyboard->draw(&painter);

    this->overboard->logic();
    this->overboard->draw(&painter);

    QPainter mainWindowPainter(this);
    mainWindowPainter.drawPixmap(QRect(0, 0, this->width(), this->height()), *this->bufferPixmap);


    /* control the intersection between objects */
    if(this->status == GAMEPLAY)
    {
        /* update the location of player */
        this->impactPlayerRect.moveCenter(this->player->getBindRect().center());

        /* update the location of soil */
        for (int j = 0; j < 13; j++)
        {
            this->impactSoilRect[j].setRect(this->soil[j]->getRect().left() + 45,
                                            this->soil[j]->getRect().y(),
                                            this->soil[j]->getRect().width() - 90,
                                            this->soil[j]->getRect().height());
        }

        /* check the intersection between midterm and the player */
        if(this->impactPlayerRect.intersects(this->midterm->getRect()))
        {
            this->midterm->hit();
            if (this->player->hasShield == 0)
            {
                this->soundHit->play();
                this->decreaseGpa(0.4);            // decrease the gpa
            }
            else
            {
                this->soundDunpai->play();
            }
        }

        /* check the intersection between finalfire and the player */
        if(this->impactPlayerRect.intersects(this->finalFire->getRect()))
        {
            if (this->player->hasShield == 0)
            {
                this->soundFinal->play();
                this->finalFire->hitFire();
                this->player->getShield();
                this->decreaseGpa(0.5);
            }
            else
            {
                this->soundDunpai->play();
            }
        }

        /* check the intersection between thunder and the player */
        if(this->impactPlayerRect.intersects(this->thunder->getRect()))
        {
            if (this->player->hasShield == 0)
            {
                this->soundQuiz->play();
                this->thunder->hitThunder();
                this->player->getShield();
                this->decreaseGpa(0.3);
            }
            else
            {
                this->soundDunpai->play();
            }
        }


        /* check the intersection between excalibur and the player */
        if(this->impactPlayerRect.intersects(this->excalibur->getRect()))
        {
            this->allClear->setDisplay(true);
            this->soundClear->play();
            this->excalibur->hit();
            this->midterm->hit();
            this->finalFire->hit();
            this->thunder->hit();
        }

        /* check the intersection between revive and the player */
        if(this->impactPlayerRect.intersects(this->revive->getRect()))
        {
            this->soundRevive->play();
            this->revive->hit();
            this->gpa->increaseGpa(0.2);
            this->reviveEffect->setDisplay(true);
        }

        /* check the intersection between shield and the player */
        if(this->impactPlayerRect.intersects(this->shield->getRect()))
        {
            this->player->getShield();
            this->shield->hit();
        }


        /* check the intersection between coins and the player */
        for (int i = 0; i < 10; i++)
        {
            if(this->impactPlayerRect.intersects(this->coin[i]->getRect()))
            {
                this->getScore();
                this->coin[i]->hit();
            }
        }


        /* check the intersection between soils and the player */
        if ((this->player->getState() == 0 || this->player->getState() == 2) && this->impactPlayerRect.bottom() > 680)
        {
            if( (this->impactPlayerRect.intersects(this->impactSoilRect[0]) && (!this->soil[0]->getShow())) ||
                (this->impactPlayerRect.intersects(this->impactSoilRect[1]) && (!this->soil[1]->getShow())) ||
                (this->impactPlayerRect.intersects(this->impactSoilRect[2]) && (!this->soil[2]->getShow())) ||
                (this->impactPlayerRect.intersects(this->impactSoilRect[3]) && (!this->soil[3]->getShow())) ||
                (this->impactPlayerRect.intersects(this->impactSoilRect[4]) && (!this->soil[4]->getShow())) ||
                (this->impactPlayerRect.intersects(this->impactSoilRect[5]) && (!this->soil[5]->getShow())) ||
                (this->impactPlayerRect.intersects(this->impactSoilRect[6]) && (!this->soil[6]->getShow())) ||
                (this->impactPlayerRect.intersects(this->impactSoilRect[7]) && (!this->soil[7]->getShow())) ||
                (this->impactPlayerRect.intersects(this->impactSoilRect[8]) && (!this->soil[8]->getShow())) ||
                (this->impactPlayerRect.intersects(this->impactSoilRect[9]) && (!this->soil[9]->getShow())) ||
                (this->impactPlayerRect.intersects(this->impactSoilRect[10]) && (!this->soil[10]->getShow())) ||
                (this->impactPlayerRect.intersects(this->impactSoilRect[11]) && (!this->soil[11]->getShow())) ||
                (this->impactPlayerRect.intersects(this->impactSoilRect[12]) && (!this->soil[12]->getShow())))
               {
                    this->player->fallDown();       // let player fall down
               }
        }

        /* check if the game goes to terminaton */
        if (this->player->getState() == FALLDOWN || this->gpa->getGpa() <= 0.0)
        {
            this->gameOver();
        }


    }
}

/*
 * Function: resizeEvent
 * Usage: implicitly
 * --------------------------
 * Resize the buttons.
 */
void MainWindow::resizeEvent(QResizeEvent *)
{
    this->startButton->setGeometry(QRect(static_cast <int> ((560.0 / 1440) * this->width()),
                                             static_cast <int> ((480.0 / 800) * this->height()),
                                             static_cast <int> ((140.0 / 1440) * this->width()),
                                             static_cast <int> ((70.0 / 800)  * this->height())));

    this->closeButton->setGeometry(QRect(static_cast <int> ((760.0 / 1440) * this->width()),
                                         static_cast <int> ((480.0 / 800) * this->height()),
                                         static_cast <int> ((140.0 / 1440) * this->width()),
                                         static_cast <int> ((70.0 / 800) * this->height())));

    this->helpButton->setGeometry(QRect(static_cast <int> ((960.0 / 1440) * this->width()),
                                        static_cast <int> ((470.0 / 800) * this->height()),
                                        static_cast <int> ((150.0 / 1440) * this->width()),
                                        static_cast <int> ((75.0 / 800) * this->height())));

    this->ruleButton->setGeometry(QRect(static_cast <int> ((495.0 / 1440) * this->width()),
                                            static_cast <int> ((130.0 / 800) * this->height()),
                                            static_cast <int> ((450.0 / 1440) * this->width()),
                                            static_cast <int> ((130.0 / 800) * this->height())));

    this->itemButton->setGeometry(QRect(static_cast <int> ((510.0 / 1440) * this->width()),
                                        static_cast <int> ((330.0 / 800) * this->height()),
                                        static_cast <int> ((410.0 / 1440) * this->width()),
                                        static_cast <int> ((120.0 / 800) * this->height())));

    this->operationButton->setGeometry(QRect(static_cast <int> ((500.0 / 1440) * this->width()),
                                            static_cast <int> ((500.0 / 800) * this->height()),
                                            static_cast <int> ((450.0 / 1440) * this->width()),
                                            static_cast <int> ((150.0 / 800) * this->height())));

    this->returnButton->setGeometry(QRect(static_cast <int> ((1300.0 / 1440) * this->width()),
                                        static_cast <int> ((700.0 / 800) * this->height()),
                                        static_cast <int> ((150.0 / 1440) * this->width()),
                                        static_cast <int> ((100.0 / 800) * this->height())));

    this->player1Button->setGeometry(QRect(static_cast <int> ((420.0 / 1440) * this->width()),
                                         static_cast <int> ((500.0 / 800) * this->height()),
                                         static_cast <int> ((200.0 / 1440) * this->width()),
                                         static_cast <int> ((140.0 / 800) * this->height())));

    this->player2Button->setGeometry(QRect(static_cast <int> ((820.0 / 1440) * this->width()),
                                         static_cast <int> ((500.0 / 800) * this->height()),
                                         static_cast <int> ((200.0 / 1440) * this->width()),
                                         static_cast <int> ((140.0 / 800) * this->height())));

    this->easyButton->setGeometry(QRect(static_cast <int> ((520.0 / 1440) * this->width()),
                                            static_cast <int> ((190.0 / 800) * this->height()),
                                            static_cast <int> ((400.0 / 1440) * this->width()),
                                            static_cast <int> ((125.0 / 800) * this->height())));

    this->mediumButton->setGeometry(QRect(static_cast <int> ((520.0 / 1440) * this->width()),
                                        static_cast <int> ((410.0 / 800) * this->height()),
                                        static_cast <int> ((400.0 / 1440) * this->width()),
                                        static_cast <int> ((125.0 / 800) * this->height())));

    this->difficultButton->setGeometry(QRect(static_cast <int> ((520.0 / 1440) * this->width()),
                                            static_cast <int> ((630.0 / 800) * this->height()),
                                            static_cast <int> ((400.0 / 1440) * this->width()),
                                            static_cast <int> ((125.0 / 800) * this->height())));
}

/*
 * Function: gameTitle
 * Usage: gameTitle()
 * --------------------------
 * Control the logic and painting of the objects when the state is gameTitle.
 */
void MainWindow::gameTitle()
{
    this->background->enabledLogic = true;
    this->background->enabledDraw = true;

    this->helpWindowBackground->enabledLogic = false;
    this->helpWindowBackground->enabledDraw = false;

    this->difficulty->enabledLogic = false;
    this->difficulty->enabledDraw =false;

    this->helpRuleWindow->enabledLogic = false;
    this->helpRuleWindow->enabledDraw = false;

    this->helpItemsWindow->enabledLogic = false;
    this->helpItemsWindow->enabledDraw = false;

    this->helpOperaitonWindow->enabledLogic = false;
    this->helpOperaitonWindow->enabledDraw = false;

    this->excalibur->enabledLogic = false;
    this->excalibur->enabledDraw = false;

    this->revive->enabledLogic = false;
    this->revive->enabledDraw = false;

    this->shield->enabledLogic = false;
    this->shield->enabledDraw = false;

    this->choice[0]->enabledLogic = false;
    this->choice[0]->enabledDraw = false;

    this->choice[1]->enabledLogic = false;
    this->choice[1]->enabledDraw = false;

    this->player->enabledLogic = false;
    this->player->enabledDraw = false;

    this->shieldEffect->enabledLogic = false;
    this->shieldEffect->enabledDraw = false;

    this->jumpFire->enabledLogic = false;
    this->jumpFire->enabledDraw = false;

    this->reviveEffect->enabledLogic = false;
    this->reviveEffect->enabledDraw = false;

    this->cry->enabledLogic = false;
    this->cry->enabledDraw = false;

    this->dizzy->enabledLogic = false;
    this->dizzy->enabledDraw = false;

    this->schorch->enabledLogic = false;
    this->schorch->enabledDraw = false;

    this->allClear->enabledLogic = false;
    this->allClear->enabledDraw = false;

    this->finalFire->enabledLogic = false;
    this->finalFire->enabledDraw = false;

    this->thunder->enabledLogic = false;
    this->thunder->enabledDraw = false;

    for (int i = 0; i < 13; i++)
    {
        this->soil[i]->enabledLogic = false;
        this->soil[i]->enabledDraw = false;
    }

    for (int i = 0; i < 13; i++)
    {
        this->cloud[i]->enabledLogic = false;
        this->cloud[i]->enabledDraw = false;
    }

    for (int i = 0; i < 10; i++)
    {
        this->coin[i]->enabledLogic = false;
        this->coin[i]->enabledDraw = false;
    }

    this->midterm->enabledLogic = false;
    this->midterm->enabledDraw = false;

    this->gameBackground->enabledLogic = false;
    this->gameBackground->enabledDraw = false;

    this->overboard->enabledLogic = false;
    this->overboard->enabledDraw = false;

    this->readyboard->enabledLogic = false;
    this->readyboard->enabledDraw = false;

    this->scoreboard->enabledLogic = false;
    this->scoreboard->enabledDraw = false;

    this->gpa->enabledLogic = false;
    this->gpa->enabledDraw = false;

    this->setButtonVisible(true, true, true, false, false, false, false, false, false, false, false, false);  // button

    this->status = GAMETITLE;   // game state
}

/*
 * Function: helpWindow
 * Usage: helpWindow()
 * --------------------------
 * Control the logic and painting of the objects when the state is helpWindow.
 */
void MainWindow::helpWindow()
{

    this->background->enabledLogic = false;
    this->background->enabledDraw = false;

    this->helpWindowBackground->enabledLogic = true;
    this->helpWindowBackground->enabledDraw = true;

    this->difficulty->enabledLogic = false;
    this->difficulty->enabledDraw =false;

    this->helpRuleWindow->enabledLogic = false;
    this->helpRuleWindow->enabledDraw = false;

    this->helpItemsWindow->enabledLogic = false;
    this->helpItemsWindow->enabledDraw = false;

    this->helpOperaitonWindow->enabledLogic = false;
    this->helpOperaitonWindow->enabledDraw = false;

    for (int i = 0; i < 13; i++)
    {
        this->soil[i]->enabledLogic = false;
        this->soil[i]->enabledDraw = false;
    }

    for (int i = 0; i < 13; i++)
    {
        this->cloud[i]->enabledLogic = false;
        this->cloud[i]->enabledDraw = false;
    }

    for (int i = 0; i < 10; i++)
    {
        this->coin[i]->enabledLogic = false;
        this->coin[i]->enabledDraw = false;
    }

    this->midterm->enabledLogic = false;
    this->midterm->enabledDraw = false;

    this->finalFire->enabledLogic = false;
    this->finalFire->enabledDraw = false;

    this->thunder->enabledLogic = false;
    this->thunder->enabledDraw = false;

    this->player->enabledLogic = false;
    this->player->enabledDraw = false;

    this->shieldEffect->enabledLogic = false;
    this->shieldEffect->enabledDraw = false;

    this->jumpFire->enabledLogic = false;
    this->jumpFire->enabledDraw = false;

    this->reviveEffect->enabledLogic = false;
    this->reviveEffect->enabledDraw = false;

    this->cry->enabledLogic = false;
    this->cry->enabledDraw = false;

    this->dizzy->enabledLogic = false;
    this->dizzy->enabledDraw = false;

    this->schorch->enabledLogic = false;
    this->schorch->enabledDraw = false;

    this->allClear->enabledLogic = false;
    this->allClear->enabledDraw = false;

    this->shield->enabledLogic = false;
    this->shield->enabledDraw = false;

    this->excalibur->enabledLogic = false;
    this->excalibur->enabledDraw = false;

    this->revive->enabledLogic = false;
    this->revive->enabledDraw = false;

    this->choice[0]->enabledLogic = false;
    this->choice[0]->enabledDraw = false;

    this->choice[1]->enabledLogic = false;
    this->choice[1]->enabledDraw = false;

    this->gameBackground->enabledLogic = false;
    this->gameBackground->enabledDraw = false;

    this->overboard->enabledLogic = false;
    this->overboard->enabledDraw = false;

    this->readyboard->enabledLogic = false;
    this->readyboard->enabledDraw = false;

    this->gpa->enabledLogic = false;
    this->gpa->enabledDraw = false;

    this->scoreboard->enabledLogic = false;
    this->scoreboard->enabledDraw = false;

    this->setButtonVisible(false, false, false, true, true, true, true, false, false, false, false, false);  // buttons

    this->status = HELPSTATE;               // game state
}


/*
 * Function: helpChar
 * Usage: helpChar()
 * --------------------------
 * Control the logic and painting of the objects when the state is helpChar.
 */
void MainWindow::helpRule()
{
    this->background->enabledLogic = false;
    this->background->enabledDraw = false;

    this->helpWindowBackground->enabledLogic = false;
    this->helpWindowBackground->enabledDraw = false;

    this->difficulty->enabledLogic = false;
    this->difficulty->enabledDraw =false;

    this->helpRuleWindow->enabledLogic = true;
    this->helpRuleWindow->enabledDraw = true;

    this->helpOperaitonWindow->enabledLogic = false;
    this->helpOperaitonWindow->enabledDraw = false;

    this->helpItemsWindow->enabledLogic = false;
    this->helpItemsWindow->enabledDraw = false;

    for (int i = 0; i < 13; i++)
    {
        this->soil[i]->enabledLogic = false;
        this->soil[i]->enabledDraw = false;
    }

    for (int i = 0; i < 13; i++)
    {
        this->cloud[i]->enabledLogic = false;
        this->cloud[i]->enabledDraw = false;
    }

    for (int i = 0; i < 10; i++)
    {
        this->coin[i]->enabledLogic = false;
        this->coin[i]->enabledDraw = false;
    }

    this->midterm->enabledLogic = false;
    this->midterm->enabledDraw = false;

    this->thunder->enabledLogic = false;
    this->thunder->enabledDraw = false;

    this->finalFire->enabledLogic = false;
    this->finalFire->enabledDraw = false;

    this->player->enabledLogic = false;
    this->player->enabledDraw = false;

    this->shieldEffect->enabledLogic = false;
    this->shieldEffect->enabledDraw = false;

    this->jumpFire->enabledLogic = false;
    this->jumpFire->enabledDraw = false;

    this->reviveEffect->enabledLogic = false;
    this->reviveEffect->enabledDraw = false;

    this->cry->enabledLogic = false;
    this->cry->enabledDraw = false;

    this->dizzy->enabledLogic = false;
    this->dizzy->enabledDraw = false;

    this->schorch->enabledLogic = false;
    this->schorch->enabledDraw = false;

    this->allClear->enabledLogic = false;
    this->allClear->enabledDraw = false;

    this->choice[0]->enabledLogic = false;
    this->choice[0]->enabledDraw = false;

    this->choice[1]->enabledLogic = false;
    this->choice[1]->enabledDraw = false;

    this->gameBackground->enabledLogic = false;
    this->gameBackground->enabledDraw = false;

    this->excalibur->enabledLogic = false;
    this->excalibur->enabledDraw = false;

    this->shield->enabledLogic = false;
    this->shield->enabledDraw = false;

    this->revive->enabledLogic = false;
    this->revive->enabledDraw = false;

    this->overboard->enabledLogic = false;
    this->overboard->enabledDraw = false;

    this->readyboard->enabledLogic = false;
    this->readyboard->enabledDraw = false;

    this->gpa->enabledLogic = false;
    this->gpa->enabledDraw = false;

    this->scoreboard->enabledLogic = false;
    this->scoreboard->enabledDraw = false;

    this->setButtonVisible(false, false, false, true, false, false, false, false, false, false, false, false); // button

    this->status = HELPRULE;        // game state
}

/*
 * Function: helpTool
 * Usage: helpTool()
 * --------------------------
 * Control the logic and painting of the objects when the state is helpTool.
 */
void MainWindow::helpTool()
{
    this->background->enabledLogic = false;
    this->background->enabledDraw = false;

    this->helpWindowBackground->enabledLogic = false;
    this->helpWindowBackground->enabledDraw = false;

    this->difficulty->enabledLogic = false;
    this->difficulty->enabledDraw =false;

    this->helpRuleWindow->enabledLogic = false;
    this->helpRuleWindow->enabledDraw = false;

    this->helpItemsWindow->enabledLogic = true;
    this->helpItemsWindow->enabledDraw = true;

    this->helpOperaitonWindow->enabledLogic = false;
    this->helpOperaitonWindow->enabledDraw = false;

    for (int i = 0; i < 13; i++)
    {
        this->soil[i]->enabledLogic = false;
        this->soil[i]->enabledDraw = false;
    }

    for (int i = 0; i < 13; i++)
    {
        this->cloud[i]->enabledLogic = false;
        this->cloud[i]->enabledDraw = false;
    }

    for (int i = 0; i < 10; i++)
    {
        this->coin[i]->enabledLogic = false;
        this->coin[i]->enabledDraw = false;
    }

    this->midterm->enabledLogic = false;
    this->midterm->enabledDraw = false;

    this->thunder->enabledLogic = false;
    this->thunder->enabledDraw = false;

    this->finalFire->enabledLogic = false;
    this->finalFire->enabledDraw = false;

    this->player->enabledLogic = false;
    this->player->enabledDraw = false;

    this->shieldEffect->enabledLogic = false;
    this->shieldEffect->enabledDraw = false;

    this->jumpFire->enabledLogic = false;
    this->jumpFire->enabledDraw = false;

    this->reviveEffect->enabledLogic = false;
    this->reviveEffect->enabledDraw = false;

    this->cry->enabledLogic = false;
    this->cry->enabledDraw = false;

    this->dizzy->enabledLogic = false;
    this->dizzy->enabledDraw = false;

    this->schorch->enabledLogic = false;
    this->schorch->enabledDraw = false;

    this->allClear->enabledLogic = false;
    this->allClear->enabledDraw = false;

    this->excalibur->enabledLogic = false;
    this->excalibur->enabledDraw = false;

    this->revive->enabledLogic = false;
    this->revive->enabledDraw = false;

    this->shield->enabledLogic = false;
    this->shield->enabledDraw = false;

    this->choice[0]->enabledLogic = false;
    this->choice[0]->enabledDraw = false;

    this->choice[1]->enabledLogic = false;
    this->choice[1]->enabledDraw = false;

    this->gameBackground->enabledLogic = false;
    this->gameBackground->enabledDraw = false;

    this->overboard->enabledLogic = false;
    this->overboard->enabledDraw = false;

    this->readyboard->enabledLogic = false;
    this->readyboard->enabledDraw = false;

    this->gpa->enabledLogic = false;
    this->gpa->enabledDraw = false;

    this->scoreboard->enabledLogic = false;
    this->scoreboard->enabledDraw = false;

    this->setButtonVisible(false, false, false, true, false, false, false, false, false, false, false, false);   // button

    this->status = HELPTOOL;        // game state
}

/*
 * Function: helpOperation
 * Usage: helpOperation()
 * --------------------------
 * Control the logic and painting of the objects when the state is helpOperation.
 */
void MainWindow::helpOperation()
{
    this->background->enabledLogic = false;
    this->background->enabledDraw = false;

    this->helpWindowBackground->enabledLogic = false;
    this->helpWindowBackground->enabledDraw = false;

    this->difficulty->enabledLogic = false;
    this->difficulty->enabledDraw =false;

    this->helpRuleWindow->enabledLogic = false;
    this->helpRuleWindow->enabledDraw = false;

    this->helpItemsWindow->enabledLogic = false;
    this->helpItemsWindow->enabledDraw = false;

    this->excalibur->enabledLogic = false;
    this->excalibur->enabledDraw = false;

    this->finalFire->enabledLogic = false;
    this->finalFire->enabledDraw = false;

    this->thunder->enabledLogic = false;
    this->thunder->enabledDraw = false;

    this->shield->enabledLogic = false;
    this->shield->enabledDraw = false;

    this->revive->enabledLogic = false;
    this->revive->enabledDraw = false;

    this->helpOperaitonWindow->enabledLogic = true;
    this->helpOperaitonWindow->enabledDraw = true;

    for (int i = 0; i < 13; i++)
    {
        this->soil[i]->enabledLogic = false;
        this->soil[i]->enabledDraw = false;
    }

    for (int i = 0; i < 13; i++)
    {
        this->cloud[i]->enabledLogic = false;
        this->cloud[i]->enabledDraw = false;
    }

    for (int i = 0; i < 10; i++)
    {
        this->coin[i]->enabledLogic = false;
        this->coin[i]->enabledDraw = false;
    }

    this->midterm->enabledLogic = false;
    this->midterm->enabledDraw = false;

    this->player->enabledLogic = false;
    this->player->enabledDraw = false;

    this->shieldEffect->enabledLogic = false;
    this->shieldEffect->enabledDraw = false;

    this->jumpFire->enabledLogic = false;
    this->jumpFire->enabledDraw = false;

    this->reviveEffect->enabledLogic = false;
    this->reviveEffect->enabledDraw = false;

    this->cry->enabledLogic = false;
    this->cry->enabledDraw = false;

    this->dizzy->enabledLogic = false;
    this->dizzy->enabledDraw = false;

    this->schorch->enabledLogic = false;
    this->schorch->enabledDraw = false;

    this->allClear->enabledLogic = false;
    this->allClear->enabledDraw = false;

    this->choice[0]->enabledLogic = false;
    this->choice[0]->enabledDraw = false;

    this->choice[1]->enabledLogic = false;
    this->choice[1]->enabledDraw = false;

    this->finalFire->enabledLogic = false;
    this->finalFire->enabledDraw = false;

    this->gameBackground->enabledLogic = false;
    this->gameBackground->enabledDraw = false;

    this->overboard->enabledLogic = false;
    this->overboard->enabledDraw = false;

    this->readyboard->enabledLogic = false;
    this->readyboard->enabledDraw = false;

    this->gpa->enabledLogic = false;
    this->gpa->enabledDraw = false;

    this->scoreboard->enabledLogic = false;
    this->scoreboard->enabledDraw = false;

    this->setButtonVisible(false, false, false, true, false, false, false, false, false, false, false, false);      // button

    this->status = HELPOPERATION;           // game state
}


/*
 * Function: chooseDifficulty
 * Usage: chooseDifficulty()
 * --------------------------
 * Control the logic and painting of the objects when the state is chooseDifficulty.
 */
void MainWindow::chooseDifficulty()
{

    this->background->enabledLogic = true;
    this->background->enabledDraw = true;

    this->helpWindowBackground->enabledLogic = false;
    this->helpWindowBackground->enabledDraw = false;

    this->difficulty->enabledLogic = true;
    this->difficulty->enabledDraw = true;

    this->helpItemsWindow->enabledLogic = false;
    this->helpItemsWindow->enabledDraw = false;

    this->helpRuleWindow->enabledLogic = false;
    this->helpRuleWindow->enabledDraw = false;

    this->finalFire->enabledLogic = false;
    this->finalFire->enabledDraw = false;

    this->thunder->enabledLogic = false;
    this->thunder->enabledDraw = false;

    this->excalibur->enabledLogic = false;
    this->excalibur->enabledDraw = false;

    this->helpOperaitonWindow->enabledLogic = false;
    this->helpOperaitonWindow->enabledDraw = false;


    for (int i = 0; i < 13; i++)
    {
        this->soil[i]->enabledLogic = false;
        this->soil[i]->enabledDraw = false;
    }

    for (int i = 0; i < 13; i++)
    {
        this->cloud[i]->enabledLogic = false;
        this->cloud[i]->enabledDraw = false;
    }

    for (int i = 0; i < 10; i++)
    {
        this->coin[i]->enabledLogic = false;
        this->coin[i]->enabledDraw = false;
    }

    this->midterm->enabledLogic = false;
    this->midterm->enabledDraw = false;

    this->player->enabledLogic = false;
    this->player->enabledDraw = false;

    this->shieldEffect->enabledLogic = false;
    this->shieldEffect->enabledDraw = false;

    this->jumpFire->enabledLogic = false;
    this->jumpFire->enabledDraw = false;

    this->reviveEffect->enabledLogic = false;
    this->reviveEffect->enabledDraw = false;

    this->finalFire->enabledLogic = false;
    this->finalFire->enabledDraw = false;

    this->cry->enabledLogic = false;
    this->cry->enabledDraw = false;

    this->dizzy->enabledLogic = false;
    this->dizzy->enabledDraw = false;

    this->schorch->enabledLogic = false;
    this->schorch->enabledDraw = false;

    this->allClear->enabledLogic = false;
    this->allClear->enabledDraw = false;

    this->choice[0]->enabledLogic = false;
    this->choice[0]->enabledDraw = false;

    this->choice[1]->enabledLogic = false;
    this->choice[1]->enabledDraw = false;

    this->gameBackground->enabledLogic = false;
    this->gameBackground->enabledDraw = false;

    this->revive->enabledLogic = false;
    this->revive->enabledDraw = false;

    this->shield->enabledLogic = false;
    this->shield->enabledDraw = false;

    this->overboard->enabledLogic = false;
    this->overboard->enabledDraw = false;

    this->readyboard->enabledLogic = false;
    this->readyboard->enabledDraw = false;

    this->gpa->enabledLogic = false;
    this->gpa->enabledDraw = false;

    this->scoreboard->enabledLogic = false;
    this->scoreboard->enabledDraw = false;

    this->setButtonVisible(false, false, false, true, false, false, false, false, false, true, true, true);    // button

    this->status = CHOOSEDIFFICULTY;        // game state
}


/*
 * Function: choosePlayer
 * Usage: choosePlayer()
 * --------------------------
 * Control the logic and painting of the objects when the state is choosePlayer.
 */
void MainWindow::choosePlayer()
{

    this->background->enabledLogic = false;
    this->background->enabledDraw = false;

    this->helpWindowBackground->enabledLogic = false;
    this->helpWindowBackground->enabledDraw = false;

    this->difficulty->enabledLogic = true;
    this->difficulty->enabledDraw = true;

    this->helpItemsWindow->enabledLogic = false;
    this->helpItemsWindow->enabledDraw = false;

    this->helpRuleWindow->enabledLogic = false;
    this->helpRuleWindow->enabledDraw = false;

    this->excalibur->enabledLogic = false;
    this->excalibur->enabledDraw = false;

    this->thunder->enabledLogic = false;
    this->thunder->enabledDraw = false;

    this->helpOperaitonWindow->enabledLogic = false;
    this->helpOperaitonWindow->enabledDraw = false;

    for (int i = 0; i < 13; i++)
    {
        this->soil[i]->enabledLogic = false;
        this->soil[i]->enabledDraw = false;
    }

    for (int i = 0; i < 13; i++)
    {
        this->cloud[i]->enabledLogic = false;
        this->cloud[i]->enabledDraw = false;
    }

    for (int i = 0; i < 10; i++)
    {
        this->coin[i]->enabledLogic = false;
        this->coin[i]->enabledDraw = false;
    }

    this->midterm->enabledLogic = false;
    this->midterm->enabledDraw = false;

    this->player->enabledLogic = false;
    this->player->enabledDraw = false;

    this->finalFire->enabledLogic = false;
    this->finalFire->enabledDraw = false;

    this->shieldEffect->enabledLogic = false;
    this->shieldEffect->enabledDraw = false;

    this->jumpFire->enabledLogic = false;
    this->jumpFire->enabledDraw = false;

    this->reviveEffect->enabledLogic = false;
    this->reviveEffect->enabledDraw = false;

    this->cry->enabledLogic = false;
    this->cry->enabledDraw = false;

    this->dizzy->enabledLogic = false;
    this->dizzy->enabledDraw = false;

    this->schorch->enabledLogic = false;
    this->schorch->enabledDraw = false;

    this->allClear->enabledLogic = false;
    this->allClear->enabledDraw = false;

    this->choice[0]->enabledLogic = true;
    this->choice[0]->enabledDraw = true;

    this->choice[1]->enabledLogic = true;
    this->choice[1]->enabledDraw = true;

    this->gameBackground->enabledLogic = false;
    this->gameBackground->enabledDraw = false;

    this->revive->enabledLogic = false;
    this->revive->enabledDraw = false;

    this->shield->enabledLogic = false;
    this->shield->enabledDraw = false;

    this->overboard->enabledLogic = false;
    this->overboard->enabledDraw = false;

    this->readyboard->enabledLogic = false;
    this->readyboard->enabledDraw = false;

    this->gpa->enabledLogic = false;
    this->gpa->enabledDraw = false;

    this->scoreboard->enabledLogic = false;
    this->scoreboard->enabledDraw = false;

    this->setButtonVisible(false, false, false, true, false, false, false, true, true, false, false, false);    // button

    this->status = CHOOSEPLAYER;        // game state
}

/*
 * Function: gameReady
 * Usage: gameReady()
 * --------------------------
 * Control the logic and painting of the objects when the state is gameReady.
 */
void MainWindow::gameReady()
{
    this->score = 0;

    this->background->enabledLogic = true;
    this->background->enabledDraw = true;

    this->helpWindowBackground->enabledLogic = false;
    this->helpWindowBackground->enabledDraw = false;

    this->difficulty->enabledLogic = false;
    this->difficulty->enabledDraw = false;

    this->helpRuleWindow->enabledLogic = false;
    this->helpRuleWindow->enabledDraw = false;

    this->excalibur->enabledLogic = false;
    this->excalibur->enabledDraw = false;

    this->finalFire->enabledLogic = false;
    this->finalFire->enabledDraw = false;

    this->revive->enabledLogic = false;
    this->revive->enabledDraw = false;

    this->shield->enabledLogic = false;
    this->shield->enabledDraw = false;

    this->thunder->enabledLogic = false;
    this->thunder->enabledDraw = false;

    this->helpItemsWindow->enabledLogic = false;
    this->helpItemsWindow->enabledDraw = false;

    this->helpOperaitonWindow->enabledLogic = false;
    this->helpOperaitonWindow->enabledDraw = false;

    for (int i = 0; i < 13; i++)
    {
        this->soil[i]->enabledLogic = true;
        this->soil[i]->enabledDraw = true;
        this->soil[i]->setProb(false);
    }

    for (int i = 0; i < 13; i++)
    {
        this->cloud[i]->enabledLogic = true;
        this->cloud[i]->enabledDraw = true;
    }

    for (int i = 0; i < 10; i++)
    {
        this->coin[i]->enabledLogic = false;
        this->coin[i]->enabledDraw = false;
    }

    this->midterm->enabledLogic = false;
    this->midterm->enabledDraw = false;

    this->player->enabledLogic = false;
    this->player->enabledDraw = true;
    this->player->setState(RUN);

    this->shieldEffect->enabledLogic = false;
    this->shieldEffect->enabledDraw = true;

    this->jumpFire->enabledLogic = false;
    this->jumpFire->enabledDraw = true;

    this->reviveEffect->enabledLogic = false;
    this->reviveEffect->enabledDraw = true;

    this->cry->enabledLogic = false;
    this->cry->enabledDraw = true;

    this->dizzy->enabledLogic = false;
    this->dizzy->enabledDraw = true;

    this->schorch->enabledLogic = false;
    this->schorch->enabledDraw = true;

    this->allClear->enabledLogic = false;
    this->allClear->enabledDraw = true;

    this->choice[0]->enabledLogic = false;
    this->choice[0]->enabledDraw = false;

    this->choice[1]->enabledLogic = false;
    this->choice[1]->enabledDraw = false;

    this->gameBackground->enabledLogic = true;
    this->gameBackground->enabledDraw = true;

    this->overboard->enabledLogic = false;
    this->overboard->enabledDraw = false;

    this->readyboard->enabledLogic = true;
    this->readyboard->enabledDraw = true;

    this->gpa->enabledLogic = true;
    this->gpa->enabledDraw = true;

    this->scoreboard->enabledLogic = true;
    this->scoreboard->enabledDraw = true;

    this->setButtonVisible(false, false, false, false, false, false, false, false, false, false, false, false);  // button

    this->status = GAMEREADY;       // game state
}

/*
 * Function: gamePlay
 * Usage: gamePlay()
 * --------------------------
 * Control the logic and painting of the objects when the state is gamePlay.
 */
void MainWindow::gamePlay()
{
    this->background->enabledLogic = true;
    this->background->enabledDraw = true;

    this->helpRuleWindow->enabledLogic = false;
    this->helpRuleWindow->enabledDraw = false;

    this->difficulty->enabledLogic = false;
    this->difficulty->enabledDraw = false;

    this->helpItemsWindow->enabledLogic = false;
    this->helpItemsWindow->enabledDraw = false;

    this->excalibur->enabledLogic = true;
    this->excalibur->enabledDraw = true;

    this->revive->enabledLogic = true;
    this->revive->enabledDraw = true;

    this->shield->enabledLogic = true;
    this->shield->enabledDraw = true;

    this->helpOperaitonWindow->enabledLogic = false;
    this->helpOperaitonWindow->enabledDraw = false;

    this->helpWindowBackground->enabledLogic = false;
    this->helpWindowBackground->enabledDraw = false;

    for (int i = 0; i < 13; i++)
    {
        this->soil[i]->enabledLogic = true;
        this->soil[i]->enabledDraw = true;
        this->soil[i]->setProb(true);
    }

    for (int i = 0; i < 13; i++)
    {
        this->cloud[i]->enabledLogic = true;
        this->cloud[i]->enabledDraw = true;
    }

    for (int i = 0; i < 10; i++)
    {
        this->coin[i]->enabledLogic = true;
        this->coin[i]->enabledDraw = true;
    }

    this->midterm->enabledLogic = true;
    this->midterm->enabledDraw = true;

    this->choice[0]->enabledLogic = false;
    this->choice[0]->enabledDraw = false;

    this->choice[1]->enabledLogic = false;
    this->choice[1]->enabledDraw = false;

    this->player->enabledLogic = true;
    this->player->enabledDraw = true;

    this->thunder->enabledLogic = true;
    this->thunder->enabledDraw = true;

    this->finalFire->enabledLogic = true;
    this->finalFire->enabledDraw = true;

    this->shieldEffect->enabledLogic = true;
    this->shieldEffect->enabledDraw = true;

    this->jumpFire->enabledLogic = true;
    this->jumpFire->enabledDraw = true;

    this->reviveEffect->enabledLogic = true;
    this->reviveEffect->enabledDraw = true;

    this->cry->enabledLogic = true;
    this->cry->enabledDraw = true;

    this->dizzy->enabledLogic = true;
    this->dizzy->enabledDraw = true;

    this->schorch->enabledLogic = true;
    this->schorch->enabledDraw = true;

    this->allClear->enabledLogic = true;
    this->allClear->enabledDraw = true;

    this->gameBackground->enabledLogic = true;
    this->gameBackground->enabledDraw = true;

    this->overboard->enabledLogic = false;
    this->overboard->enabledDraw = false;

    this->readyboard->enabledLogic = false;
    this->readyboard->enabledDraw = false;

    this->gpa->enabledLogic = true;
    this->gpa->enabledDraw = true;

    this->scoreboard->enabledLogic = true;
    this->scoreboard->enabledDraw = true;

    this->setButtonVisible(false, false, false, false, false, false, false, false, false, false, false, false);  // button

    this->status = GAMEPLAY;            // game state
}


/*
 * Function: gameOver
 * Usage: gameOver()
 * --------------------------
 * Control the logic and painting of the objects when the state is gameOver.
 */
void MainWindow::gameOver()
{
    this->background->enabledLogic = true;
    this->background->enabledDraw = true;

    this->helpWindowBackground->enabledLogic = false;
    this->helpWindowBackground->enabledDraw = false;

    this->difficulty->enabledLogic = false;
    this->difficulty->enabledDraw = false;

    this->helpRuleWindow->enabledLogic = false;
    this->helpRuleWindow->enabledDraw = false;

    this->helpItemsWindow->enabledLogic = false;
    this->helpItemsWindow->enabledDraw = false;

    this->excalibur->enabledLogic = false;
    this->excalibur->enabledDraw = false;

    this->revive->enabledLogic = false;
    this->revive->enabledDraw = false;

    this->helpOperaitonWindow->enabledLogic = false;
    this->helpOperaitonWindow->enabledDraw = false;

    for (int i = 0; i < 13; i++)
    {
        this->soil[i]->enabledLogic = false;
        this->soil[i]->enabledDraw = true;
    }

    for (int i = 0; i < 13; i++)
    {
        this->cloud[i]->enabledLogic = false;
        this->cloud[i]->enabledDraw = true;
    }

    for (int i = 0; i < 10; i++)
    {
        this->coin[i]->enabledLogic = false;
        this->coin[i]->enabledDraw = true;
    }

    this->choice[0]->enabledLogic = false;
    this->choice[0]->enabledDraw = false;

    this->finalFire->enabledLogic = false;
    this->finalFire->enabledDraw = false;

    this->thunder->enabledLogic = false;
    this->thunder->enabledDraw = false;

    this->choice[1]->enabledLogic = false;
    this->choice[1]->enabledDraw = false;

    this->player->enabledLogic = true;
    this->player->enabledDraw = true;

    this->shieldEffect->enabledLogic = true;
    this->shieldEffect->enabledDraw = true;

    this->jumpFire->enabledLogic = true;
    this->jumpFire->enabledDraw = true;

    this->reviveEffect->enabledLogic = true;
    this->reviveEffect->enabledDraw = true;

    this->cry->enabledLogic = true;
    this->cry->enabledDraw = true;

    this->dizzy->enabledLogic = true;
    this->dizzy->enabledDraw = true;

    this->schorch->enabledLogic = true;
    this->schorch->enabledDraw = true;

    this->allClear->enabledLogic = true;
    this->allClear->enabledDraw = true;

    this->shield->enabledLogic = false;
    this->shield->enabledDraw = false;

    this->midterm->enabledLogic = false;
    this->midterm->enabledDraw = false;

    this->gameBackground->enabledLogic = false;
    this->gameBackground->enabledDraw = true;

    this->overboard->setScore(this->score);
    this->overboard->enabledLogic = true;
    this->overboard->enabledDraw = true;

    this->readyboard->enabledLogic = false;
    this->readyboard->enabledDraw = false;

    this->gpa->enabledLogic = false;
    this->gpa->enabledDraw = false;

    this->scoreboard->enabledLogic = false;
    this->scoreboard->enabledDraw = false;

    this->setButtonVisible(false, false, false, false, false, false, false, false, false, false, false, false);  // button

    this->status = GAMEOVER;        // game state
}

/*
 * Function: difficultyWindow
 * Usage: difficultyWindow()
 * --------------------------
 * Initilize the objects when the user click the start Button.
 */
void MainWindow::difficultyWindow()
{
    this->soundClick->play();
    this->chooseDifficulty();
}


/*
 * Function: choiceWindow
 * Usage: choiceWindow()
 * --------------------------
 * Initilize the objects when the user click the Start Button.
 */
void MainWindow::choiceWindow()
{
    this->choice[0]->init();
    this->choice[1]->init();

    this->soundClick->play();
    this->choosePlayer();
}


/*
 * Function: choosePlayer1
 * Usage: choosePlayer1()
 * --------------------------
 * Initilize the objects when the user click the player1 Button.
 */
void MainWindow::choosePlayer1()
{
    // begin the game
    this->player->setNum(1);
    this->player->init();
    this->gameReady();

    this->soundClick->play();
}

/*
 * Function: choosePlayer2
 * Usage: choosePlayer2()
 * --------------------------
 * Initilize the objects when the users click the player2 Button.
 */
void MainWindow::choosePlayer2()
{
    // begin the game
    this->player->setNum(2);
    this->player->init();
    this->gameReady();

    this->soundClick->play();
}

/*
 * Function: closeGame
 * Usage: closeGame()
 * --------------------------
 * Excute the implementations when the users click the close Button.
 */
void MainWindow::closeGame()
{
    this->soundClick->play();
    this->close();
}

/*
 * Function: help
 * Usage: help()
 * --------------------------
 * Excute the implementations when the users click the help Button.
 */
void MainWindow::help()
{
    this->helpWindowBackground->init();
    this->soundClick->play();
    this->helpWindow();
}


/*
 * Function: charHelp
 * Usage: charHelp()
 * --------------------------
 * Excute the implementations when the users click the character Button.
 */
void MainWindow::ruleHelp()
{
    this->soundClick->play();
    this->helpRule();
}

/*
 * Function: toolHelp
 * Usage: toolHelp()
 * --------------------------
 * Excute the implementations when the users click the character Button.
 */
void MainWindow::toolHelp()
{
    this->soundClick->play();
    this->helpTool();
}

/*
 * Function: operationHelp
 * Usage: operationHelp()
 * --------------------------
 * Excute the implementations when the users click the character Button.
 */
void MainWindow::operationHelp()
{
    this->soundClick->play();
    this->helpOperation();
}

/*
 * Function: Return
 * Usage: Return()
 * --------------------------
 * Excute the implementations when the users click the Return Button.
 */
void MainWindow::Return()
{
    this->soundClick->play();

    if (this->status == HELPSTATE || this->status == CHOOSEDIFFICULTY)
    {
        this->gameTitle();
    }
    else if(this->status == HELPRULE || this->status == HELPTOOL || this->status == HELPOPERATION)
    {
        this->helpWindow();
    }
    else
    {
        this->chooseDifficulty();
    }
}

/*
 * Function: easyGame
 * Usage: easyGame()
 * --------------------------
 * Excute the implementations when the users click the easyGame Button.
 */
void MainWindow::easyGame()
{
    /* initialize the objects in the game*/
    this->background->init();
    this->gameBackground->init();
    this->shieldEffect->init();
    this->jumpFire->init();
    this->reviveEffect->init();
    this->cry->init();
    this->schorch->init();
    this->dizzy->init();
    this->allClear->init();
    this->midterm->init();
    this->thunder->init();
    this->scoreboard->init();
    this->readyboard->init();
    this->overboard->init();
    this->gpa->init();
    this->finalFire->init();
    this->excalibur->init();
    this->revive->init();
    this->shield->init();

    for (int i = 0; i < 10; i++)
    {
        this->coin[i]->init();
    }

    for (int i = 0; i < 13; i++)
    {
        this->soil[i]->init();
        this->soil[i]->setDifficulty("EASY");
    }

    for (int i = 0; i < 13; i++)
    {
        this->cloud[i]->init();
        this->cloud[i]->setDifficulty("EASY");
    }

    this->soundClick->play();
    this->choosePlayer();

    /* set difficuly */
    this->thunder->setDifficulty("EASY");
    this->finalFire->setDifficulty("EASY");
    this->midterm->setDifficulty("EASY");
    this->excalibur->setDifficulty("EASY");
    this->revive->setDifficulty("EASY");
    this->shield->setDifficulty("EASY");
}

/*
 * Function: mediumGame
 * Usage: mediumGame()
 * --------------------------
 * Excute the implementations when the users click the medium Button.
 */
void MainWindow::mediumGame()
{
    /* initialize the objects in the game*/
    this->background->init();
    this->gameBackground->init();
    this->shieldEffect->init();
    this->jumpFire->init();
    this->reviveEffect->init();
    this->cry->init();
    this->schorch->init();
    this->dizzy->init();
    this->allClear->init();
    this->midterm->init();
    this->finalFire->init();
    this->thunder->init();
    this->scoreboard->init();
    this->readyboard->init();
    this->overboard->init();
    this->gpa->init();
    this->excalibur->init();
    this->revive->init();
    this->shield->init();

    for (int i = 0; i < 10; i++)
    {
        this->coin[i]->init();
    }

    for (int i = 0; i < 13; i++)
    {
        this->soil[i]->init();
        this->soil[i]->setDifficulty("MEDIUM");
    }

    for (int i = 0; i < 13; i++)
    {
        this->cloud[i]->init();
        this->cloud[i]->setDifficulty("MEDIUM");
    }

    this->soundClick->play();
    this->choosePlayer();

    /* set difficuly */
    this->thunder->setDifficulty("MEDIUM");
    this->finalFire->setDifficulty("MEDIUM");
    this->midterm->setDifficulty("MEDIUM");
    this->excalibur->setDifficulty("MEDIUM");
    this->revive->setDifficulty("MEDIUM");
    this->shield->setDifficulty("MEDIUM");
}


/*
 * Function: difficultGame
 * Usage: difficultGame()
 * --------------------------
 * Excute the implementations when the users click the difficultGame Button.
 */
void MainWindow::difficultGame()
{
    /* initialize the objects in the game*/
    this->background->init();
    this->gameBackground->init();
    this->shieldEffect->init();
    this->jumpFire->init();
    this->reviveEffect->init();
    this->cry->init();
    this->schorch->init();
    this->dizzy->init();
    this->allClear->init();
    this->midterm->init();
    this->scoreboard->init();
    this->readyboard->init();
    this->thunder->init();
    this->finalFire->init();
    this->overboard->init();
    this->gpa->init();
    this->excalibur->init();
    this->revive->init();
    this->shield->init();

    for (int i = 0; i < 13; i++)
    {
        this->soil[i]->init();
        this->soil[i]->setDifficulty("DIFFICULT");
    }

    for (int i = 0; i < 13; i++)
    {
        this->cloud[i]->init();
        this->cloud[i]->setDifficulty("DIFFICULT");
    }

    for (int i = 0; i < 10; i++)
    {
        this->coin[i]->init();
    }

    this->soundClick->play();
    this->choosePlayer();

    /* set difficuly */
    this->thunder->setDifficulty("DIFFICULT");
    this->finalFire->setDifficulty("DIFFICULT");
    this->midterm->setDifficulty("DIFFICULT");
    this->excalibur->setDifficulty("DIFFICULT");
    this->revive->setDifficulty("DIFFICULT");
    this->shield->setDifficulty("DIFFICULT");
}

/*
 * Function: setButtonVisible
 * Usage: setButtonVisible()
 * --------------------------
 * Set the visibility of buttons.
 */
void MainWindow::setButtonVisible(bool _startBtn, bool _closeBtn, bool _infoBtn,
                                  bool _returnBtn, bool _ruleBtn, bool _itemBtn,
                                  bool _operBtn, bool _player1Btn, bool _player2Btn,
                                  bool _easyBtn, bool _mediumBtn, bool _difficultBtn)
{
    this->startButton->setVisible(_startBtn);
    this->closeButton->setVisible(_closeBtn);
    this->helpButton->setVisible(_infoBtn);
    this->returnButton->setVisible(_returnBtn);
    this->ruleButton->setVisible(_ruleBtn);
    this->itemButton->setVisible(_itemBtn);
    this->operationButton->setVisible(_operBtn);
    this->player1Button->setVisible(_player1Btn);
    this->player2Button->setVisible(_player2Btn);
    this->easyButton->setVisible(_easyBtn);
    this->mediumButton->setVisible(_mediumBtn);
    this->difficultButton->setVisible(_difficultBtn);
}


/*
 * Function: decreaseGpa
 * Usage: decreaseGpa()
 * --------------------------
 * decrease Gpa.
 */
void MainWindow::decreaseGpa(double num)
{
    this->gpa->decreaseGpa(num);
    if (num == 0.4)
    {
        this->cry->setDisplay(true);
    }else if(num == 0.5)
    {
        this->dizzy->setDisplay(true);
    }else
    {
        this->schorch->setDisplay(true);
    }

}

/*
 * Function: getScore
 * Usage: getScore()
 * --------------------------
 * increse the score.
 */
void MainWindow::getScore()
{
    this->score += 1;
    this->scoreboard->setScore(this->score);
    this->soundPoint->play();
}

/*
 * Function: playerDowm
 * Usage: playerDown()
 * --------------------------
 * change the state and the rectange of player when he is down.
 */
void MainWindow::playerDown()
{
    player->setState(RUN);
    impactPlayerRect.setRect(200, 560, 80, 120);
}
