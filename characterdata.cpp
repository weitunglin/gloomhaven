#include "characterdata.h"

CharacterData::CharacterData()
{

}

QTextStream& operator>>(QTextStream& f, CharacterData& rhs) {
    return f;
}
