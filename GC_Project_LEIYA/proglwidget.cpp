
#include "proglwidget.h"
#include <QOpenGLFunctions_4_5_Compatibility>
#include <cstdlib>
#include <QTime>

proGLWidget::proGLWidget(QOpenGLWidget *parent)
    : QOpenGLWidget(parent),w(RANGE)
{
    setEnabled(true);
}

proGLWidget::proGLWidget(QWidget *parent)
    : QOpenGLWidget((QOpenGLWidget*)parent),w(RANGE)
{
    setEnabled(true);
}

proGLWidget::~proGLWidget()
{

}

void proGLWidget::initializeGL()
{
    QOpenGLFunctions_4_5_Compatibility *f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Compatibility>();
    f->glClearColor(0.26275,0.26275,0.26275,0.0);
}

void proGLWidget::paintGL()
{
    QOpenGLFunctions_4_5_Compatibility *f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Compatibility>();
    f->glEnable(GL_DEPTH_TEST);
    f->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    draw();
}

void proGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos=event->pos();
    //step();
}

void proGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    double k=1.5;//处理屏幕旋转的速度
    GLfloat dx = (GLfloat)(event->x()-lastPos.x())/(width()*k);
    GLfloat dy = (GLfloat)(event->y()-lastPos.y())/(height()*k);
    RotateX+=180*dy;
    RotateY+=180*dx;
    if (RotateX<0) RotateX=0;
    if (RotateX>90) RotateX=90;
    if (RotateY>90) RotateY=90;
    if (RotateY<-90) RotateY=-90;
    update();
    lastPos= event->pos();
}

void proGLWidget::step()
{
    t=QTime::currentTime();
    g.timePass(w);
    int deltaT=t.msecsTo(QTime::currentTime());
    emit timeCost(deltaT);
    update();
}
void proGLWidget::step(int dt)
{
    t=QTime::currentTime();
    g.timePass(w,(double)dt/984);
    int deltaT=t.msecsTo(QTime::currentTime());
    emit timeCost(deltaT);
    update();
}

void proGLWidget::initialize()
{
    num=NUM;
    num1=num;

    g=Gas();
    LCG rng(unsigned(time(0)));

    for (int i = 0; i < NUM; ++i)
    {
        Vect x(rng() * 2*RANGE - RANGE ,rng() * 2 * RANGE - RANGE, rng() * 2 * RANGE - RANGE);
        Vect v(rng() * RANGE - RANGE/2, rng() * RANGE - RANGE / 2, rng() * RANGE - RANGE / 2);
        Ball temp(1.0,0.5,x,v);
        if (!g.is_Overlap(temp) && !temp.isCollision_2_notStep(w)) g.addBall(temp); else --i;
    }
    update();
}

/*void proGLWidget::initialize(int N)
{
    g=Gas();
    LCG rng(unsigned(time(0)));

    for (int i = 0; i < N; ++i)
    {
        Vect x(rng() * 2*RANGE - RANGE ,rng() * 2 * RANGE - RANGE, rng() * 2 * RANGE - RANGE);
        Vect v(rng() * RANGE - RANGE/2, rng() * RANGE - RANGE / 2, rng() * RANGE - RANGE / 2);
        Ball temp(1.0,0.5,x,v);
        if (!g.is_Overlap(temp) && !temp.isCollision_2_notStep(w)) g.addBall(temp); else --i;
    }
    update();
}*/

void proGLWidget::initialize(int N1,double m1,double r1,double p1,int f1,int N2,double m2,double r2,double p2,int f2)
    //N表示粒子数目，m为质量，r为半径，p为速度比率，f标记空间分布
{
    num=N1+N2;
    num1=N1;
    num2=N2;
    pSize1=POINT_SIZE*r1;
    pSize2=POINT_SIZE*r2;
    g=Gas();
    LCG rng(unsigned(time(0)));

    if (f1==0)//全空间
    {
        for (int i = 0; i < N1; ++i)
        {
            Vect x(rng() * 2*RANGE - RANGE ,rng() * 2 * RANGE - RANGE, rng() * 2 * RANGE - RANGE);
            Vect v(p1*rng() * RANGE - RANGE/2, p1*rng() * RANGE - RANGE / 2, p1*rng() * RANGE - RANGE / 2);
            Ball temp(m1,r1,x,v);
            if (!g.is_Overlap(temp) && !temp.isCollision_2_notStep(w)) g.addBall(temp); else --i;
        }
    }
    if (f1==1)//右半空间
    {
        for (int i = 0; i < N1; ++i)
        {
            Vect x(rng() * RANGE ,rng() * 2 * RANGE - RANGE, rng() * 2 * RANGE - RANGE);
            Vect v(p1*rng() * RANGE - RANGE/2, p1*rng() * RANGE - RANGE / 2, p1*rng() * RANGE - RANGE / 2);
            Ball temp(m1,r1,x,v);
            if (!g.is_Overlap(temp) && !temp.isCollision_2_notStep(w)) g.addBall(temp); else --i;
        }
    }
    if (f1==-1)//左半空间
    {
        for (int i = 0; i < N1; ++i)
        {
            Vect x(rng() * RANGE - RANGE ,rng() * 2 * RANGE - RANGE, rng() * 2 * RANGE - RANGE);
            Vect v(p1*rng() * RANGE - RANGE/2, p1*rng() * RANGE - RANGE / 2, p1*rng() * RANGE - RANGE / 2);
            Ball temp(m1,r1,x,v);
            if (!g.is_Overlap(temp) && !temp.isCollision_2_notStep(w)) g.addBall(temp); else --i;
        }
    }

    if (f2==0)//全空间
    {
        for (int i = 0; i < N2; ++i)
        {
            Vect x(rng() * 2*RANGE - RANGE ,rng() * 2 * RANGE - RANGE, rng() * 2 * RANGE - RANGE);
            Vect v(p2*rng() * RANGE - RANGE/2, p2*rng() * RANGE - RANGE / 2, p2*rng() * RANGE - RANGE / 2);
            Ball temp(m2,r2,x,v);
            if (!g.is_Overlap(temp) && !temp.isCollision_2_notStep(w)) g.addBall(temp); else --i;
        }
    }
    if (f2==1)//右半空间
    {
        for (int i = 0; i < N2; ++i)
        {
            Vect x(rng() * RANGE ,rng() * 2 * RANGE - RANGE, rng() * 2 * RANGE - RANGE);
            Vect v(p2*rng() * RANGE - RANGE/2, p2*rng() * RANGE - RANGE / 2, p2*rng() * RANGE - RANGE / 2);
            Ball temp(m2,r2,x,v);
            if (!g.is_Overlap(temp) && !temp.isCollision_2_notStep(w)) g.addBall(temp); else --i;
        }
    }
    if (f2==-1)//左半空间
    {
        for (int i = 0; i < N2; ++i)
        {
            Vect x(rng() * RANGE - RANGE ,rng() * 2 * RANGE - RANGE, rng() * 2 * RANGE - RANGE);
            Vect v(p2*rng() * RANGE - RANGE/2, p2*rng() * RANGE - RANGE / 2, p2*rng() * RANGE - RANGE / 2);
            Ball temp(m2,r2,x,v);
            if (!g.is_Overlap(temp) && !temp.isCollision_2_notStep(w)) g.addBall(temp); else --i;
        }
    }
    update();
}

void proGLWidget::initialize_LR(int N,int flag=0)//flag为1则只出现在右边，-1左边，0两边都有
{
    g=Gas();
    LCG rng(unsigned(time(0)));
    if (flag==0)//全空间
    {
        for (int i = 0; i < N; ++i)
        {
            Vect x(rng() * 2*RANGE - RANGE ,rng() * 2 * RANGE - RANGE, rng() * 2 * RANGE - RANGE);
            Vect v(rng() * RANGE - RANGE/2, rng() * RANGE - RANGE / 2, rng() * RANGE - RANGE / 2);
            Ball temp(1.0,0.5,x,v);
            if (!g.is_Overlap(temp) && !temp.isCollision_2_notStep(w)) g.addBall(temp); else --i;
        }
    }
    if (flag==1)//右半空间
    {
        for (int i = 0; i < N; ++i)
        {
            Vect x(rng() * RANGE ,rng() * 2 * RANGE - RANGE, rng() * 2 * RANGE - RANGE);
            Vect v(rng() * RANGE - RANGE/2, rng() * RANGE - RANGE / 2, rng() * RANGE - RANGE / 2);
            Ball temp(1.0,0.5,x,v);
            if (!g.is_Overlap(temp) && !temp.isCollision_2_notStep(w)) g.addBall(temp); else --i;
        }
    }
    if (flag==-1)//左半空间
    {
        for (int i = 0; i < N; ++i)
        {
            Vect x(rng() * RANGE - RANGE ,rng() * 2 * RANGE - RANGE, rng() * 2 * RANGE - RANGE);
            Vect v(rng() * RANGE - RANGE/2, rng() * RANGE - RANGE / 2, rng() * RANGE - RANGE / 2);
            Ball temp(1.0,0.5,x,v);
            if (!g.is_Overlap(temp) && !temp.isCollision_2_notStep(w)) g.addBall(temp); else --i;
        }
    }
    update();
}

void proGLWidget::readIni(vector<Ball> &bVec,int n1,int n2,double p1,double p2)
{
    num=n1+n2;
    num1=n1;
    num2=n2;
    pSize1=POINT_SIZE*p1;
    pSize2=POINT_SIZE*p2;
    g=Gas();
    for (auto it:bVec) g.addBall(it);
    update();
}

void proGLWidget::draw()
{
    //顶点信息，2*2*2的立方体
    static const GLfloat pA[3] = {-1.0,-1.0,+1.0};
    static const GLfloat pB[3] = {+1.0,-1.0,+1.0};
    static const GLfloat pC[3] = {+1.0,-1.0,-1.0};
    static const GLfloat pD[3] = {-1.0,-1.0,-1.0};
    static const GLfloat pE[3] = {-1.0,+1.0,+1.0};
    static const GLfloat pF[3] = {+1.0,+1.0,+1.0};
    static const GLfloat pG[3] = {+1.0,+1.0,-1.0};
    static const GLfloat pH[3] = {-1.0,+1.0,-1.0};

    static const GLfloat *const faces[2][4]={
        {pA,pB,pC,pD},{pE,pF,pG,pH}
    };
    static const GLfloat *const riges[4][2]={
        {pA,pE},{pB,pF}, {pC,pG},{pD,pH}
    };

    static const GLfloat CL[3][4]={{0.0000,0.3608,0.6863,0.0},{0.3647,0.6745,0.5059,0.0},{1.0,0.0,0.0,0.0}};
    //static const GLfloat CL[1]=;
    QOpenGLFunctions_4_5_Compatibility *f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Compatibility>();
    f->glColor4d(0,0,1,0);

    f->glLineWidth(3);

    for (int i=0;i<2;++i)
    {
        f->glBegin(GL_LINE_LOOP);
        for (int j=0;j<4;++j) f->glVertex3fv(faces[i][j]);
        f->glEnd();
    }

    for (int i=0;i<4;++i)
    {
        f->glBegin(GL_LINES);
        f->glVertex3fv(riges[i][0]);
        f->glVertex3fv(riges[i][1]);
        f->glEnd();
    }

    //画x,y,z轴以辅助显示
    f->glLineWidth(1);
    f->glEnable(GL_LINE_STIPPLE);
    f->glLineStipple(3,0x5555);
    f->glBegin(GL_LINES);
        f->glVertex3f(0,0,0);
        f->glVertex3f(2,0,0);
        f->glVertex3f(0,0,0);
        f->glVertex3f(0,2,0);
        f->glVertex3f(0,0,0);
        f->glVertex3f(0,0,2);
    f->glEnd();
    f->glDisable(GL_LINE_STIPPLE);

    //画点，分别处理两种气体
    if (g.output().size()!=0)
    {
        //std::cout<<"TE"<<std::endl;
        f->glEnable(GL_POINT_SMOOTH);
        auto it= g.output().begin();

        f->glPointSize(pSize1);

        f->glColor4fv(CL[1]);

        f->glBegin(GL_POINTS);
        for (int i=0;i<num1;++i)
        {
            //std::cout<<num1;
            f->glVertex3f(it->l_().x_()/RANGE,it->l_().y_()/RANGE,it->l_().z_()/RANGE);
            ++it;
        }
        f->glEnd();

        f->glPointSize(pSize2);
        f->glColor4fv(CL[2]);

        f->glBegin(GL_POINTS);
        for (int i=0;i<num2;++i)
        {
            //std::cout<<num2;
            f->glVertex3f(it->l_().x_()/RANGE,it->l_().y_()/RANGE,it->l_().z_()/RANGE);
            ++it;
        }
        f->glEnd();
    }




    f->glMatrixMode(GL_MODELVIEW);
    f->glLoadIdentity();
    f->glTranslated(0,0,-10);
    f->glRotatef(RotateX,1,0,0);
    f->glRotatef(RotateY,0,1,0);
    f->glRotatef(RotateZ,0,0,1);

    f->glMatrixMode(GL_PROJECTION);
    f->glLoadIdentity();
    f->glFrustum(-1.6,1.6,-1.6,1.6,7.9,13);
    //f->glOrtho(-2,2,-2,2,7,13);
    //f->glClearColor(0.5,0.26275,0.26275,0.0);
    f->glFlush();
}
