#include "widget.h"
#include "ui_widget.h"
#include <QHostAddress>
#include <QMessageBox>
#include "chat.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    socket=new QTcpSocket;//创建socket对象
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_cancelButton_clicked()
{
    this->close();
}

void Widget::on_connectButton_clicked()
{
    // 获取IP和地址号
    QString IP=ui->ipLineEdit->text();
    QString port=ui->portLineEdit->text();

    //连接服务器
    socket->connectToHost(QHostAddress(IP),port.toShort());

    //判断是否成功
    connect(socket,&QTcpSocket::connected,[this](){
        QMessageBox::information(this,"连接提示","连接服务器成功");
        this->hide();
        Chat *c=new Chat(socket);// 堆空间创建
        c->show();
    });

    //连接异常
    connect(socket,&QTcpSocket::disconnected,[this](){
        QMessageBox::information(this,"连接提示","连接服务器失败");
    });
}

