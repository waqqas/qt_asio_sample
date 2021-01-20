#include "mainwindow.h"

#include <QApplication>

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
   connect(login, &LoginWindow::addRequested, this, &MainWindow::sendAddRequest);
   connect(this, &MainWindow::summedResult, login, &LoginWindow::updateResult);
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

void MainWindow::sendAddRequest(const int a, const int b)
{
   _client->async_call("add", std::tuple{arg("a") = a, arg("b") = b},
                       [&](packio::error_code, const rpc::response_type &r) { emit summedResult(r.result.get<int>()); });
}