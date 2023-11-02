#include "admin_mainmenu.h"
#include "qsqlquery.h"
#include "qsqlquerymodel.h"
#include "ui_admin_mainmenu.h"
#include<signup_form.h>
#include<admin_login.h>
#include<QSql>
#include<QSqlDatabase>
#include<QMessageBox>
admin_mainmenu::admin_mainmenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_mainmenu)
{
    ui->setupUi(this);

}

admin_mainmenu::~admin_mainmenu()
{
    delete ui;
}

void admin_mainmenu::on_pushButton_SIGNUP_clicked()
{
    hide();
    signup_form sign;
    sign.setModal(true);
    sign.exec();
}






void admin_mainmenu::on_pushButton_SIGNIN_clicked()
{
    hide();
    admin_login login;
    login.setModal(true);
    login.exec();

}

