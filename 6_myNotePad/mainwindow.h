#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent * k);
    void mousePressEvent(QMouseEvent *m);

private slots:
    void on_xinjian_triggered();

    void on_dakai_triggered();

    void on_lingcunwei_triggered();



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
