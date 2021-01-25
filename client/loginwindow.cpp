#include "loginwindow.h"

#include "./ui_loginwindow.h"

#include <QDebug>

LoginWindow::LoginWindow(QWidget *parent)
   : QMainWindow(parent)
   , ui(new Ui::LoginWindow)
{
   ui->setupUi(this);
   // connect(this, &LoginWindow::addOperationRequested, parent, &MainWindow::postAddOperationRequest); // FIXME
   connect(this, SIGNAL(addOperationRequested(int, int)), parent, SLOT(postAddOperationRequest(int,int)));
   connect(this, &LoginWindow::addOperationRequested, this, &LoginWindow::showWaitingMessage);
   connect(this, &LoginWindow::addOperationRequested, this, &LoginWindow::showLoadingGif);
}

LoginWindow::~LoginWindow()
{
   delete ui;
}

void LoginWindow::on_addButton_clicked()
{
   int a = ui->input1->toPlainText().toInt();
   int b = ui->input2->toPlainText().toInt();

   emit addOperationRequested(a,b);
}

void LoginWindow::showWaitingMessage(int a, int b)
{
   ui->message->setText("Please Wait");
   ui->addOutput->setText(""); 
}

void LoginWindow::showLoadingGif()
{
   QDir buildDirectoryPath = QDir::current();
   buildDirectoryPath.cdUp();
   QString projectDirectoryPath = buildDirectoryPath.path();
   
   QMovie *movie = new QMovie(projectDirectoryPath + "/loader.gif");

   ui->loader->setMovie(movie);
   ui->loader->show();
   movie->start(); 
}

void LoginWindow::setAddResult(int result)
{
   ui->addOutput->setText(QString::number(result));  
}

void LoginWindow::clearWaitingMessage()
{
   ui->message->clear();  
}

void LoginWindow::clearLoader()
{
   ui->loader->clear();
}