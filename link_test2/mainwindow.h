#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <vector>
#include <Ball.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    initialize_LR(int,int);
    initialize(int,double,double,double,int,int,double ,double,double,int);
        //完整版初始化信号，各参数分别对应int N1,double m1,double r1,double p1,int f1,int N2,double m2,double r2,double p2,int f2
    LoadIni(void*);
    timePass();
    timePass(int);
    reverseVelo();
    showTime(QString);
    showFPS(int);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void iniB();
    void startB();
    void stopB();
    void loadB();
    void saveB();
    void revB();
    void timeEve(int);

private slots:
    void tick();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    int GasNumber=1000;
    QTime TotalTime;
    int timeInterval=50;

    //存储有关信息
    int GasN1=0;
    double M1=1;
    double R1=0.5;
    double P1=1;
    int F1=0;

    int GasN2=0;
    double M2=1;
    double R2=0.5;
    double P2=1;
    int F2=0;
};

#endif // MAINWINDOW_H
