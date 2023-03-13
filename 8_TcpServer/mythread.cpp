#include "mythread.h"
#include <QDebug>

myThread::myThread(QTcpSocket *s)
{
    socket = s;
}

void myThread::run()
{
    connect(socket, &QTcpSocket::readyRead, this, &myThread::clientInfoSlot);
}

//不能在其他类里面操作界面
void myThread::clientInfoSlot()
{
    // qDebug() << socket->readAll().data();
    QByteArray ba = socket->readAll(); //不能操作UI文件
    emit sendToWidget(ba);      //发送信号
}