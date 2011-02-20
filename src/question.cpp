#include "question.h"

QString Question::getText() const
{
    return text_;
}

QList<QString> Question::getAnswers() const
{
    return answers_;
}

quint16 Question::getValue() const
{
    return value_;
}

quint16 Question::getQuestionType() const
{
    return questionType_;
}

void Question::setUserAnswers(QList<QString> &userAnswers)
{
    userAnswers_ = userAnswers;
    answered_ = true;
}

QBitArray Question::validAnswers()
{
    QBitArray answerBitField(answers_.size());
    for (int i = 0; i < answers_.size(); i++) {
        if (answers_.at(i) == userAnswers_.at(i))
            answerBitField.setBit(i);
    }

    return answerBitField;
}

quint16 Question::getScore()
{
    return (validAnswers().count(true) == answers_.size()) ? value_ : 0;
}

bool Question::isAnswered()
{
    return answered_;
}


