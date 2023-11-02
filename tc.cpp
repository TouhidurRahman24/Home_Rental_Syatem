#include "tc.h"
#include "ui_tc.h"
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
tc::tc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tc)
{
    ui->setupUi(this);



}

tc::~tc()
{
    delete ui;
}

void tc::on_pushButton_back_clicked()
{
    hide();
    admin_after_login ad;
    ad.setModal(true);
    ad.exec();

}


void tc::on_pushButton_PRINT_clicked()
{
    QMessageBox::StandardButton reply;
    reply=QMessageBox::question(this,"T&C","DO YOU WANT TERMS AND CONDITIONS TO PRINT",QMessageBox::Yes | QMessageBox::No );

   if(reply==QMessageBox::Yes)
   {

    QString html =
            "<!DOCTYPE html>"
            "<html>"
            "<head>"
            "</head>"
            "<body>"
            "<h1>                      [TERMS AND CONDTIONS]</h1>"
            "<pre>"
            "<form>"
            "<h3>"
            "<div>"
            "<h2>   "+ui->textEdit->toHtml()+"</h2>"
            "</h3>"
            "</pre>"
            "</form>"
            "</form>"
            "</form>"
            "</body>"
            "</html>";

    QTextDocument document;
    document.setHtml(html);
      QString s= "TERMS_AND_CONDTIONS";
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("D:/"+s+".pdf");
    printer.setPageMargins(QMarginsF(6, 6, 5, 5));
    document.print(&printer);
     QMessageBox::information(this,"T&C","TERMS AND CONDITIONS ISSUED");
   }

}

