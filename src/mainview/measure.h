#ifndef MEASURE_H
#define MEASURE_H

#include "note.h"

#include <QGraphicsItem>
#include <QQueue>

class Measure : public QGraphicsItem
{
public:
    Measure(QGraphicsItem *parent);
    ~Measure();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);

    void reset();

    void calcPos(int currentElapsed);

    // create notes
    void setNotes(NoteTypeList notes,QQueue<int> &ballonHits,QQueue<int> &ballonLen,QQueue<int> &yellowbarLen);

    // property
    void setBoundingRect(QRectF rect);
    QRectF boundingRect() const { return canvasRect_; }

    int disappearElapsed() const { return disappearElapsed_; }

    int noteCount() { return notes_.count(); }
    Note *noteAt(int index) { return notes_[index]; }
    void clear();

    int appearElapsed() const { return appearElapsed_; }
    void setAppearElapsed(int appearElapsed) { appearElapsed_ = appearElapsed; }

    bool isGGT() const { return isGGT_; }
    void setGGT(bool isGGT) { isGGT_ = isGGT; }

    int beatsPerBar() const { return beatsPerBar_; }
    void setBeatsPerBar(int beatsPerBar) { beatsPerBar_ = beatsPerBar; }

    int noteValuePerBeat() const { return noteValuePerBeat_; }
    void setNoteValuePerBeat(int noteValuePerBeat) { noteValuePerBeat_ = noteValuePerBeat; }

    qreal tempo() const { return tempo_; }
    void setTempo(const qreal &tempo) { tempo_ = tempo; }

    void setNoteRect(const QRectF &noteRect) { noteRect_ = noteRect; }
private:
    int getTimeLength(int noteCount);
protected:
    void advance(int phase);

private:
    QRectF canvasRect_;
    QList<Note*> notes_;
    qreal tempo_;
    int noteValuePerBeat_;
    int beatsPerBar_;
    int noteUnitCount_;
    bool isGGT_;
    int appearElapsed_;
    int disappearElapsed_;
    QRectF noteRect_;
};
#endif // MEASURE_H
