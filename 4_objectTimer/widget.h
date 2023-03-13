#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimerEvent>

#define TIMEOUT 1000
#define MAXPICNUM 2

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    virtual void timerEvent(QTimerEvent *event);

private slots:
    void on_StartButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
    int myTimerId;
    int pixId;
};
#endif // WIDGET_H
