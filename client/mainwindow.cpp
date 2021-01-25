#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <unistd.h>

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
   connect(this, &MainWindow::addResultRequested, login, &LoginWindow::setAddResult);
   connect(this, &MainWindow::addResultRequested, login, &LoginWindow::clearWaitingMessage);
   connect(this, &MainWindow::addResultRequested, login, &LoginWindow::clearLoader);
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
   usleep(1000000); // FIXME Only here to test the wait feature
   emit addResultRequested(result);
}

void MainWindow::postAddOperationRequest(int a, int b) {

  _client->async_call("add", std::tuple{arg("a") = a, arg("b") = b},
                       [&](packio::error_code, const rpc::response_type &r) { postAddResult(r.result.get<int>()); });
}
