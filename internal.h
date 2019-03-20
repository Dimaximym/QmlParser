#ifndef INTERNAL_H
#define INTERNAL_H

#include <QVector>
#include <QString>
#include <QRect>
#include <QDomNode>
#include <QVariant>

class Internal
{
public:
    Internal(): _x(0), _y(0), _width(0), _height(0) {}
    virtual ~Internal() {}

    QString _className;
    QString _name;

    int _x;
    int _y;
    int _width;
    int _height;

    Internal *_parent;
    QVector<Internal*> _children;

    virtual void generateFromUI(QDomNode &node);
    virtual QString generateQML();

    QVariant getProperty(QDomNode &node, QString propertyName, QString propertyTag);
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
