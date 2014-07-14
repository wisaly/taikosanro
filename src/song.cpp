#include "song.h"

#include "notefileparser.h"

Song::Song(QString noteFile)
    :parser_(noteFile,this),parentItem_(0)
{
    parser_.parse(Ts::INVALID_COURSE);
}

NoteChart *Song::createChart(Ts::Course course)
{
    if (!noteCharts_.contains(course))
    {
        NoteChart *noteChart = new NoteChart(parentItem_);
        noteCharts_[course] = noteChart;
    }

    return noteCharts_[course];
}

NoteChart *Song::getChart(Ts::Course course)
{
    return noteCharts_.contains(course) ? noteCharts_[course] : 0;
}
