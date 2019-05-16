#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H
#include "widget.h"

class RadioButton : public Widget
{
public:
    RadioButton() {}

    bool    _checked;

    void generateFromUI(QDomNode &node) override;
    QString generateQML() override;
};

#endif // RADIOBUTTON_H
