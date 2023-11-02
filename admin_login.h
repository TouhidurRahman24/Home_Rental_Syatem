#ifndef ADMIN_LOGIN_H
#define ADMIN_LOGIN_H
#include<admin_login.h>
#include <QDialog>

namespace Ui {
class admin_login;
}

class admin_login : public QDialog
{
    Q_OBJECT

public:
    explicit admin_login(QWidget *parent = nullptr);
    ~admin_login();

private slots:

    void on_pushButton_LOGIN_clicked();

    void on_pushButton_SIGNUP_clicked();

    void on_pushButton_eye_pressed();

    void on_pushButton_eye_released();

private:
    Ui::admin_login *ui;
};

#endif // ADMIN_LOGIN_H
