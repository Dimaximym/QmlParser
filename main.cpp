#include "qtwidgetwindow.h"

#include <QApplication>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDialog>
#include <QPushButton>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QtWidgetWindow w;

    QDialog inputDialog;
    QVBoxLayout layout;
    QLabel label(QString("Insert path to Qt Widget's file:"));
    QLineEdit input;
    QPushButton button(QString("OK"));

    layout.addWidget(&label);
    layout.addWidget(&input);
    layout.addWidget(&button);
    QObject::connect(&button, &QPushButton::clicked, &inputDialog, &QDialog::accept);

    inputDialog.setLayout(&layout);
    if (inputDialog.exec() == QDialog::Accepted)
    {
        w.show();
        QString path = input.text();
        w.startGenerator(path);
    }



    return app.exec();
}
