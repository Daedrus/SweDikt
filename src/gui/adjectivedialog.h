#ifndef ADJECTIVEDIALOG_H
#define ADJECTIVEDIALOG_H

#include <QDialog>

namespace Ui {
    class AdjectiveDialog;
}

class AdjectiveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdjectiveDialog(QWidget *parent = 0);
    ~AdjectiveDialog();

    QString getPositivForm();
    QString getKomparativForm();
    QString getSuperlativForm();
    QString getEngTrans();

private:
    Ui::AdjectiveDialog *ui;
};

#endif // ADJECTIVEDIALOG_H
