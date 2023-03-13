#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
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

private slots:
    void on_StartButton_clicked();

    void on_StopButton_clicked();

    void timeOutSlot();

    void on_SingleButton_clicked();

private:
    Ui::Widget *ui;
    QTimer* timer;
    int picId;
};
#endif // WIDGET_H
