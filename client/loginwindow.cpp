#include "loginwindow.h"

#include "./ui_loginwindow.h"

#include <QDebug>

LoginWindow::LoginWindow(QWidget *parent)
   : QMainWindow(parent)
   , ui(new Ui::LoginWindow)
{
   ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
   delete ui;
}

void LoginWindow::on_addButton_clicked()
{
   int a = ui->input1->toPlainText().toInt();
   int b = ui->input2->toPlainText().toInt();

   emit addRequested(a, b);
}

void LoginWindow::updateResult(const int &result)
{
   ui->addOutput->setText(QString::number(result));
}