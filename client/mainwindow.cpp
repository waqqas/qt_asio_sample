#include "mainwindow.h"

#include "./ui_mainwindow.h"

using packio::arg;
using packio::nl_json_rpc::make_client;
using packio::nl_json_rpc::rpc;

MainWindow::MainWindow(MainWindow::packio_client_type &client)
   : QMainWindow(nullptr)
   , ui(new Ui::MainWindow)
   , _client(client)
{
   ui->setupUi(this);
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::on_addButton_clicked()
{
   int a = ui->input1->toPlainText().toInt();
   int b = ui->input2->toPlainText().toInt();

   // Make an asynchronous call with named arguments
   _client->async_call("add", std::tuple{arg("a") = a, arg("b") = b},
                       [&](packio::error_code, const rpc::response_type &r) { postAddResult(r.result.get<int>()); });
}

void MainWindow::postAddResult(const int &result)
{
   QApplication::postEvent(this, new AddResultEvent(result));
}

void MainWindow::customEvent(QEvent *event)
{
   if (event->type() == ADD_RESULT_EVENT)
   {
      handleAddResultEvent(static_cast<AddResultEvent *>(event));
   }
}

void MainWindow::handleAddResultEvent(const AddResultEvent *event)
{
   ui->addOutput->setText(QString::number(event->result()));
}