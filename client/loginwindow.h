#ifndef LOGINWINDO_H
#define LOGINWINDO_H

#include <QMainWindow>

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

 signals:
   void addRequested(int a, int b);
 public slots:
   void updateResult(int result);

 private slots:
   void on_addButton_clicked();

 private:
   Ui::LoginWindow *ui;
};
#endif  // LOGINWINDO_H
