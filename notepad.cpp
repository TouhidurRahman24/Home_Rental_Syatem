#include "notepad.h"
#include "ui_notepad.h"
#include<admin_after_login.h>
#include<QSql>
#include<QSqlQuery>
#include<QMessageBox>
#include<QDateTime>
#include "qsqlquery.h"
#include "qsqlquerymodel.h"
#include<QTimer>
notepad::notepad(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::notepad)
{
    ui->setupUi(this);

    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(show()));
    timer->start(400);


   ui->label->setEnabled(false);
}

notepad::~notepad()
{
    delete ui;
}

void notepad::show()
{

    QSqlQuery query(QSqlDatabase::database("myconnect"));

    query.prepare("select * from NOTEPAD order by SERIAL DESC");
   if(!query.exec())
   {
       QMessageBox::warning(this,"NOTEPAD","UNSUCCESSFULL IN QUERY");
       return;
   }
   else
   {
       while (ui->tableWidget_list->rowCount() > 0)
                         {
                            ui->tableWidget_list->removeRow(0);
                         }
   ui->tableWidget_list->setColumnCount(2);
   QStringList labels;
   labels<<"LIST"<<"TIME";
   ui->tableWidget_list->setHorizontalHeaderLabels(labels);
   ui->tableWidget_list->setColumnWidth(0,560);
   ui->tableWidget_list->setRowHeight(0,50);
   ui->tableWidget_list->setColumnWidth(1,130);


   int rowcount=0;

   while(query.next())
   {

        ui->tableWidget_list->insertRow(rowcount);
        QTableWidgetItem *text= new QTableWidgetItem;
        QTableWidgetItem *time= new QTableWidgetItem;


        text->setText(query.value(0).toString());
        time->setText(query.value(1).toString());


        ui->tableWidget_list->setItem(rowcount,0,text);
        ui->tableWidget_list->setItem(rowcount,1,time);


        rowcount++;
   }
   }



}



void notepad::on_pushButton_BACK_clicked()
{
    hide();
    admin_after_login a;
    a.setModal(true);
    a.exec();
}





void notepad::on_pushButton_ADD_clicked()
{

    QDateTime dateTime = dateTime.currentDateTime();
    QString time =dateTime.toString();
    QString text=ui->textEdit->toPlainText();
    if(text=="")
    {
        QMessageBox::warning(this,"NOTEPAD","PLEASE ENTER TEXT");
    }
    else
    {
     QSqlQuery qy(QSqlDatabase::database("myconnect"));
     qy.prepare("insert into NOTEPAD(TEXT,TIME)""values(:text,:time)");
     qy.bindValue(":text",text);
     qy.bindValue(":time",time);
     qy.exec();

    }
}


void notepad::on_tableWidget_list_activated(const QModelIndex &index)
{

    QString val = ui->tableWidget_list->model()->data(index).toString();

      QSqlQuery qy(QSqlDatabase::database("myconnect"));
     qy.prepare("select * from NOTEPAD where TEXT='"+val+"'or TIME='"+val+"'");

    if(qy.exec())
    {
        while(qy.next())
         {
              ui->textEdit->setText(qy.value(0).toString());
              ui->label_TIME->setText(qy.value(1).toString());
               ui->label->setEnabled(true);
         }
    }
    else
    {
        QMessageBox::warning(this,"Login Form","UNSUCCESSFULL IN QUERY");
    }
}


void notepad::on_pushButton_UPDATE_clicked()
{
    QDateTime dateTime = dateTime.currentDateTime();
    QString time =dateTime.toString();
    QString text=ui->textEdit->toPlainText();
    if(text=="")
    {
        QMessageBox::warning(this,"NOTEPAD","PLEASE ENTER TEXT");
    }
    else if(ui->label_TIME->text()=="")
    {
        QMessageBox::warning(this,"NOTEPAD","PLEASE SELECT ITEM FROM TABLE");
    }
    else
    {
    QString timeprogram= ui->label_TIME->text();
     QSqlQuery qy(QSqlDatabase::database("myconnect"));
    qy.prepare(QString("UPDATE NOTEPAD set TEXT=:text, TIME=:time where TIME= :timeprogram "));
    qy.bindValue(":text",text);
    qy.bindValue(":time",time);
    qy.bindValue(":timeprogram",timeprogram);
    qy.exec();

    }
}


void notepad::on_pushButton_DELETE_clicked()
{

    QString text=ui->textEdit->toPlainText();
    if(text=="")
    {
        QMessageBox::warning(this,"NOTEPAD","PLEASE ENTER TEXT");
    }
    else if(ui->label_TIME->text()=="")
    {
        QMessageBox::warning(this,"NOTEPAD","PLEASE SELECT ITEM FROM TABLE");
    }
    else
    {
    QString timeprogram= ui->label_TIME->text();
     QSqlQuery qy(QSqlDatabase::database("myconnect"));
    qy.prepare(QString("DELETE FROM NOTEPAD where TIME= :timeprogram "));
    qy.bindValue(":timeprogram",timeprogram);
    qy.exec();

    }
}


void notepad::on_pushButton_CLEAR_clicked()
{
    ui->textEdit->setText("");
    ui->label_TIME->setText("");
    ui->label->setEnabled(false);
}


void notepad::on_pushButtonDELETE_ALL_clicked()
{

     QSqlQuery qy(QSqlDatabase::database("myconnect"));
    qy.prepare(QString("DELETE FROM NOTEPAD"));
    qy.exec();


}

