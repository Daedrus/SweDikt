#ifndef QUESTION_H
#define QUESTION_H

#include <QString>
#include <QList>
#include <QBitArray>

/**
 * The Question class is the fundamental component of a quiz.
 * It can have one or more answers, different values,
 * and subclasses can define their own method of scoring.
 */
class Question
{
public:
    /**
     * Question constructor
     */
    Question(const QString &text,
             const QList<QString> &answers,
             quint16 questionType,
             quint16 value = 1)
                 :
                 text_(text),
                 answers_(answers),
                 value_(value),
                 questionType_(questionType) {}

    enum TYPE {
        NOUN,
        VERB,
        ADJECTIVE
    };

    /**
     * Save the user's answers to this question
     */
    void setUserAnswers(QList<QString> &userAnswers);

    /**
     * @return A bit array of size equal to the number of answers
     *         the user should give. If answer X is correct, then
     *         the bit on position X will be set
     */
    QBitArray validAnswers();

    /**
     * @return How much the user scored in this question, according
     *         to the question's scoring policy
     */
    virtual quint16 getScore();

    /**
     * Getter methods
     */
    QString getText() const;
    QList<QString> getAnswers() const;
    quint16 getValue() const;
    quint16 getQuestionType() const;
    bool isAnswered();

private:
    QString text_;
    QList<QString> answers_;
    QList<QString> userAnswers_;
    quint16 value_;
    quint16 questionType_;
};

#endif // QUESTION_H
