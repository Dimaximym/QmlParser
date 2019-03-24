#include "qmlparser.h"
#include "Internals/label.h"

QmlParser::QmlParser(QObject *parent)
    :QObject(parent)
{
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

    generateQML();

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
                    internal = new Widget;

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
        {
            if (internal != nullptr)
                generateInternals(node, internal);
            else
                generateInternals(node, parent);
        }
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
            qDebug() << tab << child->_classNameUI << "(" << child->_name << ")";
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
        qDebug() << obj->_classNameUI;
        outputChild(obj);
    }
}

void QmlParser::generateQML()
{
    QFile qmlFile("F:/Development/C++/QmlTranslator/test.qml");
    QString str = "import QtQuick 2.0\nimport QtQuick.Controls 2.1\n"
                  "import QtQuick.Window 2.0\n"
                  "ApplicationWindow {\nid: window\nvisible: true\n";

    /// Лямбда-функция для рекурсивного обхода
    /// дерева _internals
    auto travers = [ &str/*, &endRecursion, &result*/](auto &self, Internal *internal)
    {
        if (internal == nullptr)
            return;

        str += internal->generateQML();
        if (internal->_children.isEmpty())
        {
            // Закрытие layout
            if (internal->hasLayout())
                str += "}\n";
            // Закрытие внешнего блока (если нет детей)
            str += "}\n";
            return;
        }
        // Проход по всем детям объекта
        for (int i = 0; i < internal->_children.size(); ++i)
        {
            self(self, internal->_children.at(i));
        }
        // Закрытие layout
        if (internal->hasLayout())
            str += "}\n";
        // Закрытие внешнего блока после обхода всех детей
        str += "}\n";
    };

    Internal *internal = internals[0];
    travers(travers, internal);
    // Скобка закрывает блок ApplicationWindow
    str += "}\n";

    if (!qmlFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "QML file not open!";
        return;
    }
    else
    {
        QTextStream out(&qmlFile);
        out << str;
        qmlFile.close();
    }

    QQmlApplicationEngine *engine = new QQmlApplicationEngine;
    engine->load(QUrl("file:F:/Development/C++/QmlTranslator/test.qml"));
}
