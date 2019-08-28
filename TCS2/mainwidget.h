#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include "mypushbutton.h"
#include "gamewidget.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    void paintEvent(QPaintEvent *);

private:
    Ui::MainWidget *ui;
    QStackedWidget stackedSnake;//大窗口
    QWidget widgetStart;//开始窗口
    GameWidget widgetGame;//游戏窗口
    MyPushButton *buttonStart;//开始按钮
    MyPushButton *buttonClose;//关闭按钮
};

#endif // MAINWIDGET_H
