#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QTimer>

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);//绘图事件
    void keyPressEvent(QKeyEvent *event);
    void snakeMove();//蛇移动
    void snakeAction();//蛇动作

signals:
    void gameClose();

public slots:
private:
    int direction;//方向 1上  2下  3左  4右
    int preDirection;//前一个的方向  1上  2下  3左  4右
    int headX[500];//蛇X轴保存数组
    int headY[500];//蛇Y轴保存数组
    int headState[500];//蛇状态 1上，2下，3左，4右，5上左，6上右，7左上，8右上，9左下，10右下，11下左，12下右
    int bodyLen;//蛇长
    int foodX;//食物X
    int foodY;//食物Y
    QPainter *gamePainter;//游戏贴图
    QTimer *timerGame;//持续移动
    bool isKey;//是否能按按键
    int minUp = 1;
    int minDown = 1;
    int minLeft = 1;
    int minRight = 1;
    QTimer *timerAction;//持续动作
};

#endif // MYWIDGET_H
