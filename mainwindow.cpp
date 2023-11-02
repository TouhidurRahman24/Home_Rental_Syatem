#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<admin_login.h>
#include<QMessageBox>
#include<admin_mainmenu.h>
#include<admin_after_login.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_admin_clicked()
{
    QSqlDatabase db= QSqlDatabase::addDatabase("QSQLITE","myconnect");
    db.setDatabaseName("C:/sqlitestudio/database/faisal_sql.sqlite");

    hide();
    admin_mainmenu admin;
    admin.setModal(true);
    admin.exec();
}




