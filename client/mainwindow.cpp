#include "mainwindow.h"

#include "./ui_mainwindow.h"

using packio::arg;
using packio::nl_json_rpc::make_client;
using packio::nl_json_rpc::rpc;

MainWindow::MainWindow(QWidget *parent, MainWindow::packio_client_type &client)
   : QMainWindow(parent)
   , _client(client)
   , ui(new Ui::MainWindow)
   , trayIcon(new QSystemTrayIcon(this))
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
   delete ui;
}

QMenu *MainWindow::createMenu()
{
   // App can exit via Quit menu
   auto quitAction = new QAction("&Quit", this);
   connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

   auto menu = new QMenu(this);
   menu->addAction(quitAction);

   return menu;
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason_)
{
   switch (reason_)
   {
   case QSystemTrayIcon::Trigger:
      this->trayIcon->showMessage("Hello", "You clicked me!");
      break;
   default:;
   }
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