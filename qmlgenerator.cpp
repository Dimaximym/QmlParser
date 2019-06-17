#include "qmlgenerator.h"
#include "Internals/label.h"
#include "Internals/widget.h"
#include "Internals/button.h"
#include "Internals/textinput.h"
#include "Internals/checkbox.h"
#include "Internals/radiobutton.h"

QmlGenerator::QmlGenerator(const QString &path, QObject *parent)
    :QObject(parent)
{
    QFile file;
    //F:/Development/C++/QmlTranslator/qtwidgetwindow.ui
    file.setFileName(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Error: can't open Qt Widget's file";
        return;
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

void QmlGenerator::generateInternals(QDomNode &_node, Internal *parent)
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
                internal = createInternal(element.attribute("class", ""));

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

Internal *QmlGenerator::createInternal(QString className)
{
    if (className == "QLabel")
        return new Label;
    if (className == "QPushButton")
        return new Button;
    if (className == "QLineEdit")
        return new TextInput;
    if (className == "QCheckBox")
        return new CheckBox;
    if (className == "QRadioButton")
        return new RadioButton;
    else
        return new Widget;
}

void QmlGenerator::outputChild(Internal *obj)
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

void QmlGenerator::outputInternal()
{
    qDebug() << "\n\nCreating QML...";
    for(auto obj: internals)
    {
        qDebug() << obj->_classNameUI;
        outputChild(obj);
    }
}

void QmlGenerator::generateQML()
{
    int w = 100;
    int h = 100;

    if (!internals.isEmpty())
    {
        Widget *tmp;
        if ((tmp = dynamic_cast<Widget *>(internals.first())) != nullptr)
        {
            w = tmp->_width;
            h = tmp->_height;
        }
    }

    QString str = QString("\twidth: %1\n"
                  "\theight: %2\n\t")
                  .arg(w)
                  .arg(h);

    // Глубина вложенности для вывода табуляции
    int deep = 1;

    /// Лямбда-функция для рекурсивного обхода
    /// дерева _internals
    auto travers = [ this, &str, &deep](auto &self, Internal *internal)
    {
        if (internal == nullptr)
            return;

        str += fillTabs(internal->generateQML(), deep);
        if (internal->_children.isEmpty())
        {
            // Закрытие layout
            if (internal->hasLayout())
                str += fillTabs("}\n", deep);
            // Закрытие внешнего блока (если нет детей)
            str += fillTabs("}\n", deep);
            return;
        }
        // Проход по всем детям объекта
        for (int i = 0; i < internal->_children.size(); ++i)
        {
            deep++;
            self(self, internal->_children.at(i));
            deep--;
        }
        // Закрытие layout
        if (internal->hasLayout())
            str += fillTabs("}\n", deep);
        // Закрытие внешнего блока после обхода всех детей
        str += fillTabs("}\n", deep);
    };

    Internal *internal = internals[0];
    travers(travers, internal);
    // Скобка закрывает блок ApplicationWindow
    str += "}\n";

    QFile firstPartFile("F:/Development/C++/QmlTranslator/qml/FirstPart.qml");
    QString firstPartText;
    if (!firstPartFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << firstPartFile.fileName() << " file not open!";
        return;
    }
    else
    {
        firstPartText = firstPartFile.readAll();
        firstPartFile.close();
    }

    QFile qmlFile("F:/Development/C++/QmlTranslator/qml/output.qml");
    if (!qmlFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        qDebug() << qmlFile.fileName() << " file not open!";
        return;
    }
    else
    {
        QTextStream out(&qmlFile);
        out << firstPartText << str;
        qmlFile.close();
    }

    QQmlApplicationEngine *engine = new QQmlApplicationEngine;
    engine->load(QUrl("file:F:/Development/C++/QmlTranslator/qml/output.qml"));
}

QString QmlGenerator::fillTabs(QString source, int deep)
{
    // Генерация табуляции
    QString tab;
    for (int i = 0; i < deep; ++i) tab += "\t";

    if (source.isEmpty()) return QString();
    const QRegExp re{QString("(") + "\\n" + ")"};
    return source.replace(re, "\\1" + tab);
}
