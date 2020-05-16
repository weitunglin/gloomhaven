#include "gloomhaven.h"

Gloomhaven::Gloomhaven(QObject *parent) : QObject(parent)
{

}

Gloomhaven::Gloomhaven(QObject *parent, std::string cFilename, std::string mFilename, int mode) : QObject(parent)
{
    characterFilename = cFilename;
    monsterFilename = mFilename;
    debugMode = mode;
    QFile file(QString::fromStdString(characterFilename));
    trace(characterFilename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cout << "file save" << std::endl;
        QTextStream f(&file);
        QString line = f.readLine();
        characterAmount = line.toInt();
        trace(characterAmount);
        characters = std::vector<Character>(characterAmount);
        for (int i = 0; i < characterAmount; ++i) {
            f >> characters[i];
        }
    }
    file.close();
}
