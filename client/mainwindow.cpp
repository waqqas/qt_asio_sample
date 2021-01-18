#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include <string>
#include <QKeyEvent>
#include <QAbstractEventDispatcher>
#include <bits/stdc++.h>

#include <QApplication>
#include <packio/packio.h>
#include <thread>
#include <QSocketNotifier>
#include <stdio.h>
#include <unistd.h>

using packio::arg;
using packio::nl_json_rpc::make_client;
using packio::nl_json_rpc::rpc;

MainWindow::MainWindow(MyClient* client)
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

// void MainWindow::on_pushButton_clicked()
// {
//     int a = ui->label->text().toInt();
//     int b = ui->label_2->text().toInt();
//     // ui->label_3->setNum(a + b);
    
//     client->async_call("add", std::tuple{arg("a") = 24, arg("b") = 42}, [&](packio::error_code, const rpc::response_type
//    &r) {
//             ui->label_3->setNum(r.result.get<int>()); // event generate
//    });
// }

void MainWindow::on_pushButton_clicked()
{
   int a = ui->textEdit->toPlainText().toInt(); 
   int b = ui->textEdit_2->toPlainText().toInt();
   std::cout << "on_pushButton_clicked: " << a << ", " << b  << std::endl;

   emit _client->async_call_add(a,b);
   postMyCustomEvent(a,b,1);
}

void MainWindow::on_pushButton_2_clicked()
{
   int a = ui->textEdit->toPlainText().toInt(); 
   int b = ui->textEdit_2->toPlainText().toInt();
   std::cout << "on_pushButton_clicked : " << a << ", " << b  << std::endl;
   emit _client->async_call_multiply(a,b); // event generate

   _client->client->async_call("add", std::tuple{arg("a") = a, arg("b") = b},
                         [&](packio::error_code, const rpc::response_type &r) {
                            std::cout << a << " * " << b << " = " << r.result.get<int>() << std::endl;
                            result = r.result.get<int>();
                         });
   postMyCustomEvent(a,b,2);
}

void MainWindow::postMyCustomEvent(const int customData1, const int customData2, int button)
{
    // This method (postMyCustomEvent) can be called from any thread

    QApplication::postEvent(this, new MyCustomEvent(customData1, customData2, button, _client));
}

void MainWindow::customEvent(QEvent * event)
{
    // When we get here, we've crossed the thread boundary and are now
    // executing in the Qt object's thread

    if(event->type() == MY_CUSTOM_EVENT)
    {
        handleMyCustomEvent(static_cast<MyCustomEvent *>(event));
    }

    // use more else ifs to handle other custom events
}

void MainWindow::handleMyCustomEvent(const MyCustomEvent *event)
{
    // Now you can safely do something with your Qt objects.
    // Access your custom data using event->getCustomData1() etc.
}