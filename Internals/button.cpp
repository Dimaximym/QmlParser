#include "button.h"

void Button::generateFromUI(QDomNode &node)
{
    Widget::generateFromUI(node);

    _text = getProperty(node, QString("text"), QString("string"));
}

QString Button::generateQML()
{
    _QML = Widget::generateQML();

    _QML += QString("background: Rectangle{\n"
                    "\tcolor: qssStyle.background\n"
                    "}\n"
                    "text:%1\n")
            .arg("\"" + _text + "\"");

    return _QML;
}
