#include "profile.h"
#include "ui_profile.h"
#include<QSqlQuery>
#include<QMessageBox>
#include<admin_after_login.h>
#include<QTimer>
#include<admin_login.h>
#include<QMessageBox>
profile::profile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::profile)
{
    ui->setupUi(this);
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(show()));
    timer->start();

    QSqlQuery qy1(QSqlDatabase::database("myconnect"));
    QSqlQuery query(QSqlDatabase::database("myconnect"));

               query.prepare("select * from(SELECT * FROM(SELECT  distinct * FROM LOGIN_TIME ORDER BY SERIAL DESC) GROUP BY USER) order by SERIAL DESC");
               query.exec();
               ui->tableWidget->setColumnCount(2);
               QStringList labels;
               labels<<"USER"<<"TIME";
               ui->tableWidget->setHorizontalHeaderLabels(labels);
               ui->tableWidget->setColumnWidth(0,60);
               ui->tableWidget->setColumnWidth(1,150);


               int rowcount=0;

               while(query.next())
               {
                    ui->tableWidget->insertRow(rowcount);
                    QTableWidgetItem *user= new QTableWidgetItem;
                    QTableWidgetItem *time= new QTableWidgetItem;

                    user->setText(query.value(0).toString());
                    time->setText(query.value(1).toString()+"  "+query.value(2).toString());

                    ui->tableWidget->setItem(rowcount,0,user);
                    ui->tableWidget->setItem(rowcount,1,time);

                    rowcount++;
               }

           qy1.prepare("SELECT * FROM LOGIN_TIME ORDER BY SERIAL DESC LIMIT 1");
            qy1.exec();
            if(qy1.next())
            {

                ui->lineEdit_username->setText(qy1.value(0).toString());
                username=qy1.value(0).toString();
           }
}
void profile::show()
{
    QString password= ui->lineEdit_password->text();
       int n = password.length();
if(n!=0)
{
       // Checking lower alphabet in string
       bool hasLower = false, hasUpper = false;
       bool hasDigit = false, specialChar = false;


       for (int i = 0; i < n; i++) {
           if ((password[i]).isLower())
               hasLower = true;
           if ((password[i]).isUpper())
               hasUpper = true;
           if ((password[i]).isNumber())
               hasDigit = true;
            if (!(password[i]).isLetter()&& !(password[i]).isNumber() )
                specialChar=true;
    }



       if((hasLower || hasUpper) && hasDigit &&specialChar && (n >= 12))
       {
              ui->label_strength->setText("VERY STRONG");
              QPalette palette = ui->label_strength->palette();
          accept=true;
              palette.setColor(ui->label_strength->foregroundRole(), Qt::darkGreen);
              ui->label_strength->setPalette(palette);

       }
       else if(hasDigit && (hasLower||hasUpper|| specialChar) && (n>=10))
       {
               ui->label_strength->setText("STRONG");
               QPalette palette = ui->label_strength->palette();
               accept=true;
               palette.setColor(ui->label_strength->foregroundRole(), Qt::darkGreen);
               ui->label_strength->setPalette(palette);

       }
        else if(((hasLower || hasUpper)&& hasDigit && (n >= 8))||n>=20)
           {
                    ui->label_strength->setText("MODERATE");
                       accept=true;
                     QPalette palette = ui->label_strength->palette();

                     palette.setColor(ui->label_strength->foregroundRole(), Qt::darkCyan);
                     ui->label_strength->setPalette(palette);

           }

           else
       {

           ui->label_strength->setText("WEAK");
           QPalette palette = ui->label_strength->palette();
           palette.setColor(ui->label_strength->foregroundRole(), Qt::red);
           ui->label_strength->setPalette(palette);

       }
}
else
{
    ui->label_strength->setText("");
}
}
profile::~profile()
{
    delete ui;
}

void profile::on_pushButton_BACK_clicked()
{
    hide();
    admin_after_login ad;
    ad.setModal(true);
    ad.exec();
}


void profile::on_pushButton_EDIT_clicked()
{

     QSqlQuery qy(QSqlDatabase::database("myconnect"));
    QString new_username= ui->lineEdit_username->text();
    QString old_pass= ui->lineEdit_current_pass->text();
    QString new_pass=ui->lineEdit_password->text();

    qy.prepare(QString("select * from login where user= :username and pass =:password "));
    qy.bindValue(":username",username);
    qy.bindValue(":password",old_pass);
    if(new_username=="")
    {
         QMessageBox::warning(this,"database","PLEASE INSERT USERNAME");
    }
    else if(old_pass=="")
    {
        QMessageBox::warning(this,"database","PLEASE INSERT PASSWORD");
        return;
    }
    else if(!qy.exec())
    {
         QMessageBox::warning(this,"Login Form","UNSUCCESSFULL IN QUERY");
    }

    else
    {
       if(qy.next())
        {
          found=true;
        }
       else{
        found=false;
            QMessageBox::warning(this,"Login Form","PASSWORD DOESN'T MATCHED");

       }
    }

if(new_pass=="")
{
    accept=true;
}

if(accept==true&& found==true)
{
    QSqlQuery qy1(QSqlDatabase::database("myconnect"));
     QSqlQuery qy2(QSqlDatabase::database("myconnect"));

if(new_pass!="")
{
        qy1.prepare(QString("UPDATE login set user=:name,pass=:pass where user=:username "));
        qy1.bindValue(":name",new_username);
        qy1.bindValue(":pass",new_pass);
        qy1.bindValue(":username",username);
        qy2.prepare(QString("UPDATE LOGIN_TIME set USER=:name where USER=:username "));
        qy2.bindValue(":name",new_username);
        qy2.bindValue(":username",username);


      if(qy1.exec()&& qy2.exec())
     {

         QMessageBox::information(this,"building","UPDATED");


     }
     else
     {
         QMessageBox::warning(this,"building","DATABASE QUERY  NOT HAPPENED");
     }
}
else if(new_pass=="" && old_pass!="" && new_username !="")
{
    qy1.prepare(QString("UPDATE login set user=:name where user=:username "));
    qy1.bindValue(":name",new_username);
    qy1.bindValue(":username",username);
    qy2.prepare(QString("UPDATE LOGIN_TIME set USER=:name where USER=:username "));
    qy2.bindValue(":name",new_username);
    qy2.bindValue(":username",username);
  if(qy1.exec()&& qy2.exec())
 {

     QMessageBox::information(this,"building","USERNAME UPDATED");


 }
 else
 {
     QMessageBox::warning(this,"building","DATABASE QUERY  NOT HAPPENED");
 }
}
}
else
{
  QMessageBox::warning(this,"database","PLEASE INSERT PASSWORD CORRECTLY");
}



}

void profile::on_pushButton_DELETE_clicked()
{
    QMessageBox::StandardButton reply;
    reply=QMessageBox::question(this,"PROFILE","ARE YOU WANT TO DELETE THIS ACCOUNT?",QMessageBox::Yes | QMessageBox::No );

    if(reply==QMessageBox::Yes)
    {
    QSqlQuery qy(QSqlDatabase::database("myconnect"));
     QSqlQuery qy1(QSqlDatabase::database("myconnect"));

     qy.prepare("DELETE from login where user=:username");
     qy.bindValue(":username",username);

     qy1.prepare("delete from LOGIN_TIME where USER=:username");
     qy1.bindValue(":username",username);

     if(qy.exec()&&qy1.exec())
    {

        QMessageBox::information(this,"PROFILE","ACCOUNT DELETED");
        hide();
        admin_login a;
        a.setModal(true);
        a.exec();

    }
    else
    {
        QMessageBox::warning(this,"PROFILE","DATABASE QUERY  NOT HAPPENED");
    }
    }



}

