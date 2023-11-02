#include "renter_edit.h"
#include "qsqlquery.h"
#include "ui_renter_edit.h"
#include<QSql>
#include<QMessageBox>
#include<QSqlDatabase>
renter_edit::renter_edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::renter_edit)
{
    ui->setupUi(this);
}

renter_edit::~renter_edit()
{
    delete ui;
}

void renter_edit::on_pushButton_edit_clicked()
{
    QSqlQuery qy(QSqlDatabase::database("myconnect"));

   // QSqlDatabase db= QSqlDatabase::addDatabase("QSQLITE");
    //   db.setDatabaseName("C:/sqlitestudio/database/faisal_sql.sqlite");
      // if(db.open())
      // {
       QString flat=ui->lineEdit_FLAT->text();
       QString username= ui->lineEdit_username->text();
       QString password= ui->lineEdit_password->text();
       QString nid=ui->lineEdit_nid->text();
       QString name=ui->lineEdit_4->text();

       //QSqlQuery qy;
        qy.prepare(QString("UPDATE renter set NAME=:name, USERNAME=:username,PASSWORD=:password,NID=:nid where FLAT= :flat "));
     //qy.prepare("update renter set USERNAME='"+username+"',PASSWORD='"+password+"',NAME='"+name+"',NID='"+nid+"' where FLAT='"+flat+"'");
    // qy.prepare("UPDATE renter SET(FLAT,USERNAME,PASSWORD,NID,NAME) where FLAT="+flat+"values(:flat,:username,:password,:nid,:name)");
       //qy.prepare("update renter set NAME=':name',USERNAME=':username',PASSWORD=':password',NID=':nid' where FLAT=':flat'");
       qy.bindValue(":flat",flat);
       qy.bindValue(":username",username);
       qy.bindValue(":password",password);
       qy.bindValue(":nid",nid);
       qy.bindValue(":name",name);
     if(qy.exec())
     {

         QMessageBox::information(this,"building","UPDATED");
     }
     else
     {
         QMessageBox::warning(this,"building","DATABASE QUERY  NOT HAPPENED");
     }
   // }
    //   else
     //  {
    //        QMessageBox::warning(this,"building","DATABASE  NOT OPENED");
    //   }

}

