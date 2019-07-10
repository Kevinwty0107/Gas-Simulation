#include "inidialog.h"
#include "ui_inidialog.h"
#include <iostream>
IniDialog::IniDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IniDialog)
{
    ui->setupUi(this);
    flag=false;
    QRegExp regExp_N("[1-9][0-9]{0,3}");
    QRegExp regExp_M("[1-9][0-9]{0,1}");
    QRegExp regExp_R("[1-9][0-9]{0,1}");

    ui->lineEdit_N1->setValidator(new QRegExpValidator(regExp_N,this));
    ui->lineEdit_N2->setValidator(new QRegExpValidator(regExp_N,this));

    ui->lineEdit_M1->setValidator(new QRegExpValidator(regExp_M,this));
    ui->lineEdit_M2->setValidator(new QRegExpValidator(regExp_M,this));

    ui->lineEdit_R1->setValidator(new QRegExpValidator(regExp_R,this));
    ui->lineEdit_R2->setValidator(new QRegExpValidator(regExp_R,this));

}

IniDialog::~IniDialog()
{
    delete ui;
}

bool IniDialog::IniSucc()
{
    return flag;
}

void IniDialog::accept()
{
    flag=true;
    QString sN1,sM1,sR1;
    QString sN2,sM2,sR2;
    sN1=ui->lineEdit_N1->text();
    sM1=ui->lineEdit_M1->text();
    sR1=ui->lineEdit_R1->text();
    //std::cout<<sN1<<sM1<<sR1<<std::endl;

    sN2=ui->lineEdit_N2->text();
    sM2=ui->lineEdit_M2->text();
    sR2=ui->lineEdit_R2->text();
    //std::cout<<sN2<<sM2<<sR2<<std::endl;

    GasN1=0;M1=0;R1=0;
    GasN2=0;M2=0;R2=0;

    for(auto it:sN1)
    {
        GasN1=GasN1*10+it.digitValue();
    }
    for(auto it:sM1)
    {
        M1=M1*10+it.digitValue();
    }
    for(auto it:sR1)
    {
        R1=R1*10+it.digitValue();
    }

    for(auto it:sN2)
    {
        GasN2=GasN2*10+it.digitValue();
    }
    for(auto it:sM2)
    {
        M2=M2*10+it.digitValue();
    }
    for(auto it:sR2)
    {
        R2=R2*10+it.digitValue();
    }

    F1=ui->comboBox_F1->currentIndex();
    if (F1==2) F1=-1;
    F2=ui->comboBox_F2->currentIndex();
    if (F2==2) F2=-1;
    P1=2*(ui->horizontalSlider_P1->value()+1)/99.0;
    P2=2*(ui->horizontalSlider_P2->value()+1)/99.0;
    //std::cout<<F1<<P1<<F2<<P2<<std::endl;
    emit accepted();
    this->close();
}
