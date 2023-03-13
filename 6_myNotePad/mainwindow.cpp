#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_xinjian_triggered()
{
    ui->textEdit->clear();
    this->setWindowTitle("新建文本文件.txt");
}


void MainWindow::on_dakai_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "选择一个文件",
                                                    QCoreApplication::applicationFilePath(),  //获取当前路径
                                                    "");
    if (fileName.isEmpty())
    {
        QMessageBox::warning(this, "警告", "请选择一个文件");
    }
    else
    {
        // qDebug() << fileName;
        ui->statusbar->showMessage(fileName);
        QFile file(fileName);    //创建文件对象
        file.open(QIODevice::ReadOnly);
        QByteArray ba = file.readAll();
        ui->textEdit->setText(QString(ba));
        file.close();
    }
}


void MainWindow::on_lingcunwei_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "另存为",
                    QCoreApplication::applicationFilePath());
    if (fileName.isEmpty())
    {
        QMessageBox::warning(this, "警告", "请选择一个文件");
    }
    else
    {
        QFile file(fileName);
        file.open(QIODevice::WriteOnly);
        //ui->textEdit->toPlainText();
        QByteArray ba;
        ba.append(ui->textEdit->toPlainText());
        file.write(ba);
        file.close();
    }
}
void MainWindow::keyPressEvent(QKeyEvent *k)
{
    if ((k->modifiers() == Qt::ControlModifier) && (k->key() == Qt::Key_S))
    {
        // qDebug()<<"KeyPressEnent"<<endl;
        on_lingcunwei_triggered();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *m)
{
    QPoint pt = m->pos();
    qDebug() << pt;

    if (m->button() == Qt::LeftButton)
    {
        qDebug() << "左键被按下";
    }
    else if (m->button() == Qt::RightButton)
    {
        qDebug() << "右键被按下";
    }
}
