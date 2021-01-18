#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAbstractEventDispatcher>
#include <QEvent>
#include <QKeyEvent>
#include <QMainWindow>
#include <bits/stdc++.h>
#include <iostream>
#include <packio/packio.h>
#include <string>

#include <QApplication>
#include <QSocketNotifier>
#include <iostream>
#include <packio/packio.h>
#include <stdio.h>
#include <thread>
#include <unistd.h>

using packio::arg;
using packio::nl_json_rpc::make_client;
using packio::nl_json_rpc::rpc;
using namespace packio::arg_literals;

const QEvent::Type MY_CUSTOM_EVENT = static_cast<QEvent::Type>(QEvent::User + 1);

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
class MyClient;
}  // namespace Ui
QT_END_NAMESPACE

namespace pr = packio::nl_json_rpc;

class MyClient
{
 public:

   packio::net::io_context        io;
   packio::net::ip::tcp::endpoint server_ep{packio::net::ip::make_address("127.0.0.1"), 4000};
   std::shared_ptr<packio::client<pr::rpc, packio::net::ip::tcp::socket>> client =
      make_client(packio::net::ip::tcp::socket{io});
   void async_call_add(int a, int b)
   {
      int result = 0;

      // Make an asynchronous call with named arguments
      client->async_call("add", std::tuple{arg("a") = a, arg("b") = b},
                         [&](packio::error_code, const rpc::response_type &r) {
                            std::cout << a << " * " << b << " = " << r.result.get<int>() << std::endl;
                            result = r.result.get<int>();
                         });
      std::cout << "In async call add; a: " << a << "\tb: " << b << "\tResult: " << result << std::endl;
   }
   void async_call_multiply(int a, int b)
   {
      int result = 0;
      // Use packio::net::use_future with named arguments and literals
      client->async_call("multiply", std::tuple{arg("a") = a, arg("b") = b},
                         [&](packio::error_code, const rpc::response_type &r) {
                            std::cout << a << " * " << b << " = " << r.result.get<int>() << std::endl;
                            result = r.result.get<int>();
                         });
      std::cout << "In async call multiply; a: " << a << "\tb: " << b << "\tResult: " << result << std::endl;
   }
};

class MainWindow : public QMainWindow
{
   using packio_client_type = std::shared_ptr<packio::client<pr::rpc, packio::net::ip::tcp::socket>>;
   Q_OBJECT

 protected:
   Ui::MainWindow *ui;

   // Define your custom event subclass
   class MyCustomEvent : public QEvent
   {
    public:
      MyCustomEvent(const int customData1, const int customData2, int button, MyClient *_client)
         : QEvent(MY_CUSTOM_EVENT)
         , m_customData1(customData1)
         , m_customData2(customData2)
      {
        if (button == 1) _client->async_call_add(customData1, customData2);
        else             _client->async_call_multiply(customData1, customData2);
      }

      int getCustomData1() const
      {
         return m_customData1;
      }

      int getCustomData2() const
      {
         return m_customData2;
      }

    private:
      int m_customData1;
      int m_customData2;
   };

 public:
   void postMyCustomEvent(const int customData1, const int customData2, const int button);

 protected:
   void customEvent(QEvent *event);  // This overrides QObject::customEvent()

 private:
   void handleMyCustomEvent(const MyCustomEvent *event);

 public:
   MainWindow(MyClient *);
   ~MainWindow();

 private slots:
   void on_pushButton_clicked();
   void on_pushButton_2_clicked();

 private:
   MyClient *_client;
};
#endif  // MAINWINDOW_H
