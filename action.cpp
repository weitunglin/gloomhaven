#include "action.h"

Action::Action()
{

}

Action::Action(const Action& rhs) : skills(rhs.skills), detail(rhs.detail) {

}

void Action::setUp(QString s) {
    detail = s.trimmed();
    QTextStream ss(&s);
//    std::cout << "string:" << s.toStdString() << std::endl;
    QString key;
    int value;
    do {
        ss >> key >> value;
        if (key == "" && value == 0) break;
        qDebug() << "key:" << key << ",value:" << value;
        skills.push_back({key, value});
    } while (!ss.atEnd());
}

//QTextStream& operator>>(QTextStream& f, Action& rhs) {

//}

QString Action::toString() const {
    return detail;
}

std::vector<std::pair<QString, int>> Action::getSkills() {
    return skills;
}
