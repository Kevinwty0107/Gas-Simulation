#ifndef INITIALIZEDIALOG_H
#define INITIALIZEDIALOG_H

#include <QDialog>

namespace Ui {
class initializeDialog;
}

class initializeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit initializeDialog(QWidget *parent = 0);
    ~initializeDialog();

private:
    Ui::initializeDialog *ui;
};

#endif // INITIALIZEDIALOG_H
