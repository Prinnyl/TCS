#include "gamewidget.h"
#include <QKeyEvent>
#include <QDateTime>
#include <QtDebug>
#include <QMessageBox>


GameWidget::GameWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(800, 450);
    qDebug() << this->width();
    //随机数种子
    qsrand(uint(QTime(0, 0, 0).secsTo(QTime::currentTime())));

    //游戏开始
    gameStart();
    foodStrart();

    //移动
    timerGame = new QTimer(this);
    connect(timerGame, &QTimer::timeout, [=](){
        //移动
        snakeMove();
        isKey = true;
    });
    timerGame->start(300);

    //动作
    timerAction = new QTimer(this);
    connect(timerAction, &QTimer::timeout, [=](){
        //动作
        snakeAction();
    });
    timerAction->start(75);

}

void GameWidget::paintEvent(QPaintEvent *)
{
    //背景
    QPainter groundPainter(this);
    groundPainter.fillRect(0, 0,this->width(), this->height(), QBrush(QColor(0, 0, 255, 100)));

    //动次打次
    QString snakeUp = QString(":/new/image/headup%1.png").arg(this->minUp++);
    QString snakeDown = QString(":/new/image/headdown%1.png").arg(this->minDown++);
    QString snakeLeft = QString(":/new/image/headleft%1.png").arg(this->minLeft++);
    QString snakeRight = QString(":/new/image/headright%1.png").arg(this->minRight++);
    //蛇头
    gamePainter = new QPainter(this);
    if(mapSnake[0].snakeState == 1)
    {
        gamePainter->drawPixmap(mapSnake[0].snakeX, mapSnake[0].snakeY, 25, 25, QPixmap(snakeUp));
    }
    if(mapSnake[0].snakeState == 2)
    {
        gamePainter->drawPixmap(mapSnake[0].snakeX, mapSnake[0].snakeY, 25, 25, QPixmap(snakeDown));
    }
    if(mapSnake[0].snakeState == 3)
    {
        gamePainter->drawPixmap(mapSnake[0].snakeX, mapSnake[0].snakeY, 25, 25, QPixmap(snakeLeft));
    }
    if(mapSnake[0].snakeState == 4)
    {
        gamePainter->drawPixmap(mapSnake[0].snakeX, mapSnake[0].snakeY, 25, 25, QPixmap(snakeRight));
    }
    if(mapSnake[0].snakeState == 5)
    {
        gamePainter->drawPixmap(mapSnake[0].snakeX, mapSnake[0].snakeY, 25, 25, QPixmap(":/new/image/headupleft.png"));
    }
    if(mapSnake[0].snakeState == 6)
    {
        gamePainter->drawPixmap(mapSnake[0].snakeX, mapSnake[0].snakeY, 25, 25, QPixmap(":/new/image/headupright.png"));
    }
    if(mapSnake[0].snakeState == 7)
    {
        gamePainter->drawPixmap(mapSnake[0].snakeX, mapSnake[0].snakeY, 25, 25, QPixmap(":/new/image/headleftup.png"));
    }
    if(mapSnake[0].snakeState == 8)
    {
        gamePainter->drawPixmap(mapSnake[0].snakeX, mapSnake[0].snakeY, 25, 25, QPixmap(":/new/image/headrightup.png"));
    }
    if(mapSnake[0].snakeState == 9)
    {
        gamePainter->drawPixmap(mapSnake[0].snakeX, mapSnake[0].snakeY, 25, 25, QPixmap(":/new/image/headleftdown.png"));
    }
    if(mapSnake[0].snakeState == 10)
    {
        gamePainter->drawPixmap(mapSnake[0].snakeX, mapSnake[0].snakeY, 25, 25, QPixmap(":/new/image/headrightdown.png"));
    }
    if(mapSnake[0].snakeState == 11)
    {
        gamePainter->drawPixmap(mapSnake[0].snakeX, mapSnake[0].snakeY, 25, 25, QPixmap(":/new/image/headdownleft.png"));
    }
    if(mapSnake[0].snakeState == 12)
    {
        gamePainter->drawPixmap(mapSnake[0].snakeX, mapSnake[0].snakeY, 25, 25, QPixmap(":/new/image/headdownright.png"));
    }
    //蛇身
    for (int i = 1; i < bodyLen; i++)
    {
        if(mapSnake[i].snakeState == 1 || mapSnake[i].snakeState == 2)
        {
            gamePainter->drawPixmap(mapSnake[i].snakeX, mapSnake[i].snakeY, 25, 25, QPixmap(":/new/image/bodyup.png"));
        }
        if(mapSnake[i].snakeState == 3 || mapSnake[i].snakeState == 4)
        {
            gamePainter->drawPixmap(mapSnake[i].snakeX, mapSnake[i].snakeY, 25, 25, QPixmap(":/new/image/bodyleft.png"));
        }
        if(mapSnake[i].snakeState == 5 || mapSnake[i].snakeState == 10)
        {
            gamePainter->drawPixmap(mapSnake[i].snakeX, mapSnake[i].snakeY, 25, 25, QPixmap(":/new/image/upleft.png"));
        }
        if(mapSnake[i].snakeState == 6 || mapSnake[i].snakeState == 9)
        {
            gamePainter->drawPixmap(mapSnake[i].snakeX, mapSnake[i].snakeY, 25, 25, QPixmap(":/new/image/upright.png"));
        }
        if(mapSnake[i].snakeState == 7 || mapSnake[i].snakeState == 12)
        {
            gamePainter->drawPixmap(mapSnake[i].snakeX, mapSnake[i].snakeY, 25, 25, QPixmap(":/new/image/downright.png"));
        }
        if(mapSnake[i].snakeState == 8 || mapSnake[i].snakeState == 11)
        {
            gamePainter->drawPixmap(mapSnake[i].snakeX, mapSnake[i].snakeY, 25, 25, QPixmap(":/new/image/downleft.png"));
        }
    }
    //食物
    gamePainter->drawPixmap(foodX, foodY, 25, 25, QPixmap(":/new/image/food.png"));

    delete gamePainter;
}

void GameWidget::keyPressEvent(QKeyEvent *event)
{
    //1上  2下  3左  4右
    //1上，2下，3左，4右，5上左，6上右，7左上，8右上，9左下，10右下，11下左，12下右
    preDirection = direction;
    switch (event->key())
    {
    case Qt::Key_W:
    case Qt::Key_Up:
        if(isKey == false || preDirection == 2)
        {
            return;
        }
        if(preDirection == 3)
        {
            mapSnake[0].snakeState = 7;
        }
        if(preDirection == 4)
        {
            mapSnake[0].snakeState = 8;
        }
        direction = 1;
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
        if(isKey == false || preDirection == 1)
        {
            return;
        }
        if(preDirection == 3)
        {
            mapSnake[0].snakeState = 9;
        }
        if(preDirection == 4)
        {
            mapSnake[0].snakeState = 10;
        }
        direction = 2;
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
        if(isKey == false || preDirection == 4)
        {
            return;
        }
        if(preDirection == 1)
        {
            mapSnake[0].snakeState = 5;
        }
        if(preDirection == 2)
        {
            mapSnake[0].snakeState = 11;
        }
        direction = 3;
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        if(isKey == false || preDirection == 3)
        {
            return;
        }
        if(preDirection == 1)
        {
            mapSnake[0].snakeState = 6;
        }
        if(preDirection == 2)
        {
            mapSnake[0].snakeState = 12;
        }
        direction = 4;
        break;
    default:
        return;
    }
    isKey = false;
    update();
}

void GameWidget::snakeMove()
{

    for (int i = bodyLen - 1; i > 0; i--)
    {
        mapSnake[i].snakeX = mapSnake[i - 1].snakeX;
        mapSnake[i].snakeY = mapSnake[i - 1].snakeY;
        mapSnake[i].snakeState = mapSnake[i - 1].snakeState;
    }

    if(mapSnake[0].snakeState == 5 || mapSnake[0].snakeState == 11)
    {
        mapSnake[0].snakeState = 3;
    }
    if(mapSnake[0].snakeState == 6 || mapSnake[0].snakeState == 12)
    {
        mapSnake[0].snakeState = 4;
    }
    if(mapSnake[0].snakeState == 7 || mapSnake[0].snakeState == 8)
    {
        mapSnake[0].snakeState = 1;
    }
    if(mapSnake[0].snakeState == 9 || mapSnake[0].snakeState == 10)
    {
        mapSnake[0].snakeState = 2;
    }

    if(direction == 1)
    {
        mapSnake[0].snakeY = mapSnake[0].snakeY - 25;
    }
    else if(direction == 2)
    {
        mapSnake[0].snakeY = mapSnake[0].snakeY + 25;
    }
    else if(direction == 3)
    {
        mapSnake[0].snakeX = mapSnake[0].snakeX - 25;
    }
    else if(direction == 4)
    {
        mapSnake[0].snakeX = mapSnake[0].snakeX + 25;
    }

    //穿墙
    if(mapSnake[0].snakeX < 0)
    {
        mapSnake[0].snakeX = this->width() - 25;
        //qDebug() << this->width();
    }
    else if(mapSnake[0].snakeX == this->width())
    {
        mapSnake[0].snakeX = 0;
    }
    else if(mapSnake[0].snakeY < 0)
    {
        mapSnake[0].snakeY = this->height() -25;
    }
    if(mapSnake[0].snakeY == this->height())
    {
        mapSnake[0].snakeY = 0;
    }

    //吃的判定
    if(mapSnake[0].snakeX == foodX && mapSnake[0].snakeY == foodY)
    {
        foodStrart();
        struct Snake add;
        add.snakeX = mapSnake[bodyLen - 1].snakeX;
        add.snakeY = mapSnake[bodyLen - 1].snakeY;
        add.snakeState = mapSnake[bodyLen - 1].snakeState;
        mapSnake.insert(bodyLen,add);
        bodyLen++;
    }


    //死亡判定
    for(int i = 1; i < bodyLen; i++)
    {
        if(mapSnake[0].snakeX == mapSnake[i].snakeX && mapSnake[0].snakeY == mapSnake[i].snakeY)
        {
            timerGame->stop();
            timerAction->stop();
            isKey = false;
            QString gameDied = QString("啪叽!你死了,你的长度是%1").arg(bodyLen);
            //QMessageBox overGame(QMessageBox::Warning, "结束游戏", gameDied, QMessageBox::Yes | QMessageBox::No);
             int overSelect = QMessageBox::warning(this, "结束游戏", gameDied, tr("重新开始"), tr("离开游戏"));

            //重新开始
            if (overSelect == 0) {
                gameStart();
                timerGame->start();
                timerAction->start();
            }

            //结束游戏
            if (overSelect == 1)
            {
                emit gameClose();
            }
            return;
        }
    }

    update();
}

//蛇动作
void GameWidget::snakeAction()
{
    //当大于4时重置为1
    if(mapSnake[0].snakeState == 1)
    {
        if(this->minUp > 4)
        {
            this->minUp = 1;
        }
    }
    if(mapSnake[0].snakeState == 2)
    {
        if(this->minDown > 4)
        {
            this->minDown = 1;
        }
    }
    if(mapSnake[0].snakeState == 3)
    {
        if(this->minLeft > 4)
        {
            this->minLeft = 1;
        }
    }
    if(mapSnake[0].snakeState == 4)
    {
        if(this->minRight > 4)
        {
            this->minRight = 1;
        }
    }
    update();
}

void GameWidget::gameStart()
{
    isKey = true;
    //初始化蛇
    direction = 4;
    bodyLen = 3;
    struct Snake initial[3];
    initial[0].snakeX = 75;
    initial[0].snakeY = 200;
    initial[0].snakeState = 4;
    mapSnake.insert(0, initial[0]);
    for(int i = 1; i < bodyLen; i++)
    {
        initial[i].snakeX = initial[i - 1].snakeX - 25;
        initial[i].snakeY = initial[i - 1].snakeY;
        initial[i].snakeState = initial[i - 1].snakeState;
        mapSnake.insert(i,initial[i]);
    }
    //初始化食物的位置，不能与蛇同在
    foodStrart();
}

void GameWidget::foodStrart()
{
    //初始化食物的位置，不能与蛇同在
    while(1)
    {
        int flag = 1;
        foodX = (qrand() % 32) *25;
        foodY = (qrand() % 18) *25;
        for (int i = 0; i < bodyLen; i++)
        {
            if(mapSnake[i].snakeX == foodX && mapSnake[i].snakeY == foodY)
            {
                flag = 0;
                break;
            }
        }
        if(flag == 1)
        {
            break;
        }
    }
}
