#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "app_events.h"

#include <QMenu>
#include <QSystemTrayIcon>
#include <QWidget>
#include <packio/packio.h>

namespace pr = packio::nl_json_rpc;

class MainWindow : public QWidget
{
   using packio_client_type = std::shared_ptr<packio::client<pr::rpc, packio::net::ip::tcp::socket>>;

   Q_OBJECT

 protected:
   void customEvent(QEvent *event);

 public:
   MainWindow(QWidget *parent, packio_client_type &);
   ~MainWindow();

   void postAddResult(const int &result);

 public slots:
   void iconActivated(QSystemTrayIcon::ActivationReason);

 private:
   void handleAddRequestEvent(const AddRequestEvent *event);
   void showLoginWindow();

 private:
   packio_client_type &_client;

   QSystemTrayIcon *trayIcon;
   QMenu *          trayIconMenu;

   QMenu *createMenu();
};
#endif  // MAINWINDOW_H
