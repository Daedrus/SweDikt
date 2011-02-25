#ifndef SWEDICTIONARY_H
#define SWEDICTIONARY_H

#include <QtSql/QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QList>
#include <QVariant>
#include "word.h"
#include "swedictionarytablemodel.h"

/**
 * The core class of the application, it abstracts the connection
 * to the database so it can be viewed as a source of Noun, Verb
 * and Adjective objects.
 */
class SweDictionary
{
public:
    /**
     * SweDictionary constructor
     */
    SweDictionary(QString &dbName);

    /**
     * SweDictionary destructor
     */
    ~SweDictionary();

    /**
     * @return A list of count random nouns from the database
     */
    QList<Noun>& getRandomNouns (quint16 count) const;

    /**
     * @return A list of count random verbs from the database
     */
    QList<Verb>& getRandomVerbs (quint16 count) const;

    /**
     * @return A list of count random adjectives from the database
     */
    QList<Adjective>& getRandomAdjectives (quint16 count) const;

    /**
     * Add a given noun to the database
     */
    void addNoun(QString enEtt,
                 QString bestSingForm, QString obestSingForm,
                 QString bestPlurForm, QString obestPlurForm,
                 QString engTrans);

    /**
     * Add a given verb to the database
     */
    void addVerb(QString imperativ, QString infinitiv, QString presens,
                 QString preteritum, QString supinum, QString engTrans);

    /**
     * Add a given adjective to the database
     */
    void addAdjective(QString positiv, QString komparativ,
                      QString superlativ, QString engTrans);

    /**
     * :KLUDGE: bleah, yuck, I have to get rid of this.
     */
    SweDictionaryTableModel* getModel(QObject *parent, QString table);

private:
    QSqlDatabase db_;
    QList<QSqlQuery> preparedQueries;
    enum queries {nounAdd, nounSearch, nounQuiz,
                  verbAdd, verbSearch, verbQuiz,
                  adjAdd, adjSearch, adjQuiz};
    SweDictionaryTableModel *model_;
};

#endif // SWEDICTIONARY_H
