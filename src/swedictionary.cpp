#include "swedictionary.h"
#include <QDebug>
#include <QSqlError>

SweDictionary::SweDictionary(QString &dbName)
{
    QSqlDatabase db_ = QSqlDatabase::addDatabase("QSQLITE");
    db_.setDatabaseName(dbName);
    if (!db_.open()) {
        throw 42;
    }

    QSqlQuery createNounTable("CREATE TABLE IF NOT EXISTS noun("
                              "noun_id INTEGER PRIMARY KEY,"
                              "en_ett TEXT,"
                              "best_sing TEXT,"
                              "obest_sing TEXT,"
                              "best_plur TEXT,"
                              "obest_plur TEXT,"
                              "eng_trans TEXT)");
    createNounTable.exec();

    QSqlQuery createVerbTable("CREATE TABLE IF NOT EXISTS verb("
                              "verb_id INTEGER PRIMARY KEY,"
                              "imperativ TEXT,"
                              "infinitiv TEXT,"
                              "presens TEXT,"
                              "preteritum TEXT,"
                              "supinum TEXT,"
                              "eng_trans TEXT)");
    createVerbTable.exec();

    QSqlQuery createAdjectiveTable("CREATE TABLE IF NOT EXISTS adjective("
                                   "adjective_id INTEGER PRIMARY KEY,"
                                   "positiv TEXT,"
                                   "komparativ TEXT,"
                                   "superlativ TEXT,"
                                   "eng_trans TEXT)");
    createAdjectiveTable.exec();

    QSqlQuery query;
    query.prepare("INSERT INTO noun (en_ett, best_sing, obest_sing,"
                  "                  best_plur, obest_plur, eng_trans)"
                  "VALUES (?, ?, ?, ?, ?, ?)");
    preparedQueries.append(query);

    query.prepare("SELECT * FROM noun"
                  "WHERE best_sing = :term OR obest_sing = :term OR"
                  "      best_plur = :term OR obest_plur = :term OR"
                  "      eng_trans = :term");
    preparedQueries.append(query);

    query.prepare("SELECT * FROM noun ORDER BY RANDOM() LIMIT ?");
    preparedQueries.append(query);

    query.prepare("INSERT INTO verb (imperativ, infinitiv, presens,"
                  "                  preteritum, supinum, eng_trans)"
                  "VALUES (?, ?, ?, ?, ?, ?)");
    preparedQueries.append(query);

    query.prepare("SELECT * FROM verb"
                  "WHERE imperativ = :term OR infinitiv = :term OR"
                  "      presens = :term OR preteritum = :term OR"
                  "      supinum = :term OR eng_trans = :term");
    preparedQueries.append(query);

    query.prepare("SELECT * FROM verb ORDER BY RANDOM() LIMIT ?");
    preparedQueries.append(query);

    query.prepare("INSERT INTO adjective (positiv, komparativ,"
                  "                       superlativ, eng_trans)"
                  "VALUES (?, ?, ?, ?)");
    preparedQueries.append(query);

    query.prepare("SELECT * FROM adjective"
                  "WHERE positiv = :term OR komparativ = :term OR"
                  "      superlativ = :term OR eng_trans = :term");
    preparedQueries.append(query);

    query.prepare("SELECT * FROM adjective ORDER BY RANDOM() LIMIT ?");
    preparedQueries.append(query);
}

SweDictionary::~SweDictionary()
{
    QString connection;

    connection = db_.connectionName();
    db_.close();

    QSqlDatabase::removeDatabase(connection);

}

QList<Noun>& SweDictionary::getRandomNouns(quint16 count) const
{
    Noun *noun;
    QList<Noun> *nouns = new QList<Noun>();

    QSqlQuery query = preparedQueries.at(nounQuiz);
    query.bindValue(0, count);

    query.exec();

    while (query.next()) {
        noun = new Noun(query.value(1).toString(),
                        query.value(2).toString(),
                        query.value(3).toString(),
                        query.value(4).toString(),
                        query.value(5).toString(),
                        query.value(6).toString());

        nouns->append(*noun);

        delete noun;
    }

    query.clear();

    return *nouns;
}

QList<Verb>& SweDictionary::getRandomVerbs(quint16 count) const
{
    Verb *verb;
    QList<Verb> *verbs = new QList<Verb>();

    QSqlQuery query = preparedQueries.at(verbQuiz);
    query.bindValue(0, count);

    query.exec();

    while (query.next()) {
        verb = new Verb(query.value(1).toString(),
                        query.value(2).toString(),
                        query.value(3).toString(),
                        query.value(4).toString(),
                        query.value(5).toString(),
                        query.value(6).toString());

        verbs->append(*verb);

        delete verb;
    }

    query.clear();

    return *verbs;
}

QList<Adjective>& SweDictionary::getRandomAdjectives(quint16 count) const
{
    Adjective *adjective;
    QList<Adjective> *adjectives = new QList<Adjective>();

    QSqlQuery query = preparedQueries.at(adjQuiz);
    query.bindValue(0, count);

    query.exec();

    while (query.next()) {
        adjective = new Adjective(query.value(1).toString(),
                                  query.value(2).toString(),
                                  query.value(3).toString(),
                                  query.value(4).toString());

        adjectives->append(*adjective);

        delete adjective;
    }

    query.clear();

    return *adjectives;
}

SweDictionaryTableModel* SweDictionary::getModel(QObject *parent, QString table)
{
    model_ = new SweDictionaryTableModel(parent, db_);
    model_->setTable(table);
    model_->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_->select();

    return model_;
}

void SweDictionary::addNoun(QString enEtt,
                            QString bestSingForm, QString obestSingForm,
                            QString bestPlurForm, QString obestPlurForm,
                            QString engTrans)
{
    QSqlQuery query = preparedQueries.at(nounAdd);
    query.bindValue(0, enEtt);
    query.bindValue(1, bestSingForm);
    query.bindValue(2, obestSingForm);
    query.bindValue(3, bestPlurForm);
    query.bindValue(4, obestPlurForm);
    query.bindValue(5, engTrans);

    query.exec();

    query.clear();
}

void SweDictionary::addVerb(QString imperativ, QString infinitiv,
                            QString presens, QString preteritum,
                            QString supinum, QString engTrans)
{
    QSqlQuery query = preparedQueries.at(verbAdd);
    query.bindValue(0, imperativ);
    query.bindValue(1, infinitiv);
    query.bindValue(2, presens);
    query.bindValue(3, preteritum);
    query.bindValue(4, supinum);
    query.bindValue(5, engTrans);

    query.exec();

    query.clear();
}

void SweDictionary::addAdjective(QString positiv, QString komparativ,
                                 QString superlativ, QString engTrans)
{
    QSqlQuery query = preparedQueries.at(adjAdd);
    query.bindValue(0, positiv);
    query.bindValue(1, komparativ);
    query.bindValue(2, superlativ);
    query.bindValue(3, engTrans);

    query.exec();

    query.clear();
}
