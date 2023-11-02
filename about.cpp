#include "about.h"
#include "ui_about.h"
#include<admin_after_login.h>
ABOUT::ABOUT(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ABOUT)
{
    ui->setupUi(this);
}

ABOUT::~ABOUT()
{
    delete ui;
}

void ABOUT::on_pushButton_BACK_clicked()
{
    hide();
    admin_after_login a;
    a.setModal(true);
    a.exec();
}

