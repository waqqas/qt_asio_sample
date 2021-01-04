#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <packio/packio.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace pr = packio::nl_json_rpc;

class MainWindow : public QMainWindow
{
   using packio_client_type = std::shared_ptr<packio::client<pr::rpc, packio::net::ip::tcp::socket>>;
   Q_OBJECT

 public:
   MainWindow(packio_client_type &);
   ~MainWindow();

 private:
   Ui::MainWindow *   ui;
   packio_client_type _client;
};
#endif  // MAINWINDOW_H
