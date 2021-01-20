#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "loginwindow.h"

#include <QMenu>
#include <QSystemTrayIcon>
#include <QWidget>
#include <packio/packio.h>

namespace pr = packio::nl_json_rpc;

class MainWindow : public QWidget
{
   using packio_client_type = std::shared_ptr<packio::client<pr::rpc, packio::net::ip::tcp::socket>>;

   Q_OBJECT

 public:
   MainWindow(QWidget *parent, packio_client_type &);
   ~MainWindow();

   void showLoginWindow();

 public slots:
   void sendAddRequest(const int a, const int b);

 signals:
   void summedResult(int result);

 private:
   packio_client_type &_client;

   QSystemTrayIcon *trayIcon;
   QMenu *          trayIconMenu;

   LoginWindow *login;

   QMenu *createMenu();
};
#endif  // MAINWINDOW_H
