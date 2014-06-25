#ifndef SONG_H
#define SONG_H

#include <QList>
#include <QString>

class NoteChart;
class QGraphicsItem;

// Song is the most top container
// Song -> NoteChart -> Measure -> Note
class Song
{
public:
    Song(QGraphicsItem *parent);

    NoteChart *createNoteChart();
    int chartCount() const;
    NoteChart *chartAt(int index) const;

    QString title() const;
    void setTitle(const QString &title);

    QString subtitle() const;
    void setSubtitle(const QString &subtitle);

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
    QString subtitle_;
    int side_;
    qreal bpm_;
    QString wave_;
    qreal offset_;
    qreal demoStart_;
    QList<NoteChart*> noteCharts_;
    QGraphicsItem *parentItem_;
};

#endif // SONG_H
