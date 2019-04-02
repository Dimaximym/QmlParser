#include "checkbox.h"

void CheckBox::generateFromUI(QDomNode &node)
{
    Widget::generateFromUI(node);

    _text = getProperty(node, QString("text"), QString("string"));
}

QString CheckBox::generateQML()
{
    _QML = Widget::generateQML();

    _QML += QString("text:%1\n")
            .arg("\"" + _text + "\"");

    return _QML;
}
