#include "characterdata.h"

CharacterData::CharacterData(QObject *parent) : QObject(parent)
{

}

QTextStream& operator>>(QTextStream& f, CharacterData& rhs) {
    return f;
}
