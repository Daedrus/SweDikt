#ifndef WORD_H
#define WORD_H

#include <QString>

/**
 * Convenience classes for the three basic word types
 * in the dictionary. :TODO: Perhaps convert these to
 * simple structs in the future.
 */
class Word
{
public:
    QString getEnglishTranslation() const;

protected:
    Word(QString eng_trans) : eng_trans_(eng_trans) {}

private:
    QString eng_trans_;
};

class Noun : public Word
{
public:
    Noun (QString en_ett, QString best_sing, QString obest_sing,
          QString best_plur, QString obest_plur, QString eng_trans)
              : Word(eng_trans), en_ett_(en_ett),
                best_sing_(best_sing), obest_sing_(obest_sing),
                best_plur_(best_plur), obest_plur_(obest_plur) {}

    QString getEnEtt() const;
    QString getBestSingForm() const;
    QString getObestSingForm() const;
    QString getBestPlurForm() const;
    QString getObestPlurForm() const;

private:
    QString en_ett_;
    QString best_sing_;
    QString obest_sing_;
    QString best_plur_;
    QString obest_plur_;
};

class Verb : public Word
{
public:
    Verb (QString imperativ, QString infinitiv, QString presens,
          QString preteritum, QString supinum, QString eng_trans)
              : Word(eng_trans), imperativ_(imperativ), infinitiv_(infinitiv),
                presens_(presens), preteritum_(preteritum), supinum_(supinum) {}

    QString getImperativForm() const;
    QString getInfinitivForm() const;
    QString getPresensForm() const;
    QString getPreteritumForm() const;
    QString getSupinumForm() const;

private:
    QString imperativ_;
    QString infinitiv_;
    QString presens_;
    QString preteritum_;
    QString supinum_;
};

class Adjective : public Word
{
public:
    Adjective (QString positiv, QString komparativ,
               QString superlativ, QString eng_trans)
                   : Word(eng_trans), positiv_(positiv),
                     komparativ_(komparativ), superlativ_(superlativ) {}

    QString getPositivForm() const;
    QString getKomparativForm() const;
    QString getSuperlativForm() const;

private:
    QString positiv_;
    QString komparativ_;
    QString superlativ_;
};

#endif // WORD_H
