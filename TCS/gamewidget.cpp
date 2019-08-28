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

    isKey = true;
    //初始化蛇
    direction = 4;
    headX[0] = 75;
    headY[0] = 200;
    headState[0] = 4;
    bodyLen = 3;
    for (int i = 1; i < bodyLen; i++)
    {
        headX[i] = headX[i - 1] - 25;
        headY[i] = headY[i - 1];
        headState[i] = headState[i - 1];
    }

    //初始化食物的位置，不能与蛇同在
    while(1)
    {
        int flag = 1;
        foodX = (qrand() % 32) *25;
        foodY = (qrand() % 18) *25;
        for (int i = 0; i < bodyLen; i++)
        {
            if(headX[i] == foodX && headY[i] == foodY)
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
    if(headState[0] == 1)
    {
        gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(snakeUp));
    }
    if(headState[0] == 2)
    {
        gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(snakeDown));
    }
    if(headState[0] == 3)
    {
        gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(snakeLeft));
    }
    if(headState[0] == 4)
    {
        gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(snakeRight));
    }
    if(headState[0] == 5)
    {
        gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headupleft.png"));
    }
    if(headState[0] == 6)
    {
        gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headupright.png"));
    }
    if(headState[0] == 7)
    {
        gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headleftup.png"));
    }
    if(headState[0] == 8)
    {
        gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headrightup.png"));
    }
    if(headState[0] == 9)
    {
        gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headleftdown.png"));
    }
    if(headState[0] == 10)
    {
        gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headrightdown.png"));
    }
    if(headState[0] == 11)
    {
        gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headdownleft.png"));
    }
    if(headState[0] == 12)
    {
        gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headdownright.png"));
    }
    //蛇身
    for (int i = 1; i < bodyLen; i++)
    {
        if(headState[i] == 1 || headState[i] == 2)
        {
            gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/bodyup.png"));
        }
        if(headState[i] == 3 || headState[i] == 4)
        {
            gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/bodyleft.png"));
        }
        if(headState[i] == 5 || headState[i] == 10)
        {
            gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/upleft.png"));
        }
        if(headState[i] == 6 || headState[i] == 9)
        {
            gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/upright.png"));
        }
        if(headState[i] == 7 || headState[i] == 12)
        {
            gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/downright.png"));
        }
        if(headState[i] == 8 || headState[i] == 11)
        {
            gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/downleft.png"));
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
            headState[0] = 7;
        }
        if(preDirection == 4)
        {
            headState[0] = 8;
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
            headState[0] = 9;
        }
        if(preDirection == 4)
        {
            headState[0] = 10;
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
            headState[0] = 5;
        }
        if(preDirection == 2)
        {
            headState[0] = 11;
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
            headState[0] = 6;
        }
        if(preDirection == 2)
        {
            headState[0] = 12;
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
        headX[i] = headX[i - 1];
        headY[i] = headY[i - 1];
        headState[i] = headState[i - 1];
    }

    if(headState[0] == 5 || headState[0] == 11)
    {
        headState[0] = 3;
    }
    if(headState[0] == 6 || headState[0] == 12)
    {
        headState[0] = 4;
    }
    if(headState[0] == 7 || headState[0] == 8)
    {
        headState[0] = 1;
    }
    if(headState[0] == 9 || headState[0] == 10)
    {
        headState[0] = 2;
    }

    if(direction == 1)
    {
        headY[0] = headY[0] - 25;
    }
    else if(direction == 2)
    {
        headY[0] = headY[0] + 25;
    }
    else if(direction == 3)
    {
        headX[0] = headX[0] - 25;
    }
    else if(direction == 4)
    {
        headX[0] = headX[0] + 25;
    }

    //穿墙
    if(headX[0] < 0)
    {
        headX[0] = this->width() - 25;
        //qDebug() << this->width();
    }
    else if(headX[0] == this->width())
    {
        headX[0] = 0;
    }
    else if(headY[0] < 0)
    {
        headY[0] = this->height() -25;
    }
    if(headY[0] == this->height())
    {
        headY[0] = 0;
    }

    //吃的判定
    if(headX[0] == foodX && headY[0] == foodY)
    {
        while(1)
        {
            int flag = 1;
            foodX = (qrand() % 32) *25;
            foodY = (qrand() % 18) *25;
            for (int i = 0; i < bodyLen; i++)
            {
                if(headX[i] == foodX && headY[i] == foodY)
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
        bodyLen++;
        headX[bodyLen - 1] = headX[bodyLen - 2];
        headY[bodyLen - 1] = headY[bodyLen - 2];
        headState[bodyLen - 1] = headState[bodyLen - 2];
    }


    //死亡判定
    for(int i = 1; i < bodyLen; i++)
    {
        if(headX[0] == headX[i] && headY[0] == headY[i])
        {
            timerGame->stop();
            timerAction->stop();
            isKey = false;
            QString gameDied = QString("啪叽!你死了,你的长度是%1").arg(bodyLen);
            //QMessageBox overGame(QMessageBox::Warning, "结束游戏", gameDied, QMessageBox::Yes | QMessageBox::No);
             int overSelect = QMessageBox::warning(this, "结束游戏", gameDied, tr("重新开始"), tr("离开游戏"));

            //重新开始
            if (overSelect == 0) {
                isKey = true;
                //初始化蛇
                direction = 4;
                headX[0] = 75;
                headY[0] = 200;
                headState[0] = 4;
                bodyLen = 3;
                for (int i = 1; i < bodyLen; i++)
                {
                    headX[i] = headX[i - 1] - 25;
                    headY[i] = headY[i - 1];
                    headState[i] = headState[i - 1];
                }

                //初始化食物的位置，不能与蛇同在
                while(1)
                {
                    int flag = 1;
                    foodX = (qrand() % 32) *25;
                    foodY = (qrand() % 18) *25;
                    for (int i = 1; i < bodyLen; i++)
                    {
                        if(headX[0] == foodX && headY[i] == foodY)
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
    if(headState[0] == 1)
    {
        if(this->minUp > 4)
        {
            this->minUp = 1;
        }
    }
    if(headState[0] == 2)
    {
        if(this->minDown > 4)
        {
            this->minDown = 1;
        }
    }
    if(headState[0] == 3)
    {
        if(this->minLeft > 4)
        {
            this->minLeft = 1;
        }
    }
    if(headState[0] == 4)
    {
        if(this->minRight > 4)
        {
            this->minRight = 1;
        }
    }
    update();
}
