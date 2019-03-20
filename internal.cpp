#include "internal.h"

QVariant Internal::getProperty(QDomNode &node, QString propertyName, QString propertyTag)
{
    QDomNode childNode = node.firstChild();
    QVariant result;

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
    _className = node.attributes().namedItem("class").nodeValue();
    _name = node.attributes().namedItem("name").nodeValue();

    _x = getProperty(node, QString("geometry"), QString("x")).toInt();
    _y = getProperty(node, QString("geometry"), QString("y")).toInt();

    _width  = getProperty(node, QString("geometry"), QString("width")).toInt();
    _height = getProperty(node, QString("geometry"), QString("height")).toInt();
}

QString Internal::generateQML()
{
    return QString("Rectangle {\n "
                   "x:%1\n"
                   "y:%2\n"
                   "width:%3\n"
                   "height:%4\n"
                   "border.color: \"black\"\n")
            .arg(_x)
            .arg(_y)
            .arg(_width)
            .arg(_height);
}
