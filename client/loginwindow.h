#ifndef LOGINWINDO_H
#define LOGINWINDO_H

#include "app_events.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginWindow;
}  // namespace Ui
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
   Q_OBJECT

 protected:
   void customEvent(QEvent *event);

 private:
   void handleAddResultEvent(const AddResultEvent *event);

 public:
   LoginWindow(QWidget *parent);
   ~LoginWindow();

 private slots:
   void on_addButton_clicked();

 private:
   Ui::LoginWindow *ui;
};
#endif  // LOGINWINDO_H
