#include "transactions.h"
#include "ui_transactions.h"
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
#include<QDateTime>
#include <QApplication>
#include <QtCore>
#include<QPrinter>
#include <QPdfWriter>
#include <QPainter>
#include<QPrintDialog>
#include<QtPrintSupport>
#include<QAbstractPrintDialog>
#include<QMessageBox>
#include<QTimer>
TRANSACTIONS::TRANSACTIONS(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TRANSACTIONS)
{
    hide();
    ui->setupUi(this);

    ui->lineEdit_ID->setFrame(false);
    ui->lineEdit_ID->setReadOnly(true);
    ui->label_invoice->setEnabled(false);
    ui->lineEdit_search_3->setFrame(false);
    ui->lineEdit_search_3->setReadOnly(true);
    ui->label_money->setEnabled(false);


    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(show()));
    timer->start();

}

TRANSACTIONS::~TRANSACTIONS()
{
    delete ui;
}

void TRANSACTIONS::show()
{

    if(ui->radioButton_regular->isChecked())
    {
        ui->lineEdit_ID->setFrame(true);
        ui->lineEdit_ID->setReadOnly(false);
        ui->label_invoice->setEnabled(true);
        ui->lineEdit_search_3->setFrame(true);
        ui->lineEdit_search_3->setReadOnly(false);
        ui->label_money->setEnabled(true);


    }
    else if(ui->radioButton_advance->isChecked())
    {
        ui->lineEdit_search_3->setFrame(true);
        ui->lineEdit_search_3->setReadOnly(false);
        ui->label_money->setEnabled(true);
        ui->lineEdit_ID->setFrame(false);
        ui->lineEdit_ID->setReadOnly(true);
        ui->label_invoice->setEnabled(false);

    }
    else if(ui->radioButton_MAINTENANCE->isChecked())
    {
        ui->lineEdit_ID->setFrame(true);
        ui->lineEdit_ID->setReadOnly(false);
        ui->label_invoice->setEnabled(true);
        ui->lineEdit_search_3->setFrame(true);
        ui->lineEdit_search_3->setReadOnly(false);
        ui->label_money->setEnabled(true);


    }
    else
    {
        ui->lineEdit_ID->setFrame(false);
        ui->lineEdit_ID->setReadOnly(true);
        ui->label_invoice->setEnabled(false);
        ui->lineEdit_search_3->setFrame(false);
        ui->lineEdit_search_3->setReadOnly(true);
        ui->label_money->setEnabled(false);


    }



}


void TRANSACTIONS::on_pushButton_PAYMENT_clicked()
{
    qint64 val_rent,trans_id;
    QString val= ui->lineEdit_search->text().toUpper();
    qint64 val1=ui->lineEdit_search_3->text().toInt();
           rec_amount=QString::number(val1);
           QString invoice=ui->lineEdit_ID->text();
          QString current=QDateTime::currentDateTime().toString();

    QSqlDatabase db= QSqlDatabase::addDatabase("QSQLITE");
db.setDatabaseName("D:/CODEBLOCKS/qt projects/untitled/faisal_sql.sqlite");
     QDateTime dateTime = dateTime.currentDateTime();
     QString dateTimeString = dateTime.toString("yyyy-MM-dd");
     if(db.open())
     {
    QSqlQuery qy(QSqlDatabase::database("myconnect"));
     QSqlQuery qy1(QSqlDatabase::database("myconnect"));
     QSqlQuery qy2(QSqlDatabase::database("myconnect"));
     QSqlQuery qy3(QSqlDatabase::database("myconnect"));
     QSqlQuery qy4(QSqlDatabase::database("myconnect"));
     qy4.prepare("select * from building");
     qy4.exec();
     qy.prepare("select * from renter where FLAT='"+val+"'");
     qy.exec();
     while(qy.next())
     {
     rec_name=qy.value(1).toString();
     rec_phone=qy.value(2).toString();
     val_rent=qy.value(6).toInt();
     }
           while(qy4.next())
     {
         rec_address=qy4.value(1).toString();
         rec_apart_name=qy4.value(0).toString();
     }
     if(ui->lineEdit_search_3->text()==""||ui->lineEdit_search_3->text()=="0")
     {
           QMessageBox::warning(this,"TRANSACTIONS","PLEASE ENTER AMOUNT");
     }
   else if(ui->radioButton_regular->isChecked())
    {

   qy1.prepare("SELECT * FROM trans ORDER BY ID DESC LIMIT 1");
   qy3.prepare("select * from RENT_DATA where FLAT='"+val+"'AND INVOICE='"+invoice+"'");
   if( qy1.exec()&& qy3.exec())
   {


       if( qy1.next()&& qy3.next())
        {

           QString paid=qy3.value(9).toString();
           if(paid!="PAID")
           {
           qint64 month_rent=qy3.value(8).toInt();
            QString month=qy3.value(0).toString();
           month_rent=month_rent-val1;
            val_rent=val_rent-val1;
            if(month_rent>=0)
            {
            if(qy1.value(0).toInt()==0)
            {
                trans_id=10000001;
            }
            else
            {
            trans_id=1+qy1.value(0).toInt();
            }


             qy.prepare(QString("UPDATE renter set DUE=:val_rent where FLAT= :val "));
             qy.bindValue(":val_rent",val_rent);
             qy.bindValue(":val",val);
             qy1.prepare("insert into trans(id,date,amount,FLAT)""values(:trans_id,:dateTimeString,:val1,:val)");
             qy1.bindValue(":val1",val1);
             qy1.bindValue(":trans_id",trans_id);
             qy1.bindValue(":val",val);
             qy1.bindValue(":dateTimeString",current);
              QString payment="PAID";
              if(month_rent!=0)
              {
              qy2.prepare(QString("update RENT_DATA set TOTAL=:val_rent,RENT_TOTAL=:month_rent  where FLAT=:val and INVOICE=:invoice"));
              qy2.bindValue(":val",val);
              qy2.bindValue(":invoice",invoice);
              qy2.bindValue(":val_rent",val_rent);
              qy2.bindValue(":month_rent",month_rent);
              }
              else
              {
                  qy2.prepare(QString("update RENT_DATA set TOTAL=:val_rent,RENT_TOTAL=:month_rent,PAYMENT=:payment  where FLAT=:val and INVOICE=:invoice"));
                  qy2.bindValue(":val",val);
                  qy2.bindValue(":invoice",invoice);
                  qy2.bindValue(":payment",payment);
                  qy2.bindValue(":val_rent",val_rent);
                  qy2.bindValue(":month_rent",month_rent);
              }
             if(qy.exec() && qy1.exec()&&qy2.exec())
             {
                 QMessageBox::information(this,"PAYMENT","PAYMENT SUCCESSFULL");
                 QMessageBox::StandardButton reply;
                 reply=QMessageBox::question(this,"","DO YOU WANT RENT RECEIPT",QMessageBox::Yes | QMessageBox::No );

                if(reply==QMessageBox::Yes)
                {
                     QDateTime dateTime = dateTime.currentDateTime();
                  QString date=dateTime.toString();
                  QString asdate=dateTime.toString("dd_MM_yyyy");
                 QString html =
                         "<!DOCTYPE html>"
                         "<html>"
                         "<head>"
                         "</head>"
                         "<body>"
                         "<pre>"
                         "<form>"
                         "<h3>"
                         "<div>"
                         "<h2>   ["+rec_apart_name+"]</h2>"
                         "<h2> -----RENT RECEIPT-----</h2>"
                           "Flat            : "+val+"<br>"
                           "Name            : "+rec_name+"<br>"
                           "Phone           : "+rec_phone+"<br>"
                           "Rent month      : "+month+"<br>"
                           "Amount received : "+rec_amount+"<br>"
                           "Payment status  : Regular<br>"
                           "Date            : "+date+"<br>"
                           "Address         : "+rec_address+"   "
                         "</div>"
                         "</h3>"
                         "</pre>"
                         "</form>"
                         "</form>"
                         "</form>"
                         "</body>"
                         "</html>";

                 QTextDocument document;
                 document.setHtml(html);
                   QString s=val+"_"+rec_name+"_"+asdate;
                 QPrinter printer(QPrinter::PrinterResolution);
                 printer.setOutputFormat(QPrinter::PdfFormat);
                 printer.setOutputFileName("D:/"+s+".pdf");
                 printer.setPageMargins(QMarginsF(6, 6, 5, 5));
                 document.print(&printer);
                  QMessageBox::information(this,"RENT","RENT RECEIPT ISSUED");
                }



             }
             else
             {
                 QMessageBox::warning(this,"RENT","RENTER NOT FOUND");
             }
                }
            else
            {
                QMessageBox::warning(this,"RENT","PAYMENT IS MORE THAN RENT");
            }
             }
            else
           {
               QMessageBox::warning(this,"RENT","PAYMENT ALREADY PAID");
           }
          }

       else
       {
           QMessageBox::warning(this,"RENT","RENTER NOT FOUND");
       }
   }
   else
   {
        QMessageBox::warning(this,"RENT","UNSUCCESSFULL IN QUERY");
   }
     }

    else if(ui->radioButton_advance->isChecked())
    {
    QDateTime dateTime = dateTime.currentDateTime();
    QString asdate=dateTime.toString("dd-MM-yyyy");
    qint64 due;
    qy2.prepare("select * from renter where FLAT=:flat");
    qy2.bindValue(":flat",val);
    qy2.exec();
    if(qy2.next())
    {

       due=qy2.value(6).toInt();
       QString rent_name=qy2.value(1).toString();
        if(rent_name=="")
        {
            goto here;
        }
    if(due==0 )
    {

        QString ad="NOT ADDED";

         qy.prepare("insert into ADVANCE(FLAT,DATE,STATUS,AMOUNT)""values(:flat,:date,:ad,:amount)");
         qy.bindValue(":flat",val);
         qy.bindValue(":date",asdate);
         qy.bindValue(":amount",val1);
         qy.bindValue(":ad",ad);
         if(qy.exec())
         {
             QMessageBox::information(this,"PAYMENT","PAYMENT SUCCESSFULL");
             QMessageBox::StandardButton reply;
             reply=QMessageBox::question(this,"PAYMENT","DO YOU WANT RENT RECEIPT",QMessageBox::Yes | QMessageBox::No );

            if(reply==QMessageBox::Yes)
            {
                QDateTime dateTime = dateTime.currentDateTime();
             QString date=dateTime.toString();
             QString asdate=dateTime.toString("dd_MM_yyyy");
             QString html =
                     "<!DOCTYPE html>"
                     "<html>"
                     "<head>"
                     "</head>"
                     "<body>"
                     "<pre>"
                     "<form>"
                     "<h3>"
                     "<div>"
                     "<h2>   ["+rec_apart_name+"]</h2>"
                     "<h2> -----RENT RECEIPT-----</h2>"
                       "Flat            : "+val+"<br>"
                       "Name            : "+rec_name+"<br>"
                       "Phone           : "+rec_phone+"<br>"
                       "Amount received : "+rec_amount+"<br>"
                       "Payment status  : Advance<br>"
                       "Date            : "+date+"<br>"
                       "Address         : "+rec_address+"   "
                     "</div>"
                     "</h3>"
                     "</pre>"
                     "</form>"
                     "</form>"
                     "</form>"
                     "</body>"
                     "</html>";

             QTextDocument document;
             document.setHtml(html);
               QString s=val+"_"+rec_name+"_"+asdate;
             QPrinter printer(QPrinter::PrinterResolution);
             printer.setOutputFormat(QPrinter::PdfFormat);
             printer.setOutputFileName("D:/"+s+".pdf");
             printer.setPageMargins(QMarginsF(6, 6, 5, 5));
             document.print(&printer);
              QMessageBox::information(this,"RENT","RENT RECEIPT ISSUED");
            }

         }
         else
         {
             QMessageBox::warning(this,"RENT","query not happen");
         }
        }
       else
    {
        QMessageBox::warning(this,"RENT","PLEASE CLEAR DUE FIRST");
    }
    }
    else
    {
        here:
        QMessageBox::warning(this,"RENT","RENTER NOT FOUND");
    }
    }
    else if(ui->radioButton_MAINTENANCE->isChecked())
    {
       int bill=0;
         qy.prepare("select * from MTN_BILL where  FLAT='"+val+"'");
         qy.exec();
       QString invoice,paid;
         while(qy.next())
         {
            bill=qy.value(2).toInt();
            invoice=qy.value(4).toString();
            paid=qy.value(3).toString();
         }
         if(paid!="PAID")
         {
        bill=bill-val1;

            if(bill>=0)
            {
            val_rent=val_rent-val1;
            qy2.prepare(QString("UPDATE renter set DUE=:val_rent where FLAT=:flat "));
            qy2.bindValue(":val_rent",val_rent);
            qy2.bindValue(":flat",val);
            if(bill==0)
            {
         QString paid="PAID";
         qy1.prepare(QString("update MTN_BILL set BILL=:bill,STATUS=:PAID WHERE INVOICE= :invoice"));
         qy1.bindValue(":PAID",paid);
         qy1.bindValue(":bill",bill);
         qy1.bindValue(":invoice",invoice);
         if(qy1.exec()&&qy2.exec())
         {
             QMessageBox::information(this,"RENT","PAYMENT SUCCESSFULL");
             QMessageBox::StandardButton reply;
             reply=QMessageBox::question(this,"PAYMENT","DO YOU WANT RENT RECEIPT",QMessageBox::Yes | QMessageBox::No );

            if(reply==QMessageBox::Yes)
            {
                QDateTime dateTime = dateTime.currentDateTime();
             QString date=dateTime.toString();
             QString asdate=dateTime.toString("dd_MM_yyyy");
             QString html =
                     "<!DOCTYPE html>"
                     "<html>"
                     "<head>"
                     "</head>"
                     "<body>"
                     "<pre>"
                     "<form>"
                     "<h3>"
                     "<div>"
                     "<h2>   ["+rec_apart_name+"]</h2>"
                     "<h2> -----RENT RECEIPT-----</h2>"
                       "Flat            : "+val+"<br>"
                       "Name            : "+ rec_name +"<br>"
                       "Phone           : "+rec_phone+"<br>"
                       "Amount received : "+rec_amount+"<br>"
                       "Payment status  : Maintenance<br>"
                       "Date            : "+date+"<br>"
                       "Address         : "+rec_address+"   "
                     "</div>"
                     "</h3>"
                     "</pre>"
                     "</form>"
                     "</form>"
                     "</form>"
                     "</body>"
                     "</html>";

             QTextDocument document;
             document.setHtml(html);
                QString s=val+"_"+rec_name+"_"+asdate;
             QPrinter printer(QPrinter::PrinterResolution);
             printer.setOutputFormat(QPrinter::PdfFormat);
             printer.setOutputFileName("D:/"+s+".pdf");
             printer.setPageMargins(QMarginsF(6, 6, 5, 5));
             document.print(&printer);
              QMessageBox::information(this,"RENT","RENT RECEIPT ISSUED");
            }
         }
         else
         {
             QMessageBox::warning(this,"RENT","SORRY ACCEPT FULL PAYMENT ONLY");
         }
        }
        else
        {
                qy1.prepare(QString("update MTN_BILL set BILL=:bill WHERE INVOICE= :invoice"));

                qy1.bindValue(":bill",bill);
                qy1.bindValue(":invoice",invoice);

            if(qy1.exec())
            {
                QMessageBox::information(this,"RENT","PAYMENT SUCCESSFULL");
                QMessageBox::StandardButton reply;
                reply=QMessageBox::question(this,"PAYMENT","DO YOU WANT RENT RECEIPT",QMessageBox::Yes | QMessageBox::No );

               if(reply==QMessageBox::Yes)
               {
                   QDateTime dateTime = dateTime.currentDateTime();
                QString date=dateTime.toString();
                QString asdate=dateTime.toString("dd_MM_yyyy");
                QString html =
                        "<!DOCTYPE html>"
                        "<html>"
                        "<head>"
                        "</head>"
                        "<body>"
                        "<pre>"
                        "<form>"
                        "<h3>"
                        "<div>"
                        "<h2>   ["+rec_apart_name+"]</h2>"
                        "<h2> -----RENT RECEIPT-----</h2>"
                          "Flat            : "+val+"<br>"
                          "Name            : "+ rec_name +"<br>"
                          "Phone           : "+rec_phone+"<br>"
                          "Amount received : "+rec_amount+"<br>"
                          "Payment status  : Maintenance<br>"
                          "Date            : "+date+"<br>"
                          "Address         : "+rec_address+"   "
                        "</div>"
                        "</h3>"
                        "</pre>"
                        "</form>"
                        "</form>"
                        "</form>"
                        "</body>"
                        "</html>";

                QTextDocument document;
                document.setHtml(html);
                   QString s=val+"_"+rec_name+"_"+asdate;
                QPrinter printer(QPrinter::PrinterResolution);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setOutputFileName("D:/"+s+".pdf");
                printer.setPageMargins(QMarginsF(6, 6, 5, 5));
                document.print(&printer);
                 QMessageBox::information(this,"RENT","RENT RECEIPT ISSUED");
               }
            }
            else
            {
                QMessageBox::warning(this,"RENT","RENTER QUERY NOT HAPPENNED");
            }
        }
        }
           else
            {
                QMessageBox::warning(this,"RENT","PAYMENT IS MORE THAN BILL");
            }
         }
         else
         {
              QMessageBox::warning(this,"RENT","PAYMENT IS ALREADY PAID");
         }
    }
    else
    {
        QMessageBox::warning(this,"","PLEASE SELECT PAYMENT TYPE");
    }

     }

     else
     {
         QMessageBox::warning(this,"","database not opened");
     }
}


void TRANSACTIONS::on_pushButton_BACK_clicked()
{
    hide();
    admin_after_login ad;
    ad.setModal(true);
    ad.exec();
}




void TRANSACTIONS::on_pushButton_SEARCH_clicked()
{
    QString val= ui->lineEdit_search->text().toUpper();
    QSqlQuery qy(QSqlDatabase::database("myconnect"));
    QSqlQuery qy1(QSqlDatabase::database("myconnect"));
    QSqlQuery qy2(QSqlDatabase::database("myconnect"));
    QSqlQuery qy3(QSqlDatabase::database("myconnect"));
  qy.prepare("select * from renter where NAME IS NOT NULL AND FLAT='"+val+"'");
   if(qy.exec())
   {

       if(qy.next())
        {


           qy1.prepare("select * from RENT_DATA where FLAT='"+val+"'");
           qy2.prepare("select * from MTN_BILL where FLAT='"+val+"'");
           qy3.prepare("select * from ADVANCE where FLAT='"+val+"'");
           if(!qy1.exec())
           {
                QMessageBox::warning(this,"building","DATABASE QUERY NOT OPENED");
           }
           else {

               while (ui->tableWidget->rowCount() > 0)
               {
                  ui->tableWidget->removeRow(0);
               }
               ui->tableWidget->setColumnCount(9);
               QStringList labels;
               labels<<"INVOICE"<<"MONTH"<<"STATUS"<<"TOTAL"<<"MAINTENANCE"<<"OTHER"<<"WATER"<<"GAS"<<"SERVICE";
               ui->tableWidget->setHorizontalHeaderLabels(labels);

               int rowcount=0;

               while(qy1.next())
               {
                   if(qy1.value(7)==val)
                   {
                   ui->tableWidget->insertRow(rowcount);

                    QTableWidgetItem *date= new QTableWidgetItem;
                    QTableWidgetItem *service= new QTableWidgetItem;
                    QTableWidgetItem *gas= new QTableWidgetItem;
                    QTableWidgetItem *water= new QTableWidgetItem;
                    QTableWidgetItem *maintenance= new QTableWidgetItem;
                    QTableWidgetItem *other= new QTableWidgetItem;
                   // QTableWidgetItem *due= new QTableWidgetItem;
                    QTableWidgetItem *flat= new QTableWidgetItem;
                    QTableWidgetItem *month_rent= new QTableWidgetItem;
                    QTableWidgetItem *payment= new QTableWidgetItem;
                    QTableWidgetItem *invoice= new QTableWidgetItem;

                    date->setText(qy1.value(0).toString());
                    service->setText(qy1.value(1).toString());
                    gas->setText(qy1.value(2).toString());
                    water->setText(qy1.value(3).toString());
                    maintenance->setText(qy1.value(4).toString());
                    other->setText(qy1.value(5).toString());
                 //   due->setText(qy1.value(6).toString());
                    flat->setText(qy1.value(7).toString());
                    month_rent->setText(qy1.value(8).toString());
                    payment->setText(qy1.value(9).toString());
                    invoice->setText(qy1.value(10).toString());

                    ui->tableWidget->setItem(rowcount,0,invoice);
                    ui->tableWidget->setItem(rowcount,1,date);
                    ui->tableWidget->setItem(rowcount,2,payment);
                   // ui->tableWidget->setItem(rowcount,2,due);
                    ui->tableWidget->setItem(rowcount,3,month_rent);
                    ui->tableWidget->setItem(rowcount,4,maintenance);
                    ui->tableWidget->setItem(rowcount,5,other);
                    ui->tableWidget->setItem(rowcount,6,water);
                    ui->tableWidget->setItem(rowcount,7,gas);
                    ui->tableWidget->setItem(rowcount,8,service);

                    QFont font("Helvetica", 9, QFont::Bold);
                    invoice->setTextAlignment(Qt::AlignCenter);
                    invoice->setFont(font);

                    rowcount++;
                   }
                   else
                   {
                        rowcount++;
                   }
               }

                }
           if(!qy2.exec())
           {
                QMessageBox::warning(this,"building","DATABASE QUERY NOT OPENED");
           }
           else {
               while (ui->tableWidget_2->rowCount() > 0)
               {
                  ui->tableWidget_2->removeRow(0);
               }
               ui->tableWidget_2->setColumnCount(4);
               QStringList labels;
               labels<<"INVOICE"<<"DATE"<<"TOTAL"<<"STATUS";
               ui->tableWidget_2->setHorizontalHeaderLabels(labels);
               ui->tableWidget_2->setColumnWidth(0,65);
               ui->tableWidget_2->setColumnWidth(1,65);
               ui->tableWidget_2->setColumnWidth(2,65);
               ui->tableWidget_2->setColumnWidth(3,60);

               int rowcount=0;

               while(qy2.next())
               {

                   ui->tableWidget_2->insertRow(rowcount);

                    QTableWidgetItem *date= new QTableWidgetItem;
                    QTableWidgetItem *invoice= new QTableWidgetItem;
                    QTableWidgetItem *payment= new QTableWidgetItem;
                    QTableWidgetItem *status= new QTableWidgetItem;
                    date->setText(qy2.value(1).toString());
                    invoice->setText(qy2.value(4).toString());
                    payment->setText(qy2.value(2).toString());
                    status->setText(qy2.value(3).toString());

                    ui->tableWidget_2->setItem(rowcount,0,invoice);
                    ui->tableWidget_2->setItem(rowcount,1,date);
                    ui->tableWidget_2->setItem(rowcount,2,payment);
                    ui->tableWidget_2->setItem(rowcount,3,status);
                    QFont font("Helvetica", 9, QFont::Bold);
                    invoice->setTextAlignment(Qt::AlignCenter);
                    invoice->setFont(font);
                    rowcount++;

               }

                }

           if(!qy3.exec())
           {
                QMessageBox::warning(this,"building","DATABASE QUERY NOT OPENED");
           }
           else {
               while (ui->tableWidget_3->rowCount() > 0)
               {
                  ui->tableWidget_3->removeRow(0);
               }
               ui->tableWidget_3->setColumnCount(3);
               QStringList labels;
               labels<<"STATUS"<<"DATE"<<"TOTAL BILL";
               ui->tableWidget_3->setHorizontalHeaderLabels(labels);
               ui->tableWidget_3->setColumnWidth(0,80);
               ui->tableWidget_3->setColumnWidth(1,50);
               ui->tableWidget_3->setColumnWidth(2,90);
               int rowcount=0;

               while(qy3.next())
               {

                   ui->tableWidget_3->insertRow(rowcount);

                   QTableWidgetItem *date= new QTableWidgetItem;
                   QTableWidgetItem *add= new QTableWidgetItem;
                   QTableWidgetItem *payment= new QTableWidgetItem;

                   date->setText(qy3.value(1).toString());
                   add->setText(qy3.value(3).toString());
                   payment->setText(qy3.value(2).toString());

                   ui->tableWidget_3->setItem(rowcount,0,add);
                   ui->tableWidget_3->setItem(rowcount,1,date);
                   ui->tableWidget_3->setItem(rowcount,2,payment);
                   rowcount++;


               }

                }

       }
       else
       {
           QMessageBox::warning(this,"building","RENTER NOT FOUND");
       }
}
   else
   {
       QMessageBox::warning(this,"building","RENTER NOT FOUND");
   }
}
