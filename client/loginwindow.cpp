#include "loginwindow.h"

#include "./ui_loginwindow.h"

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

   QApplication::postEvent(this, new AddRequestEvent(a, b));
}

void LoginWindow::customEvent(QEvent *event)
{
#pragma GCC diagnostic ignored "-Wswitch"
   switch (event->type())
   {
   case ADD_RESULT_EVENT:
      handleAddResultEvent(static_cast<AddResultEvent *>(event));
      break;
   }
}

void LoginWindow::handleAddResultEvent(const AddResultEvent *event)
{
   ui->addOutput->setText(QString::number(event->result()));
}