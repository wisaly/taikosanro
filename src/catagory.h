#ifndef CATAGORY_H
#define CATAGORY_H

#include <QList>
#include <QColor>
#include "song.h"

class Catagory
{
public:
    Catagory();

    QString title() const { return title_; }
    void setTitle(const QString &title) { title_ = title; }

    QColor foreColor() const { return foreColor_; }
    void setForeColor(const QColor &foreColor) { foreColor_ = foreColor; }

    QColor backColor() const { return backColor_; }
    void setBackColor(const QColor &backColor) { backColor_ = backColor; }

    int count() const { return songs_.count(); }
    Song* songAt(int i) { return songs_[i]; }
    void append(Song *song) { songs_.append(song); }

private:
    QString title_;
    QColor foreColor_;
    QColor backColor_;
    QList<Song*> songs_;
};

#endif // CATAGORY_H
