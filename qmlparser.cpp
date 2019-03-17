#define ATTRIBUTE(name) attributes().namedItem(name).nodeValue()

#include "qmlparser.h"
#include "label.h"

QmlParser::QmlParser(QObject *parent)
    :QObject(parent)
{


    QString qmlCode;

    QFile file;
    file.setFileName("F:/Development/C++/QmlTranslator/mainwindow.ui");
//    file.setFileName("F:/Development/C++/pronto/Src/Mac/Pronto.Shell/Forms/MailWidget/MailWidget.ui");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Error: open";
//        return;
    }

    /// Реализация через QDomDocument
    QDomDocument doc;

    if (!doc.setContent(file.readAll()))
        qDebug() << "bad xml file";
    file.close();

    QDomElement root = doc.documentElement();
    if (root.tagName() != "ui")
        qDebug() << "bad xml file: not ui file";

    generateInternals(root);

    outputInternal();



}

void QmlParser::generateInternals(QDomNode &_node, Internal *parent)
{
    QDomNode node = _node.firstChild();

    while (!node.isNull())
    {
        QDomElement element = node.toElement();
        Internal *internal = nullptr;

        if (!element.isNull())
        {
            if (element.tagName() == "widget")
            {
                if (element.attribute("class", "") == "QLabel")
                    internal = new Label;
                else
                    internal = new Internal;

                internal->generateFromUI(node);
            }

        }

        if (internal != nullptr)
        {
            // Если элемент корневой, то выделить родителя
            if (element.parentNode().nodeName() == "ui" && parent == nullptr)
            {
                internals.push_back(internal);
            }
            // Если элемент не корневой, то добавить в список детей
            else
            {
                internal->_parent = parent;
                parent->_children.push_back(internal);
            }
        }

        if (node.hasChildNodes())
            generateInternals(node, internal);
        node = node.nextSibling();
    }
}

void QmlParser::outputChild(Internal *obj)
{
    static int deep = 1;
    if (!obj->_children.isEmpty())
    {
        for(auto child: obj->_children)
        {
            QString tab;
            for (int i = 0; i < deep; ++i) tab += "  ";
            qDebug() << tab << child->_className << "(" << child->_name << ")";
            ++deep;
            outputChild(child);
            --deep;
        }
    }
}

void QmlParser::outputInternal()
{
    qDebug() << "\n\nCreating QML...";
    for(auto obj: internals)
    {
        qDebug() << obj->_className;
        outputChild(obj);
    }
}

void QmlParser::generateQML()
{
    QFile qmlFile("F:/Development/C++/QmlTranslator/test.qml");
    QString str = "import QtQuick 2.0\nimport QtQuick.Controls 2.1\n"
                  "import QtQuick.Window 2.0\n"
                  "ApplicationWindow {\nid: window\nvisible: true\n"
                  "Rectangle {"
                  "anchors.fill: parent;"
                  "color: \"red\";"
                  "}"
                  ""
                  ""
                  "}";

    if (!qmlFile.open(QIODevice::WriteOnly))
    {
        qmlFile.close();
    }
    else
    {
        QTextStream out(&qmlFile);
        out << str;
        qmlFile.close();
    }

    QQmlApplicationEngine engine;
    engine.load(QUrl("file:F:/Development/C++/QmlTranslator/test.qml"));
//    if (engine.rootObjects().isEmpty())
//        return;
}
