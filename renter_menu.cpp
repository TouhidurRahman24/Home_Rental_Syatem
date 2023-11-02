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
#include<QMessageBox>
#include<QDateTime>
#include<QTimer>
renter_menu::renter_menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::renter_menu)
{
    hide();
    ui->setupUi(this);
    ui->groupBox_2->setEnabled(false);
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(show()));
    timer->start();
     QSqlDatabase db= QSqlDatabase::addDatabase("QSQLITE","myconnect");
db.setDatabaseName("D:/CODEBLOCKS/qt projects/untitled/faisal_sql.sqlite");
    if(db.open())
    {

        QSqlQuery query(db);
        QString str ="select * from renter ";
        if(!query.exec(str))
        {
             QMessageBox::warning(this,"RENTER","DATABASE QUERY NOT OPENED");
        }
        else {
            ui->tableWidget->setColumnCount(9);
            QStringList labels;
            labels<<"FLAT"<<"NAME"<<"MOBILE"<<"NID"<<"PERMANENT ADDRESS"<<"RENT"<<"DUE"<<"ADVANCE"<<"JOINING";
            ui->tableWidget->setHorizontalHeaderLabels(labels);
            ui->tableWidget->setColumnWidth(0,30);
            ui->tableWidget->setColumnWidth(1,100);
            ui->tableWidget->setColumnWidth(2,90);
            ui->tableWidget->setColumnWidth(3,100);
            ui->tableWidget->setColumnWidth(4,150);
            ui->tableWidget->setColumnWidth(5,90);
            ui->tableWidget->setColumnWidth(6,90);
            ui->tableWidget->setColumnWidth(7,90);
            ui->tableWidget->setColumnWidth(8,90);


            int rowcount=0;

            while(query.next())
            {

                 ui->tableWidget->insertRow(rowcount);
                 QTableWidgetItem *select= new QTableWidgetItem;
                 QTableWidgetItem *NAME= new QTableWidgetItem;
                 QTableWidgetItem *MOBILE= new QTableWidgetItem;
                 QTableWidgetItem *NID= new QTableWidgetItem;
                 QTableWidgetItem *H_ADDRESS= new QTableWidgetItem;
                 QTableWidgetItem *FLAT= new QTableWidgetItem;
                 QTableWidgetItem *RENT= new QTableWidgetItem;
                 QTableWidgetItem *DUE= new QTableWidgetItem;
                 QTableWidgetItem *ADVANCE= new QTableWidgetItem;
                 QTableWidgetItem *JOIN= new QTableWidgetItem;

                 select->setText(query.value(0).toString());
                 FLAT->setText(query.value(1).toString());
                 NAME->setText(query.value(2).toString());
                 MOBILE->setText(query.value(3).toString());
                 NID->setText(query.value(4).toString());
                 H_ADDRESS->setText(query.value(5).toString());
                 RENT->setText(query.value(6).toString());
                 DUE->setText(query.value(7).toString());
                 ADVANCE->setText(query.value(8).toString());
                 JOIN->setText(query.value(9).toString());

                 ui->tableWidget->setItem(rowcount,0,select);
                 ui->tableWidget->setItem(rowcount,1,FLAT);
                 ui->tableWidget->setItem(rowcount,2,NAME);
                 ui->tableWidget->setItem(rowcount,3,MOBILE);
                 ui->tableWidget->setItem(rowcount,4,NID);
                 ui->tableWidget->setItem(rowcount,5,H_ADDRESS);
                 ui->tableWidget->setItem(rowcount,6,RENT);
                 ui->tableWidget->setItem(rowcount,7,DUE);
                 ui->tableWidget->setItem(rowcount,8,ADVANCE);
                 ui->tableWidget->setItem(rowcount,9,JOIN);

                 rowcount++;
            }
            db.close();
        }
    }
    else
    {
        QMessageBox::warning(this,"RENTER","DATABASE NOT OPENED");
    }
    QDateTime dateTime = dateTime.currentDateTime();
     ui->dateEdit->setDateTime(dateTime);
    ui->dateEdit_2->setDateTime(dateTime);


}

renter_menu::~renter_menu()
{
    delete ui;
}


void renter_menu::show()
{
    qint64 service=ui->lineEdit_SERVICE->text().toInt();
    qint64 gas=ui->lineEdit_GAS->text().toInt();
    qint64 water=ui->lineEdit_WATER->text().toInt();
    qint64 maintenance=ui->lineEdit_MAINTENANCE->text().toInt();
    qint64 other=ui->lineEdit_OTHER->text().toInt();
    qint64 total=service+gas+water+maintenance+other;
    QString tot=QString::number(total);
    ui->lineEdit_TOTAL->setText(tot);

    if(ui->radioButton_ONE->isChecked())
    {
        ui->groupBox_2->setEnabled(true);
        ui->label_RENTFLAT->setEnabled(true);
        ui->lineEdit_RENTFLAT->setEnabled(true);

    }
    else if(ui->radioButton_ALL->isChecked())
    {
        ui->groupBox_2->setEnabled(true);
        ui->label_RENTFLAT->setEnabled(false);
        ui->lineEdit_RENTFLAT->setEnabled(false);
    }



}


void renter_menu::on_pushButton_3_clicked()
{

    QSqlDatabase db= QSqlDatabase::addDatabase("QSQLITE");
db.setDatabaseName("D:/CODEBLOCKS/qt projects/untitled/faisal_sql.sqlite");


     if(db.open())
     {

         QString flat=ui->lineEdit_flat->text().toUpper();
         QString H_ADDRESS= ui->lineEdit_H_ADDRESS->text();
         QString MOBILE= ui->lineEdit_MOBILE->text();
         QString nid=ui->lineEdit_nid->text();
         QString name=ui->lineEdit_name->text();
         QString rent=ui->lineEdit_RENT_AMOUNT->text();
         QString advance=ui->lineEdit_ADVANCE->text();
         //QString join=ui->lineEdit_JOIN->text();
         QString join=ui->dateEdit->text();
         QSqlQuery qy;
       qy.prepare("insert into renter(FLAT,H_ADDRESS,MOBILE,NID,NAME,MONEY,ADVANCE,JOINING)""values(:flat,:H_ADDRESS,:MOBILE,:nid,:name,:rent,:advance,:join)");
       qy.bindValue(":flat",flat);
       qy.bindValue(":H_ADDRESS",H_ADDRESS);
       qy.bindValue(":MOBILE",MOBILE);
       qy.bindValue(":nid",nid);
       qy.bindValue(":name",name);
       qy.bindValue(":rent",rent);
       qy.bindValue(":advance",advance);
       qy.bindValue(":join",join);
       if(flat==""||H_ADDRESS==""||MOBILE==""||nid==""||name==""||rent==""||advance==""||join=="")
       {
            QMessageBox::warning(this,"RENTER","PLEASE INSERT DATA");
       }

       else if(qy.exec())
       {

           QMessageBox::information(this,"RENTER","INSERTED INTO DATABASE");
            hide();
           renter_menu r;
           r.setModal(true);
           r.exec();
       }
       else
       {
           QMessageBox::warning(this,"RENTER","NOT INSERTED INTO DATABASE");
       }
     }
     else
     {
          QMessageBox::warning(this,"RENTER","DATABASE NOT OPENED");
     }
}


void renter_menu::on_pushButton_back_clicked()
{
    hide();
    admin_after_login ad;
    ad.setModal(true);
    ad.exec();
}


void renter_menu::on_pushButton_clicked()
{
    QSqlQuery qy(QSqlDatabase::database("myconnect"));

   // QSqlDatabase db= QSqlDatabase::addDatabase("QSQLITE");
    //   db.setDatabaseName("D:/QT/SQLiteStudio/faisal_sql.sqlite");
      // if(db.open())
      // {
       QString flat=ui->lineEdit_flat->text();
       QString H_ADDRESS= ui->lineEdit_H_ADDRESS->text();
       QString MOBILE= ui->lineEdit_MOBILE->text();
       QString nid=ui->lineEdit_nid->text();
       QString name=ui->lineEdit_name->text();
        QString rent=ui->lineEdit_RENT_AMOUNT->text();
        QString advance=ui->lineEdit_ADVANCE->text();
         QString join=ui->dateEdit->text();
       //QSqlQuery qy;
        qy.prepare(QString("UPDATE renter set NAME=:name, H_ADDRESS=:H_ADDRESS,MOBILE=:MOBILE,NID=:nid,MONEY=:rent,ADVANCE=:advance,JOINING=:join where FLAT= :flat "));
     //qy.prepare("update renter set H_ADDRESS='"+H_ADDRESS+"',MOBILE='"+MOBILE+"',NAME='"+name+"',NID='"+nid+"' where FLAT='"+flat+"'");
    // qy.prepare("UPDATE renter SET(FLAT,H_ADDRESS,MOBILE,NID,NAME) where FLAT="+flat+"values(:flat,:H_ADDRESS,:MOBILE,:nid,:name)");
       //qy.prepare("update renter set NAME=':name',H_ADDRESS=':H_ADDRESS',MOBILE=':MOBILE',NID=':nid' where FLAT=':flat'");
       qy.bindValue(":flat",flat);
       qy.bindValue(":H_ADDRESS",H_ADDRESS);
       qy.bindValue(":MOBILE",MOBILE);
       qy.bindValue(":nid",nid);
       qy.bindValue(":name",name);
       qy.bindValue(":rent",rent);
       qy.bindValue(":advance",advance);
       qy.bindValue(":join",join);
       if(flat==""||H_ADDRESS==""||MOBILE==""||nid==""||name==""||rent==""||advance==""||join=="")
       {
            QMessageBox::warning(this,"database","PLEASE INSERT DATA");
       }
       else if(qy.exec())
     {
         QMessageBox::information(this,"building","UPDATED");
         hide();
         renter_menu r;
         r.setModal(true);
         r.exec();
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


void renter_menu::on_pushButton_2_clicked()
{
       QSqlQuery qy(QSqlDatabase::database("myconnect"));
       QSqlQuery qy1(QSqlDatabase::database("myconnect"));
       QSqlQuery qy2(QSqlDatabase::database("myconnect"));
       QSqlQuery qy3(QSqlDatabase::database("myconnect"));
       QString flat=ui->lineEdit_flat->text();
       QString H_ADDRESS= ui->lineEdit_H_ADDRESS->text();
       QString MOBILE= ui->lineEdit_MOBILE->text();
       QString nid=ui->lineEdit_nid->text();
       QString name=ui->lineEdit_name->text();
       QString rent=ui->lineEdit_RENT_AMOUNT->text();
       QString advance=ui->lineEdit_ADVANCE->text();
       QString join=ui->dateEdit->text();
       QString due=ui->lineEdit_TOTAL->text();


       QMessageBox::StandardButton reply;
       reply=QMessageBox::question(this,"","DO YOU WANT SAVE THIS DATA",QMessageBox::Yes | QMessageBox::No |QMessageBox::Cancel);

       if(reply==QMessageBox::Yes)
       {

     qy.prepare("insert into OLD_RENTER(FLAT,H_ADDRESS,MOBILE,NID,NAME,MONEY,DUE,ADVANCE,JOINING)""values(:flat,:H_ADDRESS,:MOBILE,:nid,:name,:rent,:due,:advance,:join)");
     qy.bindValue(":flat",flat);
     qy.bindValue(":H_ADDRESS",H_ADDRESS);
     qy.bindValue(":MOBILE",MOBILE);
     qy.bindValue(":nid",nid);
     qy.bindValue(":name",name);
     qy.bindValue(":rent",rent);
     qy.bindValue(":advance",advance);
     qy.bindValue(":join",join);
     qy.bindValue(":due",due);

     if(flat==""||H_ADDRESS==""||MOBILE==""||nid==""||name==""||rent==""||advance==""||join=="")
     {
          QMessageBox::warning(this,"database","PLEASE INSERT DATA");
     }

     else if(qy.exec())
     {
         qy2.prepare("select * from trans");
         qy2.exec();
         while(qy2.next())
         {
         qy1.prepare(QString("DELETE FROM trans where FLAT=:flat"));
          qy1.bindValue(":flat",flat);
          qy1.exec();
         }
         qy3.prepare(QString("UPDATE  renter SET NAME=:NULL,MOBILE=:NULL,NID=:NULL, H_ADDRESS=:NULL,MONEY=:NULL, DUE=:ZERO, ADVANCE=:NULL,JOINING=:NULL where FLAT=:flat"));
         qy3.bindValue(":NULL","");
         qy3.bindValue(":ZERO",0);
         qy3.bindValue(":flat",flat);
         qy3.exec();
         QMessageBox::information(this,"database","DELETED");
          hide();
         renter_menu r;
         r.setModal(true);
         r.exec();
     }
     else
     {
         QMessageBox::warning(this,"database","NOT INSERTED INTO DATABASE");
     }
    }

       else if(reply==QMessageBox::No)
       {
           qy.prepare(QString("UPDATE  renter SET NAME=:NULL,MOBILE=:NULL,NID=:NULL, H_ADDRESS=:NULL,MONEY=:NULL, DUE=:ZERO, ADVANCE=:NULL,JOINING=:NULL where FLAT=:flat"));
           qy.bindValue(":NULL","");
           qy.bindValue(":ZERO",0);
           qy.bindValue(":flat",flat);
            if(qy.exec())
            {
                qy2.prepare("select * from trans");
                qy2.exec();
                while(qy2.next())
                {
                qy1.prepare(QString("DELETE FROM trans where FLAT=:flat"));
                qy1.bindValue(":flat",flat);
                qy1.exec();
                }

                QMessageBox::information(this,"database","PERMANENT DELETE");
                hide();
               renter_menu r;
               r.setModal(true);
               r.exec();
            }
            else
            {
                 QMessageBox::warning(this,"database","QUERY UNSUCCESSFULL");
            }

       }





}


void renter_menu::on_tableWidget_activated(const QModelIndex &index)
{
    //QString val = index.sibling(index.row(),index.column()).data().toString();
    QString val = ui->tableWidget->model()->data(index).toString();
    QSqlQuery qy(QSqlDatabase::database("myconnect"));
  //qy.prepare("select * from renter(FLAT,H_ADDRESS,MOBILE,NID,NAME)""values(:flat,:H_ADDRESS,:MOBILE,:nid,:name)");
   qy.prepare("select * from renter where H_ADDRESS='"+val+"'or MOBILE='"+val+"'or NAME='"+val+"'or FLAT='"+val+"'or NID='"+val+"'or MONEY='"+val+"'or ADVANCE='"+val+"'or JOINING='"+val+"'");

  if(qy.exec())
  {
      while(qy.next())
       {
          ui->lineEdit_flat->setText(qy.value(0).toString());
         ui->lineEdit_H_ADDRESS->setText(qy.value(4).toString());
         ui->lineEdit_MOBILE->setText(qy.value(2).toString());
         ui->lineEdit_nid->setText(qy.value(3).toString());
         ui->lineEdit_name->setText(qy.value(1).toString());
          ui->lineEdit_RENT_AMOUNT->setText(qy.value(5).toString());
          ui->lineEdit_ADVANCE->setText(qy.value(7).toString());

          QString format("yyyy/M/dd");
          QDateTime now = QDateTime::fromString(qy.value(8).toString(), format);
          ui->dateEdit->setDateTime(now);
       }
  }
  else
  {
      QMessageBox::warning(this,"Login Form","UNSUCCESSFULL IN QUERY");
  }
}


void renter_menu::on_pushButton_CLEAR_clicked()
{
    QDateTime dateTime = dateTime.currentDateTime();
    ui->lineEdit_flat->setText("");
   ui->lineEdit_H_ADDRESS->setText("");
   ui->lineEdit_MOBILE->setText("");
   ui->lineEdit_nid->setText("");
   ui->lineEdit_name->setText("");
    ui->lineEdit_RENT_AMOUNT->setText("");
    ui->lineEdit_ADVANCE->setText("");
    ui->dateEdit->setDateTime(dateTime);
}





void renter_menu::on_pushButton_clear_2_clicked()
{
    QDateTime dateTime = dateTime.currentDateTime();
    ui->dateEdit_2->setDateTime(dateTime);
    ui->lineEdit_SERVICE->setText("");
    ui->lineEdit_GAS->setText("");
    ui->lineEdit_WATER->setText("");
    ui->lineEdit_MAINTENANCE->setText("");
    ui->lineEdit_TOTAL->setText("");
    ui->lineEdit_OTHER->setText("");
    ui->lineEdit_RENTFLAT->setText("");
}


void renter_menu::on_pushButton_ADMIT_clicked()
{

    QMessageBox::StandardButton reply;
    reply=QMessageBox::question(this,"RENTER MENU","ARE YOU SURE WANT TO ADD BILLS?",QMessageBox::Yes| QMessageBox::No|QMessageBox::Cancel);

    if(reply==QMessageBox::Yes){
if(ui->radioButton_ALL->isChecked())
{
        QString service=ui->lineEdit_SERVICE->text();
        QString gas=ui->lineEdit_GAS->text();
        QString water=ui->lineEdit_WATER->text();
        QString maintenance=ui->lineEdit_MAINTENANCE->text();
        QString total=ui->lineEdit_TOTAL->text();
        QString other=ui->lineEdit_OTHER->text();
        QString date= ui->dateEdit_2->text();
        QSqlQuery qy(QSqlDatabase::database("myconnect"));

        QSqlQuery qy2(QSqlDatabase::database("myconnect"));
        QSqlQuery qy3(QSqlDatabase::database("myconnect"));
        QSqlQuery qy4(QSqlDatabase::database("myconnect"));
        qy2.prepare("select * from renter where NAME IS NOT NULL AND MONEY IS NOT NULL");

        qy2.exec();

        while(qy2.next())
        {
            int advance=0,advance_now;
            qint64 previous=qy2.value(6).toInt();
            qint64 rent=qy2.value(5).toInt();
            qint64 totalint =ui->lineEdit_TOTAL->text().toInt();
            QString month_rent=QString::number(rent+totalint);
            qint64 DUE=previous;
            qint64 rent_now=totalint+rent;
            QString flat=qy2.value(0).toString();
            QSqlQuery qy4(QSqlDatabase::database("myconnect"));
            QSqlQuery qy5(QSqlDatabase::database("myconnect"));
            QSqlQuery qy6(QSqlDatabase::database("myconnect"));
            qy4.prepare("select * from ADVANCE where FLAT=:flat AND STATUS=:add");
            qy4.bindValue(":add","NOT ADDED");
            qy4.bindValue(":flat",flat);
            qy4.exec();
            while(qy4.next())
            {
                   advance=advance+qy4.value(2).toInt();
            }
            advance_now=rent_now-advance;
            rent_now=rent_now-advance;

            if(advance_now<0)
            {
                advance_now=0;
            }
            qy5.prepare(QString("UPDATE ADVANCE set STATUS=:add,AMOUNT=:amount where FLAT=:flat"));
            qy5.bindValue(":flat",flat);
            qy5.bindValue(":amount",month_rent);
            qy5.bindValue(":add","ADDED");
            qy5.exec();
            if(rent_now<0)
            {
            qint64 AD_DUE=abs(rent_now);
            QString add_due=QString::number(AD_DUE);
            qy6.prepare("insert into ADVANCE(FLAT,DATE,AMOUNT,STATUS)""values(:flat,:date,:amount,:add)");
            qy6.bindValue(":flat",flat);
            qy6.bindValue(":add","NOT ADDED");
            qy6.bindValue(":amount",add_due);
            qy6.exec();
            rent_now=0;
            }
            QString payment;
            DUE=DUE+rent_now;
             month_rent=QString::number(rent_now);
            total=QString::number(DUE);
            if(rent_now>0)
            {
           payment="NOT PAID";
            }
            else if(rent_now<=0)
            {
                 payment="PAID";
                 month_rent=0;
            }

            if(rent!=0)
            {
            qy.prepare("insert into RENT_DATA(DATE,SERVICE,GAS,WATER,MAINTENANCE,OTHER,TOTAL,FLAT,RENT_TOTAL,PAYMENT)""values(:date,:service,:gas,:water,:maintenance,:other,:total,:flat,:month_rent,:payment)");
            qy.bindValue(":date",date);
            qy.bindValue(":service",service);
            qy.bindValue(":gas",gas);
            qy.bindValue(":water",water);
            qy.bindValue(":maintenance",maintenance);
            qy.bindValue(":other",other);
            qy.bindValue(":total",total);
            qy.bindValue(":flat",flat);
            qy.bindValue(":month_rent",month_rent);
            qy.bindValue(":payment",payment);
            if(qy.exec())
            {
            qy3.prepare(QString("UPDATE renter set DUE=:total where FLAT=:flat and NAME IS NOT NULL"));
            qy3.bindValue(":total",total);
            qy3.bindValue(":flat",flat);
            qy3.exec();
            }
            else
            {
                continue;
            }
            }

        }

        hide();
        renter_menu r;
        r.setModal(true);
        r.exec();
        }
else if(ui->radioButton_ONE->isChecked())
{
    QString service=ui->lineEdit_SERVICE->text();
    QString gas=ui->lineEdit_GAS->text();
    QString water=ui->lineEdit_WATER->text();
    QString maintenance=ui->lineEdit_MAINTENANCE->text();
    QString total=ui->lineEdit_TOTAL->text();
    QString other=ui->lineEdit_OTHER->text();

    QString date= ui->dateEdit_2->text();
    QString rentflat=ui->lineEdit_RENTFLAT->text().toUpper();
    QSqlQuery qy(QSqlDatabase::database("myconnect"));
    if(rentflat=="")
    {
        QMessageBox::warning(this,"RENT MENU","PLEASE INSERT FLAT");
        return;
    }
    QSqlQuery qy2(QSqlDatabase::database("myconnect"));
    QSqlQuery qy3(QSqlDatabase::database("myconnect"));
    QSqlQuery qy4(QSqlDatabase::database("myconnect"));

    qy2.prepare("select * from renter where FLAT=:rentflat");
    qy2.bindValue(":rentflat",rentflat);
    if(qy2.exec())
    {

    while(qy2.next())
    {
        int advance=0,advance_now;
        qint64 previous=qy2.value(6).toInt();
        qint64 rent=qy2.value(5).toInt();
        qint64 totalint =ui->lineEdit_TOTAL->text().toInt();
        QString month_rent=QString::number(rent+totalint);
        qint64 DUE=previous;
        qint64 rent_now=totalint+rent;
        QString flat=qy2.value(0).toString();
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
        advance_now=rent_now-advance;
        rent_now=rent_now-advance;

        if(advance_now<0)
        {
            advance_now=0;
        }
        qy5.prepare(QString("UPDATE ADVANCE set STATUS=:add,AMOUNT=:amount where FLAT=:flat"));
        qy5.bindValue(":flat",flat);
        qy5.bindValue(":amount",month_rent);
        qy5.bindValue(":add","ADDED");
        qy5.exec();
        if(rent_now<0)
        {
        qint64 AD_DUE=abs(rent_now);
        QString add_due=QString::number(AD_DUE);
        qy6.prepare("insert into ADVANCE(FLAT,DATE,AMOUNT,STATUS)""values(:flat,:date,:amount,:add)");
        qy6.bindValue(":flat",flat);
        qy6.bindValue(":add","NOT ADDED");
        qy6.bindValue(":amount",add_due);
        qy6.exec();
        rent_now=0;
        }
        QString payment;
        DUE=DUE+rent_now;
         month_rent=QString::number(rent_now);
        total=QString::number(DUE);
        if(rent_now>0)
        {
       payment="NOT PAID";
        }
        else if(rent_now<=0)
        {
             payment="PAID";
             month_rent=0;
        }
        if(rent!=0)
        {
        total=QString::number(DUE);

        qy.prepare("insert into RENT_DATA(DATE,SERVICE,GAS,WATER,MAINTENANCE,OTHER,TOTAL,FLAT,RENT_TOTAL,PAYMENT)""values(:date,:service,:gas,:water,:maintenance,:other,:total,:flat,:month_rent,:payment)");
        qy.bindValue(":date",date);
        qy.bindValue(":service",service);
        qy.bindValue(":gas",gas);
        qy.bindValue(":water",water);
        qy.bindValue(":maintenance",maintenance);
        qy.bindValue(":other",other);
        qy.bindValue(":total",total);
        qy.bindValue(":flat",flat);
        qy.bindValue(":month_rent",month_rent);
        qy.bindValue(":payment",payment);

        if(qy.exec())
        {
        qy3.prepare(QString("UPDATE renter set DUE=:total where FLAT=:flat and NAME IS NOT NULL"));
        qy3.bindValue(":total",total);
        qy3.bindValue(":flat",flat);
        qy3.exec();
        }
        else
        {
            QMessageBox::warning(this,"RENT MENU","PLEASE CHECK MONTH");
        }
        }
     else
     {
        QMessageBox::warning(this,"RENT MENU","PLEASE INSERT RENT AMOUNT");
     }
    }
    }

    hide();
    renter_menu r;
    r.setModal(true);
    r.exec();


}

    }

}

