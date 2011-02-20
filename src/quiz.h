#ifndef QUIZ_H
#define QUIZ_H

#include <QList>
#include "question.h"

/**
 * The Quiz class helps to create the notion of a quiz.
 * It contains multiple questions, how much the user
 * scored and the maximum score.
 */
class Quiz
{
public:
    /**
     * Quiz constructor
     */
    Quiz() : currentQuestion_(0), score_(0), maximumScore_(0) {}

    /**
     * Add a question to this quiz.
     */
    void addQuestion(const Question &q);

    /**
     * Advance to the quiz's next question
     */
    void advanceToNextQuestion();

    /**
     * Get the quiz's current question
     */
    Question& currentQuestion();

    /**
     * @return true if there is a next question, false otherwise
     */
    bool hasMoreQuestions();

    /**
     * Adds the current question's score to the quiz's
     * score if the question has been answered correctly
     */
    void validateQuestion();

    /**
     * Getter methods
     */
    quint16 getScore();
    quint16 getMaximumScore();
    quint16 getCurrentQuestionNumber();
    quint16 getNumberOfQuestions();

private:
    QList<Question> questions_;
    quint16 currentQuestion_;
    quint16 score_;
    quint16 maximumScore_;
};

#endif // QUIZ_H
