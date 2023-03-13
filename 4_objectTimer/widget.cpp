#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    pixId=0;
    QPixmap pix(":/image/0.png");
    ui->label->setPixmap(pix);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_StartButton_clicked()
{
    //开启定时器
    myTimerId = this->startTimer(TIMEOUT);
}

void Widget::timerEvent(QTimerEvent *event)
{

    if(event->timerId()!=myTimerId)
    {
           return ;
    }

    QString path(":/image/");
    path+=QString::number(pixId);
    path+=".png";

    // qDebug()<<path<<endl;
    QPixmap pix(path);
    ui->label->setPixmap(pix);

    pixId++;
    if(pixId==MAXPICNUM)
        pixId=0;
}

void Widget::on_pushButton_2_clicked()
{
    killTimer(myTimerId);
}

