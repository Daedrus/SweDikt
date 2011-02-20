#include "word.h"

QString Word::getEnglishTranslation() const
{
    return eng_trans_;
}

QString Noun::getEnEtt() const
{
    return en_ett_;
}

QString Noun::getBestSingForm() const
{
    return best_sing_;
}

QString Noun::getObestSingForm() const
{
    return obest_sing_;
}

QString Noun::getBestPlurForm() const
{
    return best_plur_;
}

QString Noun::getObestPlurForm() const
{
    return obest_plur_;
}

QString Verb::getImperativForm() const
{
    return imperativ_;
}

QString Verb::getInfinitivForm() const
{
    return infinitiv_;
}

QString Verb::getPresensForm() const
{
    return presens_;
}

QString Verb::getPreteritumForm() const
{
    return preteritum_;
}

QString Verb::getSupinumForm() const
{
    return supinum_;
}

QString Adjective::getPositivForm() const
{
    return positiv_;
}

QString Adjective::getKomparativForm() const
{
    return komparativ_;
}

QString Adjective::getSuperlativForm() const
{
    return superlativ_;
}
