#include "maintenance.h"
#include "ui_maintenance.h"
#include<maintenance.h>
#include<QTimer>
#include<QSqlDatabase>
#include<QSql>
#include<QSqlQuery>
#include<QMessageBox>
#include<admin_after_login.h>
#include<QString>
#include<QDateTime>
MAINTENANCE::MAINTENANCE(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MAINTENANCE)
{
    ui->setupUi(this);
    QSqlQuery query1(QSqlDatabase::database("myconnect"));
    query1.prepare("DELETE FROM MAINTENANCE");
    query1.exec();
}
MAINTENANCE::~MAINTENANCE()
{
    delete ui;
}

void MAINTENANCE::on_pushButton_ADD_clicked()
{
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(on_pushButton_ADD_clicked()));
    timer->start();

        QString flat=ui->lineEdit_FLAT->text().toUpper();
        int bill=ui->lineEdit_BILL->text().toInt();
        QString issue=ui->lineEdit_ISSUE->text();
        int percentage= ui->lineEdit_PERCENTAGE->text().toInt();
        int total=bill*percentage/100;

    QSqlDatabase db= QSqlDatabase::addDatabase("QSQLITE","myconnect");
 db.setDatabaseName("D:/CODEBLOCKS/qt projects/untitled/faisal_sql.sqlite");
   if(db.open())
   {

       QSqlQuery query(db);
       QSqlQuery query1(db);
     query1.prepare("insert into MAINTENANCE(FLAT,ISSUE,BILL,PERCENTAGE,RENTER_BILL)""values(:flat,:bill,:issue,:percentage,:total)");
     query1.bindValue(":flat",flat);
     query1.bindValue(":bill",bill);
     query1.bindValue(":issue",issue);
     query1.bindValue(":percentage",percentage);
     query1.bindValue(":total",total);
     query1.exec();


     query.prepare("select * from MAINTENANCE");



     if(!query.exec())
       {
            QMessageBox::warning(this,"MAINTENANCE","DATABASE QUERY NOT OPENED");
       }
       else {
           ui->tableWidget->setColumnCount(5);
           QStringList labels;
           labels<<"FLAT"<<"ISSUE"<<"BILL"<<"PERCENTAGE"<<"RENTER BILL";
           ui->tableWidget->setHorizontalHeaderLabels(labels);

           while (ui->tableWidget->rowCount() > 0)
                             {
                                ui->tableWidget->removeRow(0);
                             }
           int rowcount=0;

           while(query.next())
           {

               ui->tableWidget->insertRow(rowcount);
                QTableWidgetItem *flat= new QTableWidgetItem;
                QTableWidgetItem *bill= new QTableWidgetItem;
                QTableWidgetItem *issue= new QTableWidgetItem;
                QTableWidgetItem *percentage= new QTableWidgetItem;
                QTableWidgetItem *total= new QTableWidgetItem;


                flat->setText(query.value(0).toString());
                bill->setText(query.value(1).toString());
                issue->setText(query.value(2).toString());
                percentage->setText(query.value(3).toString());
                total->setText(query.value(4).toString());


                ui->tableWidget->setItem(rowcount,0,flat);
                ui->tableWidget->setItem(rowcount,1,bill);
                ui->tableWidget->setItem(rowcount,2,issue);
                ui->tableWidget->setItem(rowcount,3,percentage);
                ui->tableWidget->setItem(rowcount,4,total);

                 QSqlQuery query2(db);
                  query2.prepare("select SUM(RENTER_BILL) from MAINTENANCE");
                  query2.exec();
                  if(query2.next())
                  {

                 ui->lineEdit_TOTAL->setText(query2.value(0).toString());

                    }
                rowcount++;
           }
           timer->stop();
           db.close();
       }
   }
   else
   {
       QMessageBox::warning(this,"MAINTENANCE","DATABASE NOT OPENED");
   }



}


void MAINTENANCE::on_pushButton_back_clicked()
{
    hide();
    admin_after_login ad;
    ad.setModal(true);
    ad.exec();
}


void MAINTENANCE::on_pushButton_clear_2_clicked()
{
    ui->lineEdit_FLAT->setText("");
    ui->lineEdit_BILL->setText("");
    ui->lineEdit_ISSUE->setText("");
    ui->lineEdit_PERCENTAGE->setText("");
}


void MAINTENANCE::on_pushButton_clear_clicked()
{

  QSqlQuery query1(QSqlDatabase::database("myconnect"));
  query1.prepare("DELETE FROM MAINTENANCE");
  query1.exec();
  while(ui->tableWidget->rowCount()>0)
                    {
                       ui->tableWidget->removeRow(0);
                    }
  ui->lineEdit_TOTAL->setText("");
  ui->lineEdit_FLAT->setText("");
  ui->lineEdit_BILL->setText("");
  ui->lineEdit_ISSUE->setText("");
  ui->lineEdit_PERCENTAGE->setText("");
}


void MAINTENANCE::on_pushButton_ADMIT_clicked()
{

    QDateTime dateTime = dateTime.currentDateTime();
    QString as = dateTime.toString("MM/yyyy");
    QString flat=ui->lineEdit_FLAT->text().toUpper();
     int DUE=0,advance=0;
     int rent_now=ui->lineEdit_TOTAL->text().toInt();
     QSqlQuery qy(QSqlDatabase::database("myconnect"));
     QSqlQuery qy1(QSqlDatabase::database("myconnect"));
     QSqlQuery qy2(QSqlDatabase::database("myconnect"));
     QSqlQuery qy3(QSqlDatabase::database("myconnect"));

     qy1.prepare("select * from renter where FLAT=:flat");
     qy1.bindValue(":flat",ui->lineEdit_FLAT->text().toUpper());
     qy1.exec();
     while(qy1.next())
     {
     DUE=qy1.value(6).toInt();
     QSqlQuery qy4(QSqlDatabase::database("myconnect"));
     QSqlQuery qy5(QSqlDatabase::database("myconnect"));
      QSqlQuery qy6(QSqlDatabase::database("myconnect"));
     qy4.prepare("select * from ADVANCE where FLAT=:flat AND STATUS=:add");
     qy4.bindValue(":flat",flat);
     qy4.bindValue(":add","NOT ADDED");
     qy4.exec();
     while(qy4.next())
     {
            advance=advance+qy4.value(2).toInt();
     }

     rent_now=rent_now-advance;

     qy5.prepare(QString("UPDATE ADVANCE set STATUS=:add,AMOUNT=:amount where FLAT=:flat"));
     qy5.bindValue(":flat",flat);
     qy5.bindValue(":amount",ui->lineEdit_TOTAL->text());
     qy5.bindValue(":add","ADDED");
     qy5.exec();
     if(rent_now<0)
     {
     qint64 AD_DUE=abs(rent_now);
     QString add_due=QString::number(AD_DUE);
     qy6.prepare("insert into ADVANCE(FLAT,DATE,AMOUNT,STATUS)""values(:flat,:date,:amount,:add)");
     qy6.bindValue(":flat",flat);
     qy6.bindValue(":add","NOT ADDED");
     qy6.bindValue(":date",dateTime.toString());
     qy6.bindValue(":amount",add_due);
     qy6.exec();
     rent_now=0;
     }

     QString payment;
     DUE=DUE+rent_now;
     QString month_rent=QString::number(rent_now);

     if(rent_now>0)
     {
    payment="NOT PAID";
     }
     else if(rent_now<=0)
     {
          payment="PAID";
         rent_now=0;
     }


     QString due=QString::number(DUE);
     qy2.prepare(QString("update renter set DUE=:due  where FLAT=:flat"));
     qy2.bindValue(":due",due);
     qy2.bindValue(":flat",flat);
     qy.prepare("insert into MTN_BILL(FLAT,DATE,BILL,STATUS)""values(:flat,:date,:due,:payment)");
     qy.bindValue(":flat",ui->lineEdit_FLAT->text().toUpper());
     qy.bindValue(":payment",payment);
     qy.bindValue(":date",as);
     qy.bindValue(":due",rent_now);
     if(qy.exec() && qy2.exec())
     {
         QSqlQuery query1(QSqlDatabase::database("myconnect"));
         query1.prepare("DELETE FROM MAINTENANCE");
         query1.exec();
         while(ui->tableWidget->rowCount()>0)
                           {
                              ui->tableWidget->removeRow(0);
                           }
         ui->lineEdit_TOTAL->setText("");
         ui->lineEdit_FLAT->setText("");
         ui->lineEdit_BILL->setText("");
         ui->lineEdit_ISSUE->setText("");
         ui->lineEdit_PERCENTAGE->setText("");
         QMessageBox::information(this,"MAINTENANCE","UPDATED");
     }
     else
     {
          QMessageBox::warning(this,"MAINTENANCE","NOT UPDATED");
     }





    }
}


