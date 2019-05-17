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
