#ifndef QMLPARSER_H
#define QMLPARSER_H

#include "internal.h"

#include <QObject>
#include <QDebug>
#include <QQmlApplicationEngine>

#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include <QPoint>

#include <QDomDocument>

class QmlParser : public QObject
{
    Q_OBJECT
public:
    QmlParser(QObject *parent);
    virtual ~QmlParser() {}

    // Generate QVector of internal view .ui file
    void generateInternals(QDomNode &node, Internal *parent = nullptr);
    void generateQML();

    // Testing functional
    void outputInternal();
    void outputChild(Internal *obj);

    QVector<Internal*> internals;
};
#endif // QMLPARSER_H
