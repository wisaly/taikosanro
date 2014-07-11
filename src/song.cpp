#include "song.h"

#include "notefileparser.h"

Song::Song(QString noteFile)
    :parentItem_(0),parser_(noteFile,this)
{
    parser_.parse(Ts::INVALID_COURSE);
}

NoteChart *Song::getChart(Ts::Course course)
{
    if (!noteCharts_.contains(course))
    {
        NoteChart *noteChart = new NoteChart(parentItem_);
        noteCharts_[course] = noteChart;
    }

    return noteCharts_[course];
}
