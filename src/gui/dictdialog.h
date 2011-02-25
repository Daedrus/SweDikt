#ifndef DICTDIALOG_H
#define DICTDIALOG_H

#include "swedictionary.h"
#include "swedictionarytablemodel.h"

#include <QDialog>

namespace Ui {
    class DictDialog;
}

class DictDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DictDialog(QWidget *parent, SweDictionary *sweDict);
    ~DictDialog();

private:
    Ui::DictDialog *ui;
    SweDictionary *sweDict_;
    SweDictionaryTableModel *currentModel_;

private slots:
    void on_saveButton_clicked();
    void on_deleteRowButton_clicked();
    void on_tableSelection_activated(int index);
};

#endif // DICTDIALOG_H
