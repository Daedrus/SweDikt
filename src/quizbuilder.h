#ifndef QUIZBUILDER_H
#define QUIZBUILDER_H

#include "quiz.h"
#include "swedictionary.h"

/**
 * A collection of "static methods" that help create a quiz
 */
namespace QuizBuilder
{
    void addSimpleNounQuestions(Quiz &, const SweDictionary &, const quint16 &count);
    void addDetailedNounQuestions(Quiz &, const SweDictionary &, const quint16 &count);
    void addSimpleVerbQuestions(Quiz &, const SweDictionary &, const quint16 &count);
    void addDetailedVerbQuestions(Quiz &, const SweDictionary &, const quint16 &count);
    void addSimpleAdjectiveQuestions(Quiz &, const SweDictionary &, const quint16 &count);
    void addDetailedAdjectiveQuestions(Quiz &, const SweDictionary &, const quint16 &count);
}
#endif // QUIZBUILDER_H
