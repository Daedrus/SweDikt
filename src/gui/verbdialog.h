#ifndef VERBDIALOG_H
#define VERBDIALOG_H

#include <QDialog>

namespace Ui {
    class VerbDialog;
}

class VerbDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VerbDialog(QWidget *parent = 0);
    ~VerbDialog();

    QString getImperativForm();
    QString getInfinitivForm();
    QString getPresensForm();
    QString getPreteritumForm();
    QString getSupinumForm();
    QString getEngTrans();

private:
    Ui::VerbDialog *ui;
};

#endif // VERBDIALOG_H
