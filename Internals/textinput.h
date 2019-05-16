#ifndef TEXTEDIT_H
#define TEXTEDIT_H
#include "widget.h"

class TextInput : public Widget
{
public:
    TextInput() {}

    void generateFromUI(QDomNode &node) override;
    QString generateQML() override;
};

#endif // TEXTEDIT_H
