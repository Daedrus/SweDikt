#ifndef DICTDIALOG_H
#define DICTDIALOG_H

#include "swedictionary.h"
#include "swedictionarytablemodel.h"
#include <QKeyEvent>

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

    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);

private:
    Ui::DictDialog *ui;
    SweDictionary *sweDict_;
    SweDictionaryTableModel *currentModel_;

private slots:
    void on_searchButton_clicked();
    void on_tableSelection_activated(int index);
};

#endif // DICTDIALOG_H
