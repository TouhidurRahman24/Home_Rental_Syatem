#include "renter_delete.h"
#include "qsqlquery.h"
#include "ui_renter_delete.h"
#include<QSql>
#include<QSqlDatabase>
#include<QMessageBox>
renter_delete::renter_delete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::renter_delete)
{
    ui->setupUi(this);
}

renter_delete::~renter_delete()
{
    delete ui;
}

void renter_delete::on_pushButton_DELETE_clicked()
{
    QSqlQuery qy(QSqlDatabase::database("myconnect"));

    QString del= ui->lineEdit->text();

   qy.prepare(QString("DELETE FROM renter where FLAT=:del"));
  qy.bindValue(":del",del);
  if(qy.exec())
  {
      QMessageBox::information(this,"building","DELETED");
  }
  else
  {
      QMessageBox::warning(this,"building","DATABASE QUERY  NOT HAPPENED");
  }

}

