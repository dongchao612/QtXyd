#include "widget.h"
#include "ui_widget.h"
#include <QProcess>
#include <QMessageBox>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    // 连接信号与槽
    connect(ui->cmdLineEdit,SIGNAL(returnPressed()),this,SLOT(on_commitButton_clicked()));

    connect(ui->cancelButton,&QPushButton::clicked,this,&Widget::on_cancelButton_clicked);

    connect(ui->browseButton,&QPushButton::clicked,[this](){
        QMessageBox::information(this,"信息","点击浏览");
    });
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_commitButton_clicked()
{
    // 获取QlineEdit的值
    QString program=ui->cmdLineEdit->text();
    //创建一个QProcess对象
    QProcess *myProcess = new QProcess(this);
    myProcess->start(program);
}


void Widget::on_cancelButton_clicked()
{
    this->close();
}

