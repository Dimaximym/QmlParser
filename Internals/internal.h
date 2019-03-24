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
    Internal() {}
    virtual ~Internal() {}

    QString _classNameUI;
    QString _classNameQML;
    QString _name;
    QString _QML;

    Internal *_parent;
    QVector<Internal*> _children;

    virtual void generateFromUI(QDomNode &node);
    virtual QString generateQML();
    virtual bool hasLayout() const {return false;}

    QString getProperty(QDomNode &node, QString propertyName, QString propertyTag);
};

#endif // INTERNAL_H
