#ifndef INIDIALOG_H
#define INIDIALOG_H

#include <QDialog>

namespace Ui {
class IniDialog;
}

class IniDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IniDialog(QWidget *parent = 0);
    ~IniDialog();

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
    bool IniSucc();
public slots:
    void accept();
    //void reject();

private:
    Ui::IniDialog *ui;
    bool flag;
};

#endif // INIDIALOG_H
