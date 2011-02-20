#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "quizbuilder.h"
#include <QFileDialog>
#include <QDebug>
#include <QSqlTableModel>
#include <QTableView>
#include "noundialog.h"
#include "verbdialog.h"
#include "adjectivedialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sweDict(0)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete sweDict;
}

/**
 * Main Window actions
 */
void MainWindow::on_openButton_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Choose database"), "", 0, 0, QFileDialog::DontConfirmOverwrite);

    try {
        sweDict = new SweDictionary(path);
    } catch (int error) {
        ui->statusBar->showMessage("Could not open dictionary");
        return;
    }

    ui->statusBar->showMessage("Dictionary opened");
}

void MainWindow::on_simpleQuizButton_clicked()
{
    if (sweDict == 0) {
        QMessageBox::warning(this, tr("Warning"),
                             "No dictionary has been loaded",
                             QMessageBox::Ok);
        return;
    }

    quiz = new Quiz();
    QuizBuilder::addSimpleNounQuestions(*quiz, *sweDict, 3);
    QuizBuilder::addSimpleVerbQuestions(*quiz, *sweDict, 3);
    QuizBuilder::addSimpleAdjectiveQuestions(*quiz, *sweDict, 3);

    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_detailedQuizButton_clicked()
{
    if (sweDict == 0) {
        QMessageBox::warning(this, tr("Warning"),
                             "No dictionary has been loaded",
                             QMessageBox::Ok);
        return;
    }

    quiz = new Quiz();
    QuizBuilder::addDetailedNounQuestions(*quiz, *sweDict, 3);
    QuizBuilder::addDetailedVerbQuestions(*quiz, *sweDict, 3);
    QuizBuilder::addDetailedAdjectiveQuestions(*quiz, *sweDict, 3);

    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_editNounsButton_clicked()
{
    if (sweDict == 0) {
        QMessageBox::warning(this, tr("Warning"),
                             "No dictionary has been loaded",
                             QMessageBox::Ok);
        return;
    }

    QSqlTableModel &model = sweDict->getModel(this, "noun");

    QTableView *view = new QTableView;
    view->setModel(&model);
    view->show();
}

void MainWindow::on_editVerbsButton_clicked()
{
    if (sweDict == 0) {
        QMessageBox::warning(this, tr("Warning"),
                             "No dictionary has been loaded",
                             QMessageBox::Ok);
        return;
    }

    QSqlTableModel &model = sweDict->getModel(this, "verb");

    QTableView *view = new QTableView;
    view->setModel(&model);
    view->show();
}

void MainWindow::on_editAdjectivesButton_clicked()
{
    if (sweDict == 0) {
        QMessageBox::warning(this, tr("Warning"),
                             "No dictionary has been loaded",
                             QMessageBox::Ok);
        return;
    }

    QSqlTableModel &model = sweDict->getModel(this, "adjective");

    QTableView *view = new QTableView;
    view->setModel(&model);
    view->show();
}

void MainWindow::on_addNounsButton_clicked()
{
    NounDialog nounDialog;

    if (nounDialog.exec() == QDialog::Accepted) {
        sweDict->addNoun(nounDialog.getEnEtt(),
                         nounDialog.getBestSingForm(),
                         nounDialog.getObestSingForm(),
                         nounDialog.getBestPlurForm(),
                         nounDialog.getObestSingForm(),
                         nounDialog.getEngTrans());
    }
}

void MainWindow::on_addVerbsButton_clicked()
{
    VerbDialog verbDialog;

    if (verbDialog.exec() == QDialog::Accepted) {
        sweDict->addVerb(verbDialog.getImperativForm(),
                         verbDialog.getInfinitivForm(),
                         verbDialog.getPresensForm(),
                         verbDialog.getPreteritumForm(),
                         verbDialog.getSupinumForm(),
                         verbDialog.getEngTrans());
    }
}

void MainWindow::on_addAdjectivesButton_clicked()
{
    AdjectiveDialog adjectiveDialog;

    if (adjectiveDialog.exec() == QDialog::Accepted) {
        sweDict->addAdjective(adjectiveDialog.getPositivForm(),
                              adjectiveDialog.getKomparativForm(),
                              adjectiveDialog.getSuperlativForm(),
                              adjectiveDialog.getEngTrans());
    }
}

/**
 * Simple Quiz actions
 */
void MainWindow::on_nextButton_clicked()
{
    QString message;
    if (quiz->hasMoreQuestions()) {
        message.append("Question ");
        message.append(QString::number(quiz->getCurrentQuestionNumber()));
        message.append(" out of ");
        message.append(QString::number(quiz->getNumberOfQuestions()));

        ui->answerButton->show();

        Question &q = quiz->currentQuestion();

        ui->answerBox->clear();
        ui->answerBox->setFocus();
        ui->nextButton->hide();
        ui->feedbackText->clear();
        ui->questionBox->setText(q.getText());
        ui->statusBar->showMessage(message);
    } else {
        message.append("Quiz is over :) You've got ");
        message.append(QString::number(quiz->getScore()));
        message.append(" out of ");
        message.append(QString::number(quiz->getMaximumScore()));
        message.append(" points");
        QMessageBox::warning(this, tr("Warning"),
                             message,
                             QMessageBox::Ok);
        return;
    }
}

void MainWindow::on_answerButton_clicked()
{

    ui->answerButton->hide();

    QList<QString> userAnswers;
    userAnswers.append(ui->answerBox->text());

    quiz->currentQuestion().setUserAnswers(userAnswers);

    if (quiz->currentQuestion().getScore() != 0) {
        ui->feedbackText->setText(tr("Correct!"));
        quiz->validateQuestion();
    } else {
        ui->feedbackText->setText(tr("Wrong! The answer was ") + quiz->currentQuestion().getAnswers().at(0));
    }

    ui->nextButton->show();
    quiz->advanceToNextQuestion();
}

void MainWindow::on_backButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

    delete quiz;
}

/**
 * Detailed Quiz actions
 */
void MainWindow::on_nextButton_2_clicked()
{
    QString message;
    if (quiz->hasMoreQuestions()) {
        message.append("Question ");
        message.append(QString::number(quiz->getCurrentQuestionNumber()));
        message.append(" out of ");
        message.append(QString::number(quiz->getNumberOfQuestions()));

        ui->answerButton_2->show();
        ui->nextButton_2->hide();

        ui->feedback_1->clear();
        ui->feedback_2->clear();
        ui->feedback_3->clear();
        ui->feedback_4->clear();
        ui->feedback_5->clear();

        ui->statusBar->showMessage(message);

        Question &q = quiz->currentQuestion();

        switch(q.getQuestionType())
        {
        case(Question::NOUN) :
            ui->label_1->setText("en/ett");
            ui->label_2->setText("bestämd singular");
            ui->label_3->setText("obestämd singular");
            ui->label_4->setText("bestämd plural");
            ui->label_5->setText("obestämd plural");
            ui->answerBox_4->show();
            ui->answerBox_5->show();
            break;
        case(Question::VERB) :
            ui->label_1->setText("imperativ");
            ui->label_2->setText("infinitiv");
            ui->label_3->setText("presens");
            ui->label_4->setText("preteritum");
            ui->label_5->setText("supinum");
            ui->answerBox_4->show();
            ui->answerBox_5->show();
            break;
        case(Question::ADJECTIVE) :
            ui->label_1->setText("positiv");
            ui->label_2->setText("komparativ");
            ui->label_3->setText("superlativ");
            ui->label_4->hide();
            ui->label_5->hide();
            ui->answerBox_4->hide();
            ui->answerBox_5->hide();
            break;
        }

        ui->questionBox_2->setText(q.getText());

        ui->answerBox_1->clear();
        ui->answerBox_1->setFocus();
        ui->answerBox_2->clear();
        ui->answerBox_3->clear();
        ui->answerBox_4->clear();
        ui->answerBox_5->clear();

        ui->nextButton_2->hide();

    } else {
        message.append("Quiz is over :) You've got ");
        message.append(QString::number(quiz->getScore()));
        message.append("/");
        message.append(QString::number(quiz->getMaximumScore()));
        message.append(" points");
        QMessageBox::warning(this, tr("Warning"),
                             message,
                             QMessageBox::Ok);
        return;
    }
}

void MainWindow::on_answerButton_2_clicked()
{
    ui->answerButton_2->hide();

    QList<QString> userAnswers;
    Question &q = quiz->currentQuestion();

    switch(q.getQuestionType())
    {
        case(Question::NOUN) :
            userAnswers.append(ui->answerBox_1->text());
            userAnswers.append(ui->answerBox_2->text());
            userAnswers.append(ui->answerBox_3->text());
            userAnswers.append(ui->answerBox_4->text());
            userAnswers.append(ui->answerBox_5->text());
            break;
        case(Question::VERB) :
            userAnswers.append(ui->answerBox_1->text());
            userAnswers.append(ui->answerBox_2->text());
            userAnswers.append(ui->answerBox_3->text());
            userAnswers.append(ui->answerBox_4->text());
            userAnswers.append(ui->answerBox_5->text());
            break;
        case(Question::ADJECTIVE) :
            userAnswers.append(ui->answerBox_1->text());
            userAnswers.append(ui->answerBox_2->text());
            userAnswers.append(ui->answerBox_3->text());
            break;
    }

    q.setUserAnswers(userAnswers);

    QBitArray validAnswers = q.validAnswers();

    switch(q.getQuestionType())
    {
        case(Question::NOUN) :
            if (validAnswers.at(0)) {
                ui->feedback_1->setText("Correct!");
            } else {
                ui->feedback_1->setText("Wrong! it is " + q.getAnswers().at(0));
            }
            if (validAnswers.at(1)) {
                ui->feedback_2->setText("Correct!");
            } else {
                ui->feedback_2->setText("Wrong! it is " + q.getAnswers().at(1));
            }
            if (validAnswers.at(2)) {
                ui->feedback_3->setText("Correct!");
            } else {
                ui->feedback_3->setText("Wrong! it is " + q.getAnswers().at(2));
            }
            if (validAnswers.at(3)) {
                ui->feedback_4->setText("Correct!");
            } else {
                ui->feedback_4->setText("Wrong! it is " + q.getAnswers().at(3));
            }
            if (validAnswers.at(4)) {
                ui->feedback_5->setText("Correct!");
            } else {
                ui->feedback_5->setText("Wrong! it is " + q.getAnswers().at(4));
            }
            break;
        case(Question::VERB) :
            if (validAnswers.at(0)) {
                ui->feedback_1->setText("Correct!");
            } else {
                ui->feedback_1->setText("Wrong! it is " + q.getAnswers().at(0));
            }
            if (validAnswers.at(1)) {
                ui->feedback_2->setText("Correct!");
            } else {
                ui->feedback_2->setText("Wrong! it is " + q.getAnswers().at(1));
            }
            if (validAnswers.at(2)) {
                ui->feedback_3->setText("Correct!");
            } else {
                ui->feedback_3->setText("Wrong! it is " + q.getAnswers().at(2));
            }
            if (validAnswers.at(3)) {
                ui->feedback_4->setText("Correct!");
            } else {
                ui->feedback_4->setText("Wrong! it is " + q.getAnswers().at(3));
            }
            if (validAnswers.at(4)) {
                ui->feedback_5->setText("Correct!");
            } else {
                ui->feedback_5->setText("Wrong! it is " + q.getAnswers().at(4));
            }
            break;
        case(Question::ADJECTIVE) :
            if (validAnswers.at(0)) {
                ui->feedback_1->setText("Correct!");
            } else {
                ui->feedback_1->setText("Wrong! it is " + q.getAnswers().at(0));
            }
            if (validAnswers.at(1)) {
                ui->feedback_2->setText("Correct!");
            } else {
                ui->feedback_2->setText("Wrong! it is " + q.getAnswers().at(1));
            }
            if (validAnswers.at(2)) {
                ui->feedback_3->setText("Correct!");
            } else {
                ui->feedback_3->setText("Wrong! it is " + q.getAnswers().at(2));
            }
            break;
    }

    quiz->validateQuestion();

    ui->nextButton_2->show();
    quiz->advanceToNextQuestion();
}

void MainWindow::on_backButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

    delete quiz;
}

void MainWindow::on_answerBox_returnPressed()
{
    if (!quiz->currentQuestion().isAnswered()) {
        ui->answerButton->click();
    }
}

void MainWindow::on_stackedWidget_currentChanged(int window)
{
    switch(window) {
    case 0:
        ui->statusBar->clearMessage();
        break;
    case 1:
        ui->statusBar->clearMessage();
        on_nextButton_clicked();
        break;
    case 2:
        ui->statusBar->clearMessage();
        on_nextButton_2_clicked();
        break;
    }
}

/**
 * Menu actions
 */
void MainWindow::on_actionAbout_triggered()
{
    QMessageBox* aboutBox = new QMessageBox();
    aboutBox->setAttribute(Qt::WA_DeleteOnClose);

    aboutBox->setText("SweDikt is a small application that can be used when"
                     " you're starting to learn swedish. You can use it to"
                     " enter words in the dictionary as you learn them and"
                     " then play small quizzes that test your knowledge."
                     "\n\n"
                     "To start, click on Open Dictionary. Here you can select "
                     "an existing dictionary, or create a new one by typing whatever "
                     "name you want in the text field. "
                     "\n\n"
                     "After you've opened a dictionary, you can start adding words "
                     "to it or edit the words that are already present in it. Or you "
                     "have enough words in your dictionary you can just skip this step "
                     "and start playing quizzes."
                     "\n\n"
                     "The simple quiz contains three noun questions where the "
                     "answer is the \"singular obestämt\" form, three verb questions "
                     "where the answer is the \"infinitiv\" form and three adjective "
                     "questions where the answer is the \"positiv\" form. The words are "
                     "selected randomly from the dictionary you've opened."
                     "\n\n"
                     "The detailed quiz contains the same number of questions "
                     "as the simple quiz however the answers have to cover all forms."
                     "\n\n"
                     "Enjoy!"
                     "\n\n"
                     "Andrei Faur");

    aboutBox->setModal(false);
    aboutBox->open();
}
