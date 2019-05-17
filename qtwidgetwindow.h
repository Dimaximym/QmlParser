#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qmlgenerator.h"

namespace Ui {
class MainWindow;
}

class QtWidgetWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QtWidgetWindow(QWidget *parent = nullptr);
    ~QtWidgetWindow();

private:
    Ui::MainWindow *ui;
    QmlGenerator _parser;
};

#endif // MAINWINDOW_H
