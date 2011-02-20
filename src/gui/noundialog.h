#ifndef NOUNDIALOG_H
#define NOUNDIALOG_H

#include <QDialog>

namespace Ui {
    class NounDialog;
}

class NounDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NounDialog(QWidget *parent = 0);
    ~NounDialog();

    QString getEnEtt();
    QString getBestSingForm();
    QString getObestSingForm();
    QString getBestPlurForm();
    QString getObestPlurForm();
    QString getEngTrans();

private:
    Ui::NounDialog *ui;
};

#endif // NOUNDIALOG_H
