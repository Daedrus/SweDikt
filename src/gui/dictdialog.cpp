#include "dictdialog.h"
#include "ui_dictdialog.h"
#include <QDebug>

DictDialog::DictDialog(QWidget *parent, SweDictionary *sweDict) :
    QDialog(parent),
    ui(new Ui::DictDialog),
    sweDict_(sweDict),
    currentModel_(0)
{
    ui->setupUi(this);
    on_tableSelection_activated(0);
}

DictDialog::~DictDialog()
{
    if (currentModel_ != 0)
        delete currentModel_;

    delete ui;
}

void DictDialog::on_tableSelection_activated(int index)
{
    if (currentModel_ != 0)
        delete currentModel_;

    switch(index) {
    case 0:
        currentModel_ = sweDict_->getModel(this, "noun");
        break;
    case 1:
        currentModel_ = sweDict_->getModel(this, "verb");
        break;
    case 2:
        currentModel_ = sweDict_->getModel(this, "adjective");
        break;
    }

    ui->tableView->setModel(currentModel_);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->show();
}

void DictDialog::on_deleteRowButton_clicked()
{
    if (ui->tableView->selectionModel()->currentIndex().isValid())
        currentModel_->removeRow(ui->tableView->selectionModel()->currentIndex().row());
}

void DictDialog::on_saveButton_clicked()
{
    currentModel_->submitAll();
}
