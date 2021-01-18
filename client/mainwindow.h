#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "app_events.h"

#include <QMainWindow>
#include <packio/packio.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}  // namespace Ui
QT_END_NAMESPACE

namespace pr = packio::nl_json_rpc;

class MainWindow : public QMainWindow
{
   using packio_client_type = std::shared_ptr<packio::client<pr::rpc, packio::net::ip::tcp::socket>>;

   Q_OBJECT

 public:
   void postAddResult(const int &result);

 protected:
   void customEvent(QEvent *event);

 private:
   void handleAddResultEvent(const AddResultEvent *event);

 public:
   MainWindow(packio_client_type &);
   ~MainWindow();

 private slots:
   void on_addButton_clicked();

 private:
   packio_client_type &_client;
   Ui::MainWindow *    ui;
};
#endif  // MAINWINDOW_H
