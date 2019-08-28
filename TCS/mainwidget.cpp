#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QTimer>
#include <QPainter>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    this->setFixedSize(800, 450);
    stackedSnake.setParent(this);
    stackedSnake.setFixedSize(800, 450);
    stackedSnake.addWidget(&widgetStart);
    widgetStart.setFixedSize(800, 450);
    stackedSnake.setCurrentWidget(&widgetStart);

    //开始页面
    //开始按钮
    buttonStart = new MyPushButton(":/new/image/start.png", 1);
    buttonStart->setParent(&widgetStart);
    buttonStart->move(this->width() * 0.5 - buttonStart->width() * 0.5, 120);
    connect(buttonStart, &MyPushButton::clicked, [=](){
        buttonStart->zoom1();
        buttonStart->zoom2();
        QTimer::singleShot(200, this, [=](){
            stackedSnake.setCurrentWidget(&widgetGame);
        });
    });

    //离开游戏
    buttonClose = new MyPushButton(":/new/image/close.png", 1);
    buttonClose->setParent(&widgetStart);
    buttonClose->move(this->width() * 0.5 - buttonStart->width() * 0.5, 250);
    connect(buttonClose, &MyPushButton::clicked, [=](){
        buttonClose->zoom1();
        buttonClose->zoom2();
        QTimer::singleShot(200, this, [=](){
            this->close();
        });
    });

    //游戏页面
    stackedSnake.addWidget(&widgetGame);
    connect(&widgetGame, &GameWidget::gameClose, [=](){
        this->close();
    });

}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::paintEvent(QPaintEvent *)
{
    //背景
    QPainter groundPainter(this);
    groundPainter.drawPixmap(0, 0, QPixmap(":/new/image/74000492_p0.png"));
}
