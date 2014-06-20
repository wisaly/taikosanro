#include "song.h"

#include "notefileparser.h"

Song::Song(QString filePath)
    :fileParser_(new NoteFileParser(filePath))
{
}
QString Song::title() const
{
    return title_;
}

void Song::setTitle(const QString &title)
{
    title_ = title;
}
int Song::side() const
{
    return side_;
}

void Song::setSide(int side)
{
    side_ = side;
}
qreal Song::bpm() const
{
    return bpm_;
}

void Song::setBpm(const qreal &bpm)
{
    bpm_ = bpm;
}
QString Song::wave() const
{
    return wave_;
}

void Song::setWave(const QString &wave)
{
    wave_ = wave;
}
qreal Song::offset() const
{
    return offset_;
}

void Song::setOffset(const qreal &offset)
{
    offset_ = offset;
}
qreal Song::demoStart() const
{
    return demoStart_;
}

void Song::setDemoStart(const qreal &demoStart)
{
    demoStart_ = demoStart;
}






