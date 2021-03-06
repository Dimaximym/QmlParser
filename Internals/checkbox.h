#ifndef CHECKBOX_H
#define CHECKBOX_H
#include "widget.h"

class CheckBox : public Widget
{
public:
    CheckBox() {}

    bool    _checked;

    void generateFromUI(QDomNode &node) override;
    QString generateQML() override;
};

#endif // CHECKBOX_H
