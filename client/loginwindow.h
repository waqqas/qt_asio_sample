#ifndef LOGINWINDO_H
#define LOGINWINDO_H

#include <QMainWindow>
#include <QMovie>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginWindow;
}  // namespace Ui
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
   Q_OBJECT

 public:
   LoginWindow(QWidget *parent);
   ~LoginWindow();

 private slots:
   void on_addButton_clicked();
   void showWaitingMessage(int, int);
   void showLoadingGif();
  
 public slots:
   void setAddResult(int result);
   void clearWaitingMessage();
   void clearLoader();
  
  signals:
  void addOperationRequested(int a, int b);

 private:
   Ui::LoginWindow *ui;
};
#endif  // LOGINWINDO_H
