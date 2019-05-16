#include "checkbox.h"

void CheckBox::generateFromUI(QDomNode &node)
{
    Widget::generateFromUI(node);

    _text = getProperty(node, QString("text"),    QString("string"));

    if (getProperty(node, QString("checked"), QString("bool")) == "true")
        _checked = true;
    else
        _checked = false;
}

QString CheckBox::generateQML()
{
    _QML = Widget::generateQML();

    _QML += QString("text:%1\n")
            .arg("\"" + _text + "\"");

    QString checked = _checked ? "true" : "false";
    _QML += QString("checked:%1\n")
            .arg(checked);

    return _QML;
}
