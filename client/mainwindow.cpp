#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(packio_client_type &client)
   : QMainWindow(nullptr)
   , ui(new Ui::MainWindow)
   , _client(client)
{}

MainWindow::~MainWindow()
{
   delete ui;
}
