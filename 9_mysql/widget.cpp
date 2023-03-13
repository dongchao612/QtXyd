﻿#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
/*
create database mydatabase;
create table student(
    id inteher unsigned primary key,
    name varchar(16) not null,
    birth date
);

insert into student values(1,"tom","1999-9-9");
*/
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    db=QSqlDatabase::addDatabase("QSQLITE");// 加载SqLite3 数据库驱动
    db.setDatabaseName("mydatabase.db");

    // db.setDatabaseName("localhost");
    // db.setUserName("root");
    // db.setPassword("root");

    if(db.open())
    {
        QMessageBox::information(this,"连接提示","连接成功");
        m=new QSqlTableModel;
        m->setTable("student");
        ui->tableView->setModel(m);
    }
    else
    {
        QMessageBox::warning(this,"连接提示","连接失败");
    }
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_insertPushButton_clicked()
{
    QString id = ui->idLineEdit->text();
    QString name = ui->nameLineEdit->text();
    QString birth = ui->birLineEdit->text();

    QString sql = QString("insert into student values (%1, '%2', '%3');").arg(id).arg(name).arg(birth);

    QSqlQuery query;
    if (query.exec(sql))
    {
        QMessageBox::information(this, "插入提示", "插入成功");
    }
    else
    {
        QMessageBox::information(this, "插入提示", "插入失败");
    }
}


void Widget::on_findPushButton_clicked()
{
//    QSqlQuery query;
//    query.exec("select * from student;");
//    while (query.next())
//    {
//        qDebug() << query.value(0);
//        qDebug() << query.value(1);
//        qDebug() << query.value(2);
//    }
    m->select();
}

