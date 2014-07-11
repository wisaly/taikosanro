#include "notefileparser.h"

#include <QFile>
#include <QDebug>
#include <QQueue>
#include "song.h"

NoteFileParser::NoteFileParser(QString filePath,Song *song)
    :filePath_(filePath),song_(song)
{
}

bool NoteFileParser::parse(Ts::Course loadCourse)
{
    QFile inputFile(filePath_);
    if (!inputFile.open(QFile::ReadOnly | QFile::Text))
    {
        return false;
    }
    QTextStream inputStream(&inputFile);

    Ts::Course course = Ts::ONI;
    int level = 1;
    int scoreInit = 0;
    int scoreDiff = 0;
    qreal tempo = 0;
    QQueue<int> ballons;
    int beatsPerBar = 4;
    int noteValuePerBeat = 4;

    while (!inputStream.atEnd())
    {
        QString line = inputStream.readLine().trimmed();

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
                    ballons.enqueue(ballonsSrc[i].toInt());
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
                    course = Ts::KANTAN;
                }
                else if (val == "Normal" || val == "1")
                {
                    course = Ts::FUTSU;
                }
                else if (val == "Hard" || val == "2")
                {
                    course = Ts::MUZUKASHII;
                }
                else if (val == "Oni" || val == "3")
                {
                    course = Ts::ONI;
                }
                else if (val == "Edit" || val == "4")
                {
                    course = Ts::URA;
                }
                else
                {
                    course = Ts::ONI;
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
        else if (line.startsWith('#'))
        {
            if (line == "#START")
            {
                NoteChart *noteChart = song_->getChart(course);
                int elapsed = 0;

                noteChart->setCourse(course);
                noteChart->setLevel(level);
                noteChart->setScoreInit(scoreInit);
                noteChart->setScoreDiff(scoreDiff);

                bool isGGT = false;

                // parse notes
                while (!inputStream.atEnd())
                {
                    line = inputStream.readLine().trimmed();

                    if (line.startsWith('#'))
                    {
                        QStringList commands = line.split(' ',QString::SkipEmptyParts);
                        if (commands[0] == "#END")
                        {
                            break;
                        }
                        else if (commands[0] == "#GOGOSTART")
                        {
                            isGGT = true;
                        }
                        else if (commands[0] == "#GOGOEND")
                        {
                            isGGT = false;
                        }
                        else if (commands[0] == "#MEASURE")
                        {

                        }
                        else if (commands[0] == "#BPMCHANGE")
                        {
                        }
                        else if (commands[0] == "#SCROLL")
                        {
                        }
                        else if (commands[0] == "#DELAY")
                        {
                        }
                        else if (commands[0] == "#SECTION")
                        {
                        }
                        else if (commands[0] == "#BRANCHSTART")
                        {
                        }
                        else if (commands[0] == "#BRANCHEND")
                        {
                        }
                        else if (commands[0] == "#N")
                        {
                        }
                        else if (commands[0] == "#E")
                        {
                        }
                        else if (commands[0] == "#M")
                        {
                        }
                        else if (commands[0] == "#LEVELHOLD")
                        {
                        }
                        else if (commands[0] == "#BMSCROLL")
                        {
                        }
                        else if (commands[0] == "#HBSCROLL")
                        {
                        }
                        else if (commands[0] == "#BARLINEOFF")
                        {
                        }
                        else if (commands[0] == "#BARLINEON")
                        {
                        }

                        continue;
                    }
                    if (loadCourse != course)
                    {
                        break;
                    }
                    noteChart->clear();

                    // TODO: a measure could sperated in multi lines.
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

                        noteChart->createMeasure(noteTypes,ballons,tempo,noteValuePerBeat,beatsPerBar,isGGT,elapsed);

                        elapsed += 60000 * beatsPerBar / tempo;
                    }
                }
            }
            else if (line == "#BREAK")
            {
                break;
            }
        }
    }

    return true;
}
