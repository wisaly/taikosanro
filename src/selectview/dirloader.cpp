#include "dirloader.h"
#include <QDebug>
#include <QSettings>
#include <QTextCodec>

DirLoader::DirLoader(QString initPath)
    :dir_(initPath)
{
}

QList<Catagory> DirLoader::load()
{
    QList<Catagory> catagories;

    QFileInfoList genreDirs = dir_.entryInfoList(
                QDir::Dirs | QDir::NoDotAndDotDot ,QDir::Name | QDir::IgnoreCase);
    foreach (QFileInfo genreDirInfo, genreDirs)
    {
        QDir genreDir(genreDirInfo.filePath());
        QString genreFilePath = genreDir.filePath("genre.ini");

        // ignore sub dir without genre.ini
        if (!QFile::exists(genreFilePath))
            continue;

        Catagory catagory;

        // load config content
        QSettings genreFile(genreFilePath,QSettings::IniFormat);
        genreFile.setIniCodec(QTextCodec::codecForLocale());
        genreFile.beginGroup("Genre");
        catagory.setTitle(genreFile.value("GenreName").toString());
        catagory.setForeColor(QColor(genreFile.value("FontColor").toString()));
        catagory.setBackColor(QColor(genreFile.value("GenreColor").toString()));

        // get inner dir and genre dir self
        QFileInfoList innerDirs = genreDir.entryInfoList(
                    QDir::Dirs | QDir::NoDotDot,QDir::Name | QDir::IgnoreCase);
        foreach (QFileInfo innerDir, innerDirs)
        {
            // search tja files
            QFileInfoList noteFiles = QDir(innerDir.filePath()).entryInfoList(
                        QStringList() << "*.tja",QDir::Files,QDir::Name | QDir::IgnoreCase);

            foreach (QFileInfo noteFile, noteFiles)
            {\
                catagory.files().append(noteFile.filePath());
            }
        }

        catagories.append(catagory);
    }
    return catagories;
}
