#include "tolet.h"
#include "ui_tolet.h"
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
TOLET::TOLET(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TOLET)
{
    ui->setupUi(this);
    QSqlDatabase db= QSqlDatabase::addDatabase("QSQLITE","myconnect");
db.setDatabaseName("D:/CODEBLOCKS/qt projects/untitled/faisal_sql.sqlite");
   if(db.open())
   {

       QSqlQuery query(db);
       QSqlQuery qy(QSqlDatabase::database("myconnect"));
       //QString str ="select * from renter order by FLAT ASC";
       query.prepare("select FLAT from renter WHERE NAME IS NULL or NAME=:NULL");
       query.bindValue(":NULL","");
       qy.prepare("select * from building");
       if(!query.exec())
       {
            QMessageBox::warning(this,"building","DATABASE QUERY NOT OPENED");
       }
       else {

           qy.exec();
           while(qy.next())
            {
            ui->textEdit->setText(qy.value(2).toString());
            }
           ui->tableWidget->setColumnCount(1);

           QStringList labels;
           labels<<"FLAT";
           ui->tableWidget->setHorizontalHeaderLabels(labels);
           ui->tableWidget->setColumnWidth(0,15);
           int rowcount=0;
            QString val=NULL;
           while(query.next())
           {

               ui->tableWidget->insertRow(rowcount);
                QTableWidgetItem *select= new QTableWidgetItem;
                select->setText(query.value(0).toString());
                ui->tableWidget->setItem(rowcount,0,select);

                rowcount++;
           }
           db.close();
       }
   }
   else
   {
       QMessageBox::warning(this,"building","DATABASE NOT OPENED");
   }
}

TOLET::~TOLET()
{
    delete ui;
}

void TOLET::on_pushButton_BACK_clicked()
{
    hide();
    admin_after_login ad;
    ad.setModal(true);
    ad.exec();
}

