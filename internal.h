#ifndef INTERNAL_H
#define INTERNAL_H

#include <QVector>
#include <QString>
#include <QRect>

class Internal
{
public:
    Internal()/*: layoutMode(Layout::Coordinates)*/ {}
    virtual ~Internal() {}

    QString className;
    QString name;

    QRect rect;

    Internal *parent;
    QVector<Internal*> children;

    virtual void generateQML();

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

};

#endif // INTERNAL_H
