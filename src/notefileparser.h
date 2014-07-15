#ifndef NOTEFILEPARSER_H
#define NOTEFILEPARSER_H

#include "mainview/notechart.h"

class Song;
class QTextStream;

class NoteFileParser
{
public:
    NoteFileParser(QString filePath,Song *song);

    bool parse(Ts::Course loadCourse);

private:
    QString getLine(QTextStream& input);
    QString filePath_;
    Song *song_;
};

#endif // NOTEFILEPARSER_H
