#ifndef BUTTON_H
#define BUTTON_H
#include "widget.h"

class Button : public Widget
{
public:
    Button() {}

    void generateFromUI(QDomNode &node) override;
    QString generateQML() override;
};

#endif // BUTTON_H
