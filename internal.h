#ifndef INTERNAL_H
#define INTERNAL_H

#include <QVector>
#include <QString>
#include <QRect>
#include <QDomNode>

class Internal
{
public:
    Internal()/*: layoutMode(Layout::Coordinates)*/ {}
    virtual ~Internal() {}

    QString _className;
    QString _name;

    QRect _rect;

    Internal *_parent;
    QVector<Internal*> _children;

    virtual void generateFromUI(QDomNode &node);
    virtual QString generateQML();

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
