#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qmlparser.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QmlParser parser(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
