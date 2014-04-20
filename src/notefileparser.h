#ifndef NOTEFILEPARSER_H
#define NOTEFILEPARSER_H

#include "notechart.h"

class NoteFileParser
{
public:
    NoteFileParser(QString filePath);

    void loadSongInfo();
    void loadChart(NoteChart *noteChart);

protected:
    QString filePath_;
};

#endif // NOTEFILEPARSER_H
