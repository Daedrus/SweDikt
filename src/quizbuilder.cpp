#include "quizbuilder.h"
#include "quiz.h"
#include "word.h"

namespace QuizBuilder {
    void addSimpleNounQuestions(Quiz &quiz, const SweDictionary &sweDict, const quint16 &count)
    {
        QString questionText;

        QList<Noun> &nouns = sweDict.getRandomNouns(count);

        for (int i = 0; i < nouns.size(); i++) {
            questionText.append("What is ");
            questionText.append(nouns.at(i).getEnglishTranslation());
            questionText.append(" in swedish?");

            const QString &singForm = nouns.at(i).getBestSingForm();
            QList<QString> answer;
            answer.append(singForm);
            const Question &q = Question(questionText, answer, Question::NOUN);

            quiz.addQuestion(q);

            questionText.clear();
        }

        delete &nouns;
    }

    void addDetailedNounQuestions(Quiz &quiz, const SweDictionary &sweDict, const quint16 &count)
    {
        QString questionText;

        QList<Noun> &nouns = sweDict.getRandomNouns(count);

        for (int i = 0; i < nouns.size(); i++) {
            questionText.append("What are the forms of \"");
            questionText.append(nouns.at(i).getEnglishTranslation());
            questionText.append("\" in swedish?");

            //const QString &singForm = nouns.at(i).getBestSingForm();
            QList<QString> answer;
            answer.append(nouns.at(i).getEnEtt());
            answer.append(nouns.at(i).getBestSingForm());
            answer.append(nouns.at(i).getObestSingForm());
            answer.append(nouns.at(i).getBestPlurForm());
            answer.append(nouns.at(i).getObestPlurForm());
            const Question &q = Question(questionText, answer, Question::NOUN);

            quiz.addQuestion(q);

            questionText.clear();
        }

        delete &nouns;
    }

    void addSimpleVerbQuestions(Quiz &quiz, const SweDictionary &sweDict, const quint16 &count)
    {
        QString questionText;

        QList<Verb> &verbs = sweDict.getRandomVerbs(count);

        for (int i = 0; i < verbs.size(); i++) {
            questionText.append("What is ");
            questionText.append(verbs.at(i).getEnglishTranslation());
            questionText.append(" in swedish?");

            const QString &infForm = verbs.at(i).getInfinitivForm();
            QList<QString> answer;
            answer.append(infForm);
            const Question &q = Question(questionText, answer, Question::VERB);

            quiz.addQuestion(q);

            questionText.clear();
        }

        delete &verbs;
    }

    void addDetailedVerbQuestions(Quiz &quiz, const SweDictionary &sweDict, const quint16 &count)
    {
        QString questionText;

        QList<Verb> &verbs = sweDict.getRandomVerbs(count);

        for (int i = 0; i < verbs.size(); i++) {
            questionText.append("What are the forms of \"");
            questionText.append(verbs.at(i).getEnglishTranslation());
            questionText.append("\" in swedish?");

            QList<QString> answer;
            answer.append(verbs.at(i).getImperativForm());
            answer.append(verbs.at(i).getInfinitivForm());
            answer.append(verbs.at(i).getPresensForm());
            answer.append(verbs.at(i).getPreteritumForm());
            answer.append(verbs.at(i).getSupinumForm());
            const Question &q = Question(questionText, answer, Question::VERB);

            quiz.addQuestion(q);

            questionText.clear();
        }

        delete &verbs;
    }

    void addSimpleAdjectiveQuestions(Quiz &quiz, const SweDictionary &sweDict, const quint16 &count)
    {
        QString questionText;

        QList<Adjective> &adjectives = sweDict.getRandomAdjectives(count);

        for (int i = 0; i < adjectives.size(); i++) {
            questionText.append("What is ");
            questionText.append(adjectives.at(i).getEnglishTranslation());
            questionText.append(" in swedish?");

            const QString &posForm = adjectives.at(i).getPositivForm();
            QList<QString> answer;
            answer.append(posForm);
            const Question &q = Question(questionText, answer, Question::ADJECTIVE);

            quiz.addQuestion(q);

            questionText.clear();
        }

        delete &adjectives;
    }

    void addDetailedAdjectiveQuestions(Quiz &quiz, const SweDictionary &sweDict, const quint16 &count)
    {
        QString questionText;

        QList<Adjective> &adjectives = sweDict.getRandomAdjectives(count);

        for (int i = 0; i < adjectives.size(); i++) {
            questionText.append("What are the forms of \"");
            questionText.append(adjectives.at(i).getEnglishTranslation());
            questionText.append("\" in swedish?");

            QList<QString> answer;
            answer.append(adjectives.at(i).getPositivForm());
            answer.append(adjectives.at(i).getKomparativForm());
            answer.append(adjectives.at(i).getSuperlativForm());
            const Question &q = Question(questionText, answer, Question::ADJECTIVE);

            quiz.addQuestion(q);

            questionText.clear();
        }

        delete &adjectives;
    }
}
