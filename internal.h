#ifndef INTERNAL_H
#define INTERNAL_H

#include <QVector>
#include <QString>
#include <QPoint>

class Internal
{
public:
    Internal()/*: layoutMode(Layout::Coordinates)*/ {}

    QString className;
    QString name;

//    enum Layout
//    {
//        Coordinates = 0,
//        Layout
//    } layoutMode;

//    enum LayoutType
//    {
//        Cell = 0,
//        Row,
//        Column
//    } layoutType;

    QPoint coords;

    QVector<Internal*> children;
};

#endif // INTERNAL_H
