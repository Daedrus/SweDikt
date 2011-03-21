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

void DictDialog::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier) {
        if (event->key() & Qt::Key_D) {
            if (ui->tableView->selectionModel()->currentIndex().isValid()) {
                currentModel_->removeRow(ui->tableView->selectionModel()->currentIndex().row());
            }
        }
    }

    QWidget::keyPressEvent(event);
}

void DictDialog::closeEvent(QCloseEvent *event)
{
    currentModel_->submitAll();
    event->accept();
}

void DictDialog::on_tableSelection_activated(int index)
{
    if (currentModel_ != 0) {
        currentModel_->submitAll();
        delete currentModel_;
    }

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
    ui->tableView->setSortingEnabled(true);
    ui->tableView->show();
}

void DictDialog::on_searchButton_clicked()
{
    QString whereClause;

    currentModel_->submitAll();

    if (ui->searchPattern->text().isEmpty()) {
        currentModel_->setFilter("");
        return;
    }

    for (int i = 1; i < currentModel_->columnCount(); i++) {
        whereClause.append(currentModel_->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
        whereClause.append("= '");
        whereClause.append(ui->searchPattern->text());
        whereClause.append("'");
        if (i != currentModel_->columnCount() - 1) {
            whereClause.append(" OR ");
        }
    }

    currentModel_->setFilter(whereClause);
}
