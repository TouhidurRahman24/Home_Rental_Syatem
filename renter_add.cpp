#include "renter_add.h"
#include "qsqlquery.h"
#include "ui_renter_add.h"
#include<QSql>
#include<QSqlDatabase>
#include<QMessageBox>
#include<renter_menu.h>
renter_add::renter_add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::renter_add)
{
    ui->setupUi(this);

}

renter_add::~renter_add()
{
    delete ui;
}

void renter_add::on_pushButton_ADD_clicked()
{

   QSqlDatabase db= QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/sqlitestudio/database/faisal_sql.sqlite");


    if(db.open())
    {

        QString flat=ui->lineEdit_flat->text();
        QString username= ui->lineEdit_username->text();
        QString password= ui->lineEdit_password->text();
        QString nid=ui->lineEdit_nid->text();
        QString name=ui->lineEdit_4->text();

        QSqlQuery qy;
      qy.prepare("insert into renter(FLAT,USERNAME,PASSWORD,NID,NAME)""values(:flat,:username,:password,:nid,:name)");
      qy.bindValue(":flat",flat);
      qy.bindValue(":username",username);
      qy.bindValue(":password",password);
      qy.bindValue(":nid",nid);
      qy.bindValue(":name",name);
      if(qy.exec())
      {
          QMessageBox::information(this,"database","INSERTED INTO DATABASE");
      }
      else
      {
          QMessageBox::warning(this,"database","NOT INSERTED INTO DATABASE");
      }
    }
    else
    {
         QMessageBox::warning(this,"database","DATABASE NOT OPENED");
    }
}


void renter_add::on_pushButton_back_clicked()
{
    hide();
    renter_menu re;
    re.setModal(true);
    re.exec();
}

