#ifndef NOTEFILEPARSER_H
#define NOTEFILEPARSER_H

#include "notechart.h"

class Song;
class NoteFileParser
{
public:
    NoteFileParser(QString filePath,Song *song);

    bool parse();

protected:
    QString filePath_;
    Song *song_;
};

#endif // NOTEFILEPARSER_H
