#include "mainwindow.h"
#include "ui_mainwindow.h"

// 简单的窗口视频播放器

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
