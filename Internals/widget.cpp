#include "widget.h"

void Widget::generateFromUI(QDomNode &node)
{
    Internal::generateFromUI(node);
    findLayout(node);

    _x = getProperty(node, QString("geometry"), QString("x")).toInt();
    _y = getProperty(node, QString("geometry"), QString("y")).toInt();

    _width  = getProperty(node, QString("geometry"), QString("width")).toInt();
    _height = getProperty(node, QString("geometry"), QString("height")).toInt();
}

QString Widget::generateQML()
{
    // Задаем имя класса для QML кода
    _QML = Internal::generateQML()
            .arg(_classNameQML);

    if (!(_parent != nullptr && _parent->hasLayout()))
    {
        _QML += QString("x:%1\n"
                       "y:%2\n"
                       "width:%3\n"
                       "height:%4\n")
                .arg(_x)
                .arg(_y)
                .arg(_width)
                .arg(_height);
    }

    // TEST.Delete later
    if (_classNameUI == "QWidget")
        _QML += "border.color: \"black\"\n";
    // END TEST

    if (hasLayout())
        _QML += QString("Column {\n");

    return _QML;
}

void Widget::findLayout(QDomNode &node)
{
    QDomNode childNode = node.firstChild();

    /// Плоский проход по потомкам widget'а
    /// Плоский означает проход только по этой глубине.
    while(!childNode.isNull())
    {
        QDomElement element = childNode.toElement();
        if (element.tagName() == "layout")
        {
            _hasLayout = true;
            _layoutName = element.attribute("class");
            return;
        }

        childNode = childNode.nextSibling();
    }
}

bool Widget::hasLayout() const
{
    return _hasLayout;
}
