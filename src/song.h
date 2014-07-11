#ifndef SONG_H
#define SONG_H

#include <QList>
#include <QHash>
#include <QString>
#include "notefileparser.h"
#include "stable.h"

class NoteChart;
class QGraphicsItem;

// Song is the most top container
// Song -> NoteChart -> Measure -> Note
class Song
{
public:
    Song(QString noteFile);

    NoteChart *getChart(Ts::Course course);

    QString title() const { return title_; }
    void setTitle(const QString &title) { title_ = title; }

    QString subtitle() const { return subtitle_; }
    void setSubtitle(const QString &subtitle) { subtitle_ = subtitle; }

    int side() const { return side_; }
    void setSide(int side) { side_ = side; }

    qreal bpm() const { return bpm_; }
    void setBpm(const qreal &bpm) { bpm_ = bpm; }

    QString wave() const { return wave_; }
    void setWave(const QString &wave) { wave_ = wave; }

    qreal offset() const { return offset_; }
    void setOffset(const qreal &offset) { offset_ = offset; }

    qreal demoStart() const { return demoStart_; }
    void setDemoStart(const qreal &demoStart) { demoStart_ = demoStart; }

    NoteFileParser &parser() { return parser_; }

private:
    NoteFileParser parser_;
    QString title_;
    QString subtitle_;
    int side_;
    qreal bpm_;
    QString wave_;
    qreal offset_;
    qreal demoStart_;
    QHash<Ts::Course,NoteChart*> noteCharts_;
    QGraphicsItem *parentItem_;
};

#endif // SONG_H
