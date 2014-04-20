#ifndef SONG_H
#define SONG_H

#include <QList>

class NoteChart;
class NoteFileParser;

class Song
{
public:
    Song(QString filePath);

    int chartCount() const;
    NoteChart* chartAt(int index) const;

    QString title() const;
    void setTitle(const QString &title);

    int side() const;
    void setSide(int side);

    qreal bpm() const;
    void setBpm(const qreal &bpm);

    QString wave() const;
    void setWave(const QString &wave);

    qreal offset() const;
    void setOffset(const qreal &offset);

    qreal demoStart() const;
    void setDemoStart(const qreal &demoStart);

private:
    QString title_;
    int side_;
    qreal bpm_;
    QString wave_;
    qreal offset_;
    qreal demoStart_;
    QList<NoteChart*> noteCharts_;
    NoteFileParser *fileParser_;
};

#endif // SONG_H
