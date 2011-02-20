#include "quiz.h"

void Quiz::addQuestion(const Question &q)
{
    questions_.append(q);
    maximumScore_ += q.getValue();
}

void Quiz::advanceToNextQuestion()
{
   currentQuestion_++;
}

Question& Quiz::currentQuestion()
{
    return questions_[currentQuestion_];
}

bool Quiz::hasMoreQuestions()
{
    return (currentQuestion_ < questions_.size()) ? true : false;
}

void Quiz::validateQuestion()
{
    score_ += questions_[currentQuestion_].getScore();
}

quint16 Quiz::getScore()
{
    return score_;
}

quint16 Quiz::getMaximumScore()
{
    return maximumScore_;
}

quint16 Quiz::getCurrentQuestionNumber()
{
    return currentQuestion_ + 1;
}

quint16 Quiz::getNumberOfQuestions()
{
    return questions_.size();
}
