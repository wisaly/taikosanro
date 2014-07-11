#ifndef CATAGORY_H
#define CATAGORY_H

#include <QList>
#include <QColor>
#include <QStringList>

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

    QStringList &files() { return files_; }

private:
    QString title_;
    QColor foreColor_;
    QColor backColor_;
    QStringList files_;
};

#endif // CATAGORY_H
