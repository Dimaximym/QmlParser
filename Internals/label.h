#ifndef LABEL_H
#define LABEL_H

#include "widget.h"

class Label : public Widget
{
public:
    Label() {}
    QString _text;

    void generateFromUI(QDomNode &node) override;
    QString generateQML() override;
};

#endif // LABEL_H
