#include "adjectivedialog.h"
#include "ui_adjectivedialog.h"

AdjectiveDialog::AdjectiveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdjectiveDialog)
{
    ui->setupUi(this);
}

AdjectiveDialog::~AdjectiveDialog()
{
    delete ui;
}

QString AdjectiveDialog::getPositivForm()
{
    return ui->positivField->text();
}

QString AdjectiveDialog::getKomparativForm()
{
    return ui->komparativField->text();
}

QString AdjectiveDialog::getSuperlativForm()
{
    return ui->superlativField->text();
}

QString AdjectiveDialog::getEngTrans()
{
    return ui->engTransField->text();
}
