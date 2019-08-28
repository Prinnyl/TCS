#include "mypushbutton.h"
#include <QMessageBox>
#include <QPropertyAnimation>

//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
//{

//}

MyPushButton::MyPushButton(QString imageA, double B)
{
    QPixmap pixmapImage;
    bool ret = pixmapImage.load(imageA);
    if(ret == false)
    {
        QMessageBox::warning(this, "错误", "加载按钮图片出错");
        return;
    }
    this->setFixedSize(pixmapImage.width() *B, pixmapImage.height() *B);
    this->setStyleSheet("QPushButton{border : 0px;}");
    this->setIcon(pixmapImage);
    this->setIconSize(QSize(pixmapImage.width() *B, pixmapImage.height() *B));
}

//弹跳，下去
void MyPushButton::zoom1()
{
    QPropertyAnimation *myAnimation = new QPropertyAnimation(this, "geometry");
    myAnimation->setDuration(100);
    myAnimation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    myAnimation->setEndValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    myAnimation->setEasingCurve(QEasingCurve::OutBounce);
    myAnimation->start();
}

//弹跳，回来
void MyPushButton::zoom2()
{
    QPropertyAnimation *myAnimation = new QPropertyAnimation(this, "geometry");
    myAnimation->setDuration(100);
    myAnimation->setStartValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    myAnimation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    myAnimation->setEasingCurve(QEasingCurve::OutBounce);
    myAnimation->start();
}
