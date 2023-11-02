#include "renter_search.h"
#include "ui_renter_search.h"
#include "renter_menu.h"
#include "qsqlquery.h"
#include "qsqlquerymodel.h"
#include "ui_renter_menu.h"
#include<QSql>
#include<QSqlDatabase>
#include<renter_add.h>
#include<QMessageBox>
#include<admin_after_login.h>
#include<renter_edit.h>
#include<renter_delete.h>

renter_search::renter_search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::renter_search)
{

    ui->setupUi(this);

}

renter_search::~renter_search()
{
    delete ui;
}


void renter_search::on_pushButton_search_clicked()
{



    QString val= ui->lineEdit_search->text();
    if(val=="")
    {
        QMessageBox::warning(this,"RENTER","PLEASE INSERT DATA");
    }
    else
    {
    QSqlQuery qy(QSqlDatabase::database("myconnect"));
    QSqlQuery qy1(QSqlDatabase::database("myconnect"));
    QSqlQuery qy2(QSqlDatabase::database("myconnect"));
    QSqlQuery qy3(QSqlDatabase::database("myconnect"));
  //qy.prepare("select * from renter(FLAT,H_ADDRESS,MOBILE,NID,NAME)""values(:flat,:H_ADDRESS,:MOBILE,:nid,:name)");
   qy.prepare("select * from renter where NID='"+val+"'");
   qy2.prepare("select * from OLD_RENTER where NID='"+val+"'");
   if(qy.exec())
   {
       if(qy.next())
        {
           QString val1=qy.value(0).toString();
       ui->lineEdit_flat->setText(qy.value(0).toString());
      ui->lineEdit_H_ADDRESS->setText(qy.value(4).toString());
      ui->lineEdit_MOBILE->setText(qy.value(2).toString());
      ui->lineEdit_nid->setText(qy.value(3).toString());
      ui->lineEdit_name->setText(qy.value(1).toString());
       ui->lineEdit_RENT_AMOUNT->setText(qy.value(5).toString());
        ui->lineEdit_due->setText(qy.value(6).toString());
       ui->lineEdit_ADVANCE->setText(qy.value(7).toString());
        ui->lineEdit_date->setText(qy.value(8).toString());

           qy1.prepare("select * from trans where FLAT='"+val1+"'");
           qy3.prepare("select * from RENT_DATA where FLAT='"+val1+"'");

           if(!qy1.exec())
           {
                QMessageBox::warning(this,"RENTER","DATABASE QUERY NOT OPENED");
           }
           else {
               while(ui->tableWidget->rowCount() > 0)
               {
                  ui->tableWidget->removeRow(0);
               }
               while (ui->tableWidget_2->rowCount() > 0)
               {
                  ui->tableWidget_2->removeRow(0);
               }
               ui->tableWidget->setColumnCount(3);
               ui->tableWidget_2->setColumnCount(3);
               QStringList labels,labels2;
               labels<<"TRANSACTION ID"<<"DATE"<<"PAYMENT";
               ui->tableWidget->setHorizontalHeaderLabels(labels);
               labels2<<"MONTH"<<"RENT"<<"STATUS";
               ui->tableWidget_2->setHorizontalHeaderLabels(labels2);
               int rowcount=0,rowcount2=0;

               while(qy1.next())
               {
                   //if(qy1.value(3)==val1)
                 //  {
                   ui->tableWidget->insertRow(rowcount);

                    QTableWidgetItem *id= new QTableWidgetItem;
                    QTableWidgetItem *date= new QTableWidgetItem;
                    QTableWidgetItem *payment= new QTableWidgetItem;


                    id->setText(qy1.value(0).toString());
                    date->setText(qy1.value(1).toString());
                    payment->setText(qy1.value(2).toString());

                    ui->tableWidget->setItem(rowcount,0,id);
                    ui->tableWidget->setItem(rowcount,1,date);
                    ui->tableWidget->setItem(rowcount,2,payment);

                    rowcount++;
                  // }
                 //  else
                 //  {
                 //       rowcount++;
                 //  }
               }
               if(!qy3.exec())
               {
                    QMessageBox::warning(this,"RENTER","DATABASE QUERY NOT OPENED");
               }
               else
               {
             while(qy3.next())
              {
                   qDebug()<<qy3.value(7)<<val1;
                //  if(qy3.value(7)==val1)
               //  {
                   ui->tableWidget_2->insertRow(rowcount2);

                    QTableWidgetItem *month= new QTableWidgetItem;
                    QTableWidgetItem *rent= new QTableWidgetItem;
                    QTableWidgetItem *status= new QTableWidgetItem;


                    month->setText(qy3.value(0).toString());
                    rent->setText(qy3.value(8).toString());
                    status->setText(qy3.value(9).toString());


                    ui->tableWidget_2->setItem(rowcount2,0,month);
                    ui->tableWidget_2->setItem(rowcount2,1,rent);
                    ui->tableWidget_2->setItem(rowcount2,2,status);


                    rowcount2++;
                /*  }
                  else
                  {
                       rowcount2++;
                  }
                  */

              }
            }
           }
       }
       else if(qy2.exec())
       {
           if(qy2.next())
            {
           ui->lineEdit_flat->setText(qy2.value(0).toString());
          ui->lineEdit_H_ADDRESS->setText(qy2.value(4).toString());
          ui->lineEdit_MOBILE->setText(qy2.value(2).toString());
          ui->lineEdit_nid->setText(qy2.value(3).toString());
          ui->lineEdit_name->setText(qy2.value(1).toString());
           ui->lineEdit_RENT_AMOUNT->setText(qy2.value(5).toString());
            ui->lineEdit_due->setText(qy2.value(6).toString());
           ui->lineEdit_ADVANCE->setText(qy2.value(7).toString());
            ui->lineEdit_date->setText(qy2.value(8).toString());

               qy1.prepare("select * from trans where FLAT='"+val+"'");
               if(!qy1.exec())
               {
                    QMessageBox::warning(this,"RENTER","DATABASE QUERY NOT OPENED");
               }
               else {
                   while (ui->tableWidget->rowCount() > 0)
                   {
                      ui->tableWidget->removeRow(0);
                   }
                   ui->tableWidget->setColumnCount(3);
                   QStringList labels;
                   labels<<"TRANSACTION ID"<<"DATE"<<"PAYMENT";
                   ui->tableWidget->setHorizontalHeaderLabels(labels);

                   int rowcount=0;

                   while(qy1.next())
                   {
                       if(qy1.value(3)==val)
                       {
                       ui->tableWidget->insertRow(rowcount);

                        QTableWidgetItem *id= new QTableWidgetItem;
                        QTableWidgetItem *date= new QTableWidgetItem;
                        QTableWidgetItem *payment= new QTableWidgetItem;


                        id->setText(qy1.value(0).toString());
                        date->setText(qy1.value(1).toString());
                        payment->setText(qy1.value(2).toString());


                        ui->tableWidget->setItem(rowcount,0,id);
                        ui->tableWidget->setItem(rowcount,1,date);
                        ui->tableWidget->setItem(rowcount,2,payment);


                        rowcount++;
                       }
                       else
                       {
                            rowcount++;
                       }
                   }

               }

       }

       else
       {
            QMessageBox::warning(this,"RENTER","RENTER NOT FOUND");
       }


    }

       else
       {
           QMessageBox::warning(this,"RENTER","RENTER NOT FOUND");
       }




    }


}
}


void renter_search::on_pushButton_BACK_clicked()
{
    hide();
    admin_after_login ad;
    ad.setModal(true);
    ad.exec();
}

