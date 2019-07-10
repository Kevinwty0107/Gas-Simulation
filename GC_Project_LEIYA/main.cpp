#include "mainwindow.h"
#include "inidialog.h"
#include <QApplication>
#include <QFileDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //IniDialog ID;
    //ID.show();
    /*QFileDialog f;
    f.open();*/
    return a.exec();
}
