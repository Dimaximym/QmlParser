#include "radiobutton.h"

void RadioButton::generateFromUI(QDomNode &node)
{
    Widget::generateFromUI(node);

    _text = getProperty(node, QString("text"), QString("string"));
}

QString RadioButton::generateQML()
{
    _QML = Widget::generateQML();

    _QML += QString("text:%1\n")
            .arg("\"" + _text + "\"");

    return _QML;
}
