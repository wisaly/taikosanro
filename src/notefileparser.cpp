#include "notefileparser.h"

#include <QFile>
#include <QDebug>
#include <QQueue>
#include "song.h"

NoteFileParser::NoteFileParser(QString filePath,Song *song) :
    filePath_(filePath),song_(song)
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
        QString line = getLine(inputStream);

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
        else if (line == "#START")
        {
            NoteChart *noteChart = song_->createChart(course);
            noteChart->clear();
            int elapsed = 0;

            noteChart->setCourse(course);
            noteChart->setLevel(level);
            noteChart->setScoreInit(scoreInit);
            noteChart->setScoreDiff(scoreDiff);

            bool isGGT = false;

            // parse notes
            line = getLine(inputStream);
            while (!inputStream.atEnd())
            {
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

                    line = getLine(inputStream);
                    continue;
                }
                if (loadCourse != course)
                {
                    break;
                }

                QString lineCombine;
                while (!inputStream.atEnd() && !line.startsWith('#'))
                {
                    lineCombine += line;
                    line = getLine(inputStream);
                }
                QStringList measures = lineCombine.split(',',QString::SkipEmptyParts);
                QQueue<int> yellowbarLen;
                QQueue<int> ballonLen;
                // reformat yellowbar
                for (int i = 0;i < measures.count();i++)
                {
                    QString &mealine = measures[i];
                    for (int j = 0;j < mealine.count();j++)
                    {
                        bool ballonStart = false;
                        bool yellowbarStart = false;
                        if (mealine[j] == '7')
                            ballonStart = true;
                        else if (mealine[j] == '5' || mealine[j] == '6')
                            yellowbarStart = true;

                        // yellow bar start
                        if (ballonStart || yellowbarStart)
                        {
                            int count = 1;
                            j++;

                            // get whole yellow bar
                            while (i < measures.count())
                            {
                                // move to next measure
                                if (j == mealine.count())
                                {
                                    mealine = measures[i++];
                                    j = 0;
                                }

                                // end of yellow bar
                                if (mealine[j] == '8')
                                {
                                    mealine[j++] = '0';
                                    if (yellowbarStart)
                                        yellowbarLen.append(++count);
                                    else
                                        ballonLen.append(++count);
                                    break;
                                }
                                mealine[j++] = '0';
                                count++;
                            }
                        }
                    }
                }

                // create measure
                for (int i = 0;i < measures.count();i++)
                {
                    QString mealine = measures[i];

                    NoteTypeList noteTypes;
                    for (int j = 0;j < mealine.count();j++)
                    {
                        switch (mealine[j].toLatin1())
                        {
                        case '0':
                            noteTypes.append(Note::Blank);
                            break;
                        case '1':
                            noteTypes.append(Note::RedMarker);
                            break;
                        case '2':
                            noteTypes.append(Note::BlueMarker);
                            break;
                        case '3':
                            noteTypes.append(Note::BigRedMarker);
                            break;
                        case '4':
                            noteTypes.append(Note::BigBlueMarker);
                            break;
                        case '5':
                            noteTypes.append(Note::YellowBar);
                            break;
                        case '6':
                            noteTypes.append(Note::BigYellowBar);
                            break;
                        case '7':
                            noteTypes.append(Note::Balloon);
                            break;
                        case '8':
                            // never reach here
                            noteTypes.append(Note::EndYellowBar);
                            break;
                        case '9':
                            noteTypes.append(Note::Yam);
                            break;
                        }
                    }

                    Measure *measure = noteChart->createMeasure();
                    measure->setTempo(tempo);
                    measure->setNoteValuePerBeat(noteValuePerBeat);
                    measure->setBeatsPerBar(beatsPerBar);
                    measure->setAppearElapsed(elapsed);
                    measure->setGGT(isGGT);
                    measure->setNotes(noteTypes,ballons,ballonLen,yellowbarLen);

                    elapsed += 60000 * beatsPerBar / tempo;
                }
            }
        }
        else if (line == "#BREAK")
        {
            break;
        }
    }

    return true;
}

QString NoteFileParser::getLine(QTextStream &input)
{
    QString line = input.readLine().trimmed();
    int commentIndex = line.indexOf("//");
    if (commentIndex >= 0)
    {
        line = line.left(commentIndex);
    }

    return line;
}
