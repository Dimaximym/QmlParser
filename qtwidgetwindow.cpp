#include "qtwidgetwindow.h"
#include "ui_qtwidgetwindow.h"

QtWidgetWindow::QtWidgetWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

QtWidgetWindow::~QtWidgetWindow()
{
    delete ui;
}

void QtWidgetWindow::startGenerator(const QString &path)
{
    _parser = new QmlGenerator(path, this);
}
