#ifndef WIDGET_H
#define WIDGET_H

#include <QVector>
#include <QString>
#include <QRect>
#include <QDomNode>
#include <QVariant>

#include "internal.h"

class Widget : public Internal
{
public:
    Widget(): _x(0), _y(0), _width(0), _height(0), _hasLayout(false) {}

    void generateFromUI(QDomNode &node) override;
    QString generateQML() override;

    bool hasLayout() const override;

    int _x;
    int _y;
    int _width;
    int _height;


private:
    /// Ищет в заданном ноде присутствие layout
    void findLayout(QDomNode &node);

    bool _hasLayout;
    QString _layoutName;



};

#endif // WIDGET_H
