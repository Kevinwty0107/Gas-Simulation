#include "initializedialog.h"
#include "ui_initializedialog.h"

initializeDialog::initializeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::initializeDialog)
{
    ui->setupUi(this);
}

initializeDialog::~initializeDialog()
{
    delete ui;
}
