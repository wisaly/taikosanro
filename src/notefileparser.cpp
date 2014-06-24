#include "notefileparser.h"

#include <QFile>
#include "song.h"

NoteFileParser::NoteFileParser(QString filePath,Song *song)
    :filePath_(filePath),song_(song)
{
}

bool NoteFileParser::parse()
{
    QFile inputFile(filePath_);
    if (!inputFile.open(QFile::ReadOnly | QFile::Text))
    {
        return false;
    }

    int course = 3;
    int level = 1;
    int scoreInit = 0;
    int scoreDiff = 0;
    qreal tempo = 0;
    QList<int> ballons;

    while (!inputFile.atEnd())
    {
        QString line = inputFile.readLine();

        if (line.isEmpty())
        {
            continue;
        }
        int splitIndex = line.indexOf(':');
        if (splitIndex != -1)
        {
            QString key = line.left(splitIndex);
            QString val = line.mid(splitIndex + 1);

            if (key == "TITLE")
            {
                song_->setTitle(val);
            }
            else if (key == "BPM")
            {
                song_->setBpm(val.toDouble());
                tempo = song_->bpm();
            }
            else if (key == "WAVE")
            {
                song_->setWave(val);
            }
            else if (key == "OFFSET")
            {
                song_->setOffset(val.toDouble());
            }
            else if (key == "LEVEL")
            {
                level = val.toInt();
            }
            else if (key == "BALLOON")
            {
                QStringList ballonsSrc = val.split(',',QString::SkipEmptyParts);
                ballons.clear();
                for (int i = 0;i < ballonsSrc.count();i++)
                {
                    ballons.append(ballonsSrc[i].toInt());
                }
            }
            else if (key == "SCOREINIT")
            {
                scoreInit = val.toInt();
            }
            else if (key == "SCOREDIFF")
            {
                scoreDiff = val.toInt();
            }
            else if (key == "COURSE")
            {
                if (val == "Easy" || val == "0")
                {
                    course = 0;
                }
                else if (val == "Normal" || val == "1")
                {
                    course = 1;
                }
                else if (val == "Hard" || val == "2")
                {
                    course = 2;
                }
                else if (val == "Oni" || val == "3")
                {
                    course = 3;
                }
                else if (val == "Edit" || val == "4")
                {
                    course = 4;
                }
                else
                {
                    course = 3;
                }
            }
            else if (key == "SONGVOL")
            {
            }
            else if (key == "SEVOL")
            {
            }
            else if (key == "STYLE")
            {
            }
            else if (key == "GAME")
            {
            }
            else if (key == "LIFE")
            {
            }
            else if (key == "DEMOSTART")
            {
                song_->setDemoStart(val.toDouble());
            }
            else if (key == "SIDE")
            {
            }
            else if (key == "SUBTITLE")
            {
                song_->setSubtitle(val);
            }
            else if (key == "SCOREMODE")
            {
            }
            else if (key == "TOTAL")
            {
            }
        }

        if (line.startsWith('#'))
        {
            if (line == "#START")
            {
                NoteChart *noteChart = song_->createNoteChart();

                noteChart->setCourse(course);
                noteChart->setLevel(level);
                noteChart->setScoreInit(scoreInit);
                noteChart->setScoreDiff(scoreDiff);

                while (!inputFile.atEnd())
                {
                    line = inputFile.readLine();

                    if (line.startsWith('#'))
                    {
                        if (line == "#END")
                        {
                            break;
                        }
                        else if (line == "#GOGOSTART")
                        {

                        }
                        else if (line == "GOGOEND")
                        {

                        }
                    }

                    QStringList measuresSrc = line.split(',',QString::SkipEmptyParts);
                    for (int i = 0;i < measuresSrc.count();i++)
                    {
                        QString measureSrc = measuresSrc[i];

                        NoteTypeList noteTypes;
                        for (int j = 0;j < measureSrc.count();j++)
                        {
                            if (measureSrc[j] == '0')
                                noteTypes.append(Note::Blank);
                            else if (measureSrc[j] == '1')
                                noteTypes.append(Note::RedMarker);
                            else if (measureSrc[j] == '2')
                                noteTypes.append(Note::BlueMarker);
                            else if (measureSrc[j] == '3')
                                noteTypes.append(Note::BigRedMarker);
                            else if (measureSrc[j] == '4')
                                noteTypes.append(Note::BigBlueMarker);
                            else if (measureSrc[j] == '5')
                                noteTypes.append(Note::YellowBar);
                            else if (measureSrc[j] == '6')
                                noteTypes.append(Note::BigYellowBar);
                            else if (measureSrc[j] == '7')
                                noteTypes.append(Note::Ballon);
                            else if (measureSrc[j] == '8')
                                noteTypes.append(Note::EndYellowBar);
                            else if (measureSrc[j] == '9')
                                noteTypes.append(Note::Yam);
                        }
                        noteChart->createMeasure(noteTypes,tempo,0,0);
                    }
                }
            }
        }
    }

    return true;
}
