#include "verbdialog.h"
#include "ui_verbdialog.h"

VerbDialog::VerbDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VerbDialog)
{
    ui->setupUi(this);
}

VerbDialog::~VerbDialog()
{
    delete ui;
}

QString VerbDialog::getImperativForm() {
    return ui->imperativField->text();
}

QString VerbDialog::getInfinitivForm() {
    return ui->infinitivField->text();
}

QString VerbDialog::getPresensForm() {
    return ui->presensField->text();
}

QString VerbDialog::getPreteritumForm() {
    return ui->preteritumField->text();
}

QString VerbDialog::getSupinumForm() {
    return ui->supinumField->text();
}

QString VerbDialog::getEngTrans() {
    return ui->engTransField->text();
}
