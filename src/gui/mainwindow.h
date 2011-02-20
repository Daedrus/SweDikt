#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "swedictionary.h"
#include "quiz.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    SweDictionary *sweDict;
    Quiz *quiz;

private slots:
    void on_actionAbout_triggered();
    void on_stackedWidget_currentChanged(int );
    void on_answerBox_returnPressed();
    void on_backButton_2_clicked();
    void on_nextButton_2_clicked();
    void on_answerButton_2_clicked();
    void on_detailedQuizButton_clicked();
    void on_addAdjectivesButton_clicked();
    void on_addVerbsButton_clicked();
    void on_addNounsButton_clicked();
    void on_openButton_clicked();
    void on_editAdjectivesButton_clicked();
    void on_editVerbsButton_clicked();
    void on_editNounsButton_clicked();
    void on_backButton_clicked();
    void on_answerButton_clicked();
    void on_nextButton_clicked();
    void on_simpleQuizButton_clicked();
};

#endif // MAINWINDOW_H
