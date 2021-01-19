#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

using packio::arg;
using packio::nl_json_rpc::make_client;
using packio::nl_json_rpc::rpc;

MainWindow::MainWindow(QWidget *parent, MainWindow::packio_client_type &client)
   : QWidget(parent)
   , _client(client)
   , trayIcon(new QSystemTrayIcon(this))
   , login(new LoginWindow(this))
{
   // Tray icon menu
   auto menu = this->createMenu();
   this->trayIcon->setContextMenu(menu);

   // App icon
   auto appIcon = QIcon(":/icons/heart.png");
   this->trayIcon->setIcon(appIcon);
   this->setWindowIcon(appIcon);

   // Displaying the tray icon
   this->trayIcon->show();

   // Interaction
   connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::iconActivated);
}

MainWindow::~MainWindow()
{
   delete login;
   delete trayIcon;
}

QMenu *MainWindow::createMenu()
{
   auto menu = new QMenu(this);

   auto loginAction = new QAction("&Login", this);
   connect(loginAction, &QAction::triggered, this, &MainWindow::showLoginWindow);
   menu->addAction(loginAction);

   auto quitAction = new QAction("&Quit", this);
   connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
   menu->addAction(quitAction);

   return menu;
}

void MainWindow::showLoginWindow()
{
   if (!login->isVisible())
   {
      login->show();
   }
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason_)
{
   switch (reason_)
   {
   case QSystemTrayIcon::Trigger:
      // this->trayIcon->showMessage("Hello", "You clicked me!");
      break;
   default:;
   }
}

void MainWindow::postAddResult(const int &result)
{
   QApplication::postEvent(login, new AddResultEvent(result));
}

void MainWindow::customEvent(QEvent *event)
{
#pragma GCC diagnostic ignored "-Wswitch"
   switch (event->type())
   {
   case ADD_REQUEST_EVENT:
      qDebug() << "Main: ADD_REQUEST_EVENT";
      handleAddRequestEvent(static_cast<AddRequestEvent *>(event));
      break;
   }
}

void MainWindow::handleAddRequestEvent(const AddRequestEvent *event)
{
   _client->async_call("add", std::tuple{arg("a") = event->param1(), arg("b") = event->param2()},
                       [&](packio::error_code, const rpc::response_type &r) { postAddResult(r.result.get<int>()); });
}