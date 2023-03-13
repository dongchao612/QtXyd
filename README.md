# QtOnline
学益得在线课堂QT代码

## 01_qmake

```makefile
生成工程文件
	qmake -project
工程文件中添加
	QT+=widgets gui
生成Makefile 
	qmake
mingw32-make
```

## 02_run

```c++
//创建一个QProcess对象
QProcess *myProcess = new QProcess(this);
myProcess->start(program);
```

## 3_calculator

```
//字体对象
QFont f("仿宋",10);
ui->mainLineEdit->setFont(f);

//按钮上放图片
QIcon con(":/image/tt.PNG");
ui->delButton->setIcon(con);

//改变按钮背景色
ui->equalButton->setStyleSheet("background:blue");
```

```c++
QStack<int> s_num, s_opt;

char opt[128] = {0};
int i = 0, tmp = 0, num1, num2;

//把QString转换成char *
QByteArray ba;
ba.append(expression);   //把QString转换成QByteArray
strcpy(opt, ba.data());  //data可以把QByteArray转换成const char *

while (opt[i] != '\0' || s_opt.empty() != true)
{
    if (opt[i] >= '0' && opt[i] <= '9')
    {
        tmp = tmp * 10 + opt[i] - '0';
        i++;
        if (opt[i] < '0' || opt[i] > '9')
        {
            s_num.push(tmp);
            tmp = 0;
        }
    }
    else           //操作符
    {
        if (s_opt.empty() == true || Priority(opt[i]) > Priority(s_opt.top()) ||
            (s_opt.top() == '(' && opt[i] != ')'))
        {
            s_opt.push(opt[i]);
            i++;
            continue;
        }

        if (s_opt.top() == '(' && opt[i] == ')')
        {
            s_opt.pop();
            i++;
            continue;
        }

        if (Priority(opt[i]) <= Priority(s_opt.top()) || (opt[i] == ')' && s_opt.top() != '(') ||
            (opt[i] == '\0' && s_opt.empty() != true))
        {
            char ch = s_opt.top();
            s_opt.pop();
            switch(ch)
            {
                case '+':
                    num1 = s_num.top();
                    s_num.pop();
                    num2 = s_num.top();
                    s_num.pop();
                    s_num.push(num1 + num2);
                    break;
                case '-':
                    num1 = s_num.top();
                    s_num.pop();
                    num2 = s_num.top();
                    s_num.pop();
                    s_num.push(num1 - num2);
                    break;
                case '*':
                    num1 = s_num.top();
                    s_num.pop();
                    num2 = s_num.top();
                    s_num.pop();
                    s_num.push(num1 * num2);
                    break;
                case '/':
                    num1 = s_num.top();
                    s_num.pop();
                    num2 = s_num.top();
                    s_num.pop();
                    s_num.push(num1 / num2);
                    break;
            }
        }
    }
}
ui->mainLineEdit->setText(QString::number(s_num.top()));

int Priority(char ch)
{
    switch(ch)
    {
        case '(':
            return 3;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}
```

## 4_objectTimer

```c++
//图片
QPixmap pix(":/image/0.png");
ui->label->setPixmap(pix);

//开启定时器
#define TIMEOUT 1000
int myTimerId;
myTimerId = this->startTimer(TIMEOUT);

#include <QTimerEvent>
virtual void timerEvent(QTimerEvent *event);


if(event->timerId()!=myTimerId)
{
	return ;
}

killTimer(myTimerId);
```

## 5_QTimer

```c++
//定时器事件到了 发出timeout信号
connect(timer,&QTimer::timeout,this,&Widget::timeOutSlot);

timer->start(TIMEOUT);

timer->stop();
```

## 6_myNotePad

```c++
QString fileName = QFileDialog::getOpenFileName(this,"选择一个文件",QCoreApplication::applicationFilePath(),  //获取当前路径 "");

//KeyPressEnent
if ((k->modifiers() == Qt::ControlModifier) && (k->key() == Qt::Key_S))
{
	// pass
}
```

## 7_TCPClient

```c++
socket=new QTcpSocket;//创建socket对象

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
```



## 8_TcpServer

```c++
server=new QTcpServer;
server->listen(QHostAddress::AnyIPv4, PORT);

//客户端发起连接，server发出信号
connect(server, &QTcpServer::newConnection, this, &Widget::newClientHandler);

//建立TCP连接
QTcpSocket *socket = server->nextPendingConnection();
//socket->peerAddress();   //获取客户端地址
//socket->peerPort();      //获取客户端的端口号

ui->ipLineEdit->setText(socket->peerAddress().toString());
ui->portLineEdit->setText(QString::number(socket->peerPort()));


//服务器收到客户端发送的信息，socket发出readyread信号
// connect(socket, &QTcpSocket::readyRead, this,&Widget::clientInfoSlot);

//启动线程
myThread *t = new myThread(socket);   //创建线程对象
t->start();                           //开始线程

connect(t, &myThread::sendToWidget, this, &Widget::threadSlot); //自定义信号

#if 1
void Widget::clientInfoSlot()
{
    //获取信号的发出者
    QTcpSocket *s = (QTcpSocket *)sender();
    ui->mainLineEdit->setText(QString(s->readAll()));
}
#endif

void Widget::threadSlot(QByteArray b)
{
    ui->mainLineEdit->setText(QString(b));
}
```



## 9_mysql

```c++
db=QSqlDatabase::addDatabase("QSQLITE");// 加载SqLite3 数据库驱动
db.setDatabaseName("mydatabase.db");

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

//    QSqlQuery query;
//    query.exec("select * from student;");
//    while (query.next())
//    {
//        qDebug() << query.value(0);
//        qDebug() << query.value(1);
//        qDebug() << query.value(2);
//	  }
m->select();
```

