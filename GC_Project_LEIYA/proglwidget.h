#ifndef PROGLWIDGET_H
#define PROGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QMouseEvent>

#include "stdafx.h"
#include "Vect.h"
#include "Wall.h"
#include "Gas.h"
#include "Ball.h"
#include <cstdlib>
#include <ctime>
#include "LCG.h"
#include <QTimer>
#include <QTime>
#define NUM 1000
#define POINT_SIZE 11
class proGLWidget : public QOpenGLWidget
{
    Q_OBJECT
    //friend class MainWindow;
signals:
    timeCost(int);
public:
    proGLWidget(QOpenGLWidget *parent = 0);
    proGLWidget(QWidget *parent = 0);
    ~proGLWidget();
//protected:
    void initializeGL();
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    vector<Ball> out() { return g.output();}
public slots:
    void step();
    void step(int);
    void initialize();
    //void initialize(int N);
    void initialize_LR(int N,int flag);
    void initialize(int N1,double m1=0,double r1=0.5,double p1=1,int f1=0,int N2=0,double m2=1,double r2=0.5,double p2=1,int f2=0);

    void readIni(vector<Ball>& bVec,int n1,int n2,double p1,double p2);
    //void readIni(void* p);
    void stop(){flag=false;}
    void reverse(){/*std::cout<<"Reverse!"<<std::endl;*/g.reverse();}
private:
    void draw();
    Wall w;
    Gas g;
    //GLfloat a[NUM][3];
    GLfloat RotateX=30;
    GLfloat RotateY=-25;
    GLfloat RotateZ=0;
    QPoint lastPos;
    GLfloat pointSize=POINT_SIZE;
    GLfloat pSize1=POINT_SIZE;
    GLfloat pSize2=POINT_SIZE;

    QTime t;
    int num=0,num1=0,num2=0;
    bool flag=true;
};

#endif // PROGLWIDGET_H
