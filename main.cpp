#include "qtwidgetwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QtWidgetWindow w;
    w.show();

    return app.exec();
}
