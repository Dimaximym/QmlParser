#include "internal.h"


void Internal::generateFromUI(QDomNode &node)
{
    _className = node.attributes().namedItem("class").nodeValue();
    _name = node.attributes().namedItem("name").nodeValue();
}

QString Internal::generateQML()
{

}
