#include "noundialog.h"
#include "ui_noundialog.h"

NounDialog::NounDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NounDialog)
{
    ui->setupUi(this);
}

NounDialog::~NounDialog()
{
    delete ui;
}

QString NounDialog::getEnEtt() {
    return ui->enEttField->currentText();
}

QString NounDialog::getBestSingForm() {
    return ui->bestSingField->text();
}

QString NounDialog::getObestSingForm() {
    return ui->obestSingField->text();
}

QString NounDialog::getBestPlurForm() {
    return ui->bestPlurField->text();
}

QString NounDialog::getObestPlurForm() {
    return ui->obestPlurField->text();
}

QString NounDialog::getEngTrans() {
    return ui->engTransField->text();
}
