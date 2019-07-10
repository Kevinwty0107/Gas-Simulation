#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <inidialog.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->setInterval(timeInterval);
    connect(timer, SIGNAL(timeout()), this, SLOT(tick()));

    ui->startButton->setDisabled(true);
    ui->stopButton->setDisabled(true);
    ui->revButton->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::iniB()
{
    IniDialog ID;
    /*ID.show();
    ID.raise();
    ID.activateWindow();*/
    if (!ID.exec())
    {
        //std::cout<<"YES"<<std::endl;
        if (!ID.IniSucc()) return;
        //bool flag=ID.IniSucc();
        GasN1=ID.GasN1;
        M1=ID.M1/10;
        R1=ID.R1/10;
        P1=ID.P1;
        F1=ID.F1;
        GasN2=ID.GasN2;
        M2=ID.M2/10;
        R2=ID.R2/10;
        P2=ID.P2;
        F2=ID.F2;

        //std::cout<<GasN1<<' '<<M1<<' '<<R1<<' '<<P1<<' '<<F1<<std::endl;
        //std::cout<<GasN2<<' '<<M2<<' '<<R2<<' '<<P2<<' '<<F2<<std::endl;
        //bool flag=ID.IniSucc();

        //emit initialize_LR(200,1);
        //GasN1=200;M1=1.0;R1=0.5;P1=0.8;F1=1;
        //GasN2=150;M2=1.2;R2=1.0;P2=1.2;F2=-1;
        //emit initialize(200,1.0,0.5,0.8,1,150,1.2,1.0,1.2,-1);
        emit initialize(GasN1,M1,R1,P1,F1,GasN2,M2,R2,P2,F2);
        if (GasN1+GasN2==0) {ui->startButton->setDisabled(true);return;}
        emit setN1(GasN1);
        emit setN2(GasN2);

        //emit set
        ui->startButton->setDisabled(false);
        TotalTime=QTime(0,0,0,0);
    }
    //std::cout<<"NOT"<<std::endl;

}

void MainWindow::startB()
{
    ui->iniButton->setDisabled(true);
    ui->loadButton->setDisabled(true);
    ui->saveButton->setDisabled(true);
    ui->startButton->setDisabled(true);
    ui->stopButton->setDisabled(false);
    ui->revButton->setDisabled(false);
    timer->start();
    tick();
}

void MainWindow::stopB()
{
    ui->iniButton->setDisabled(false);
    ui->loadButton->setDisabled(false);
    ui->saveButton->setDisabled(false);
    ui->startButton->setDisabled(false);
    ui->startButton->setDisabled(false);
    ui->stopButton->setDisabled(true);
    ui->revButton->setDisabled(true);
    timer->stop();
}

void MainWindow::loadB()
{

    QFileDialog dialog;
    dialog.setNameFilter(tr("Binary Data (*.dat);; Text Files (*.txt)"));

    dialog.open();
    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    if (!fileNames.empty())ui->startButton->setDisabled(false);

    if (fileNames.isEmpty()) return;

    QFile f(fileNames[0]);
    f.open(QIODevice::ReadOnly);
    QDataStream fin(&f);
    fin.setVersion(QDataStream::Qt_5_5);

    quint32 n1,f1,n2,f2;
    qreal m1,r1,p1,m2,r2,p2;
    fin>>n1>>m1>>r1>>p1>>f1;
    fin>>n2>>m2>>r2>>p2>>f2;

    GasN1=n1;M1=m1;R1=r1;P1=p1;F1=f1;
    GasN2=n2;M2=m2;R2=r2;P2=p2;F2=f2;

    vector<Ball> temp;
    qreal lx,ly,lz,vx,vy,vz;
    //Vect l,v;
    for (int i=0;i<GasN1;++i)
    {
        fin>>lx>>ly>>lz;
        fin>>vx>>vy>>vz;
        //l=Vect(lx,ly,lz);
        //v=Vect(vx,vy,vz);
        Ball t(M1,R1,Vect(lx,ly,lz),Vect(vx,vy,vz));
        temp.push_back(t);
    }
    for (int i=0;i<GasN2;++i)
    {
        fin>>lx>>ly>>lz;
        fin>>vx>>vy>>vz;
        Ball t(M2,R2,Vect(lx,ly,lz),Vect(vx,vy,vz));
        temp.push_back(t);
    }
    //std::cout<<temp.size()<<std::endl;
    ui->openGLWidget->readIni(temp,n1,n2,r1,r2);
    emit setN1(GasN1);
    emit setN2(GasN2);

    /*quint32 n;
    quint32 temp;
    fin>>n;
    for (int i=0;i<n;++i) {fin>>temp;std::cout<<temp<<std::endl;}*/
}

void MainWindow::saveB()
{
    QFileDialog dialog;
    dialog.setNameFilter(tr("Binary Data (*.dat);; Text Files (*.txt)"));
    dialog.open();
    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    if (fileNames.isEmpty()) return;
    QFile f(fileNames[0]);
    f.open(QIODevice::WriteOnly);
    QDataStream fout(&f);
    fout.setVersion(QDataStream::Qt_5_5);

    fout<<(quint32)GasN1<<(qreal)M1<<(qreal)R1<<(qreal)P1<<(quint32)F1;
    fout<<(quint32)GasN2<<(qreal)M2<<(qreal)R2<<(qreal)P2<<(quint32)F2;
    //std::cout<<GasN1<<std::endl;
    vector<Ball> temp = ui->openGLWidget->out();
    auto it=temp.begin();
    for (int i=0;i<GasN1+GasN2;++i)
    {
        fout<<(qreal)it->l_().x_()<<(qreal)it->l_().y_()<<(qreal)it->l_().z_();
        fout<<(qreal)it->v_().x_()<<(qreal)it->v_().y_()<<(qreal)it->v_().z_();
        ++it;
    }

    /*std::cout<<"out!"<<std::endl;
    int n=5;
    fout<<(quint32)n;
    for (int i=0;i<n;++i) fout<<(quint32)(i*i);*/
}

void MainWindow::revB()
{
    timer->stop();
    //for (int i=0;i<100000000;++i){}

    emit reverseVelo();
    timer->start();
}

void MainWindow::timeEve(int deltaT)
{
    if (deltaT<20) deltaT=20;
    timeInterval=deltaT;
    TotalTime=TotalTime.addMSecs(timeInterval);
}

void MainWindow::tick()
{
    emit timePass(timeInterval);
    //emit timePass();
    timer->stop();
    timer->setInterval(timeInterval);
    int fps=(984/timeInterval);
    QString temp(TotalTime.toString());
    emit showTime(temp);
    emit showFPS(fps);
    auto it=ui->openGLWidget->out().begin();
    double t1=0,t2=0;
    for (int i=0;i<GasN1;++i)
    {
        t1+=0.5*M1*(it->v_().length()*it->v_().length());
        ++it;
    }
    for (int i=0;i<GasN2;++i)
    {
        t2+=0.5*M2*(it->v_().length()*it->v_().length());
        ++it;
    }
    //质量为10，速度为5的粒子平均动能为51.1(折合）,设为T=50
    //std::cout<<"EK:"<<t1+t2<<std::endl;
    t1=50*((t1/GasN1)/51.1);
    t2=50*((t2/GasN2)/51.1);
    QString T1;
    QString T2;
    T1.setNum(t1);
    T2.setNum(t2);
    if (GasN1==0) T1="0";
    if (GasN2==0) T2="0";
    emit setT1(T1);
    emit setT2(T2);
    timer->start();
}
