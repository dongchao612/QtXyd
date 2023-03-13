#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    picId=1;

    timer=new QTimer;
    QImage img;
    img.load(":/image/0.png");
    ui->label->setPixmap(QPixmap::fromImage(img));

    //定时器事件到了 发出timeout信号
    connect(timer,&QTimer::timeout,this,&Widget::timeOutSlot);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::timeOutSlot()
{
    QString path(":/image/");
    path+=QString::number(picId);
    path+=".png";

    QImage img;
    img.load(path);
    ui->label->setPixmap(QPixmap::fromImage(img));

    picId++;
    if(picId==MAXPICNUM)
        picId=0;
}
void Widget::on_StartButton_clicked()
{
    timer->start(TIMEOUT);
}


void Widget::on_StopButton_clicked()
{
    timer->stop();
}


void Widget::on_SingleButton_clicked()
{
    QTimer::singleShot(TIMEOUT,this,SLOT(timeOutSlot()));
}

