#include "internal.h"

QString Internal::getProperty(QDomNode &node, QString propertyName, QString propertyTag)
{
    QDomNode childNode = node.firstChild();
    QString result;

    /// Плоский проход по потомкам widget'а
    /// Плоский означает проход только по этой глубине.
    /// При этом для каждого элемента плоского прохода
    /// следует обойти всех потомков для поиска нужного свойства.
    while(!childNode.isNull())
    {
        QDomElement property = childNode.toElement();
        if (property.tagName() == "property")
            if (property.attribute("name") == propertyName)
            {
                bool endRecursion = false;

                /// Лямбда-функция для рекурсивного обхода
                /// дерева со свойствами объекта
                auto travers = [&endRecursion, &result, propertyTag](auto &self, QDomElement &_parent)
                {
                    if (endRecursion) return;
                    QDomElement childProperty = _parent.firstChild().toElement();

                    while(!childProperty.isNull())
                    {
                        if (childProperty.tagName() == propertyTag)
                        {
                            result = childProperty.text();
                            endRecursion = true;
                            return;
                        }
                        if (childProperty.hasChildNodes())
                            self(self, childProperty);//call recursive lambda function
                        childProperty = childProperty.nextSiblingElement();
                    }
                };

                travers(travers, property);
            }

        childNode = childNode.nextSibling();
    }

    return result;
}

void Internal::generateFromUI(QDomNode &node)
{
    _classNameUI = node.attributes().namedItem("class").nodeValue();

    // Parsing for QML class name
    if (_classNameUI == "QMainWindow")
        _classNameQML = "Rectangle";
    else if (_classNameUI == "QWidget")
        _classNameQML = "Rectangle";
    else if (_classNameUI == "QLabel")
        _classNameQML = "Label";
    else if (_classNameUI == "QPushButton")
        _classNameQML = "Button";

    _name = node.attributes().namedItem("name").nodeValue();
}

QString Internal::generateQML()
{
    _QML = "%1 {\n";
    return _QML;
}
