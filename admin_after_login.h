#ifndef ADMIN_AFTER_LOGIN_H
#define ADMIN_AFTER_LOGIN_H

#include <QDialog>

namespace Ui {
class admin_after_login;
}

class admin_after_login : public QDialog
{
    Q_OBJECT

public:
    explicit admin_after_login(QWidget *parent = nullptr);
    ~admin_after_login();

private slots:

    void on_pushButton_buildin_clicked();

    void on_pushButton_CUSTOMIZE_clicked();

    void on_pushButton_RENTE_SEARCH_clicked();

    void on_pushButton_trans_clicked();

    void on_pushButton_TC_clicked();

    void on_pushButton_TO_LET_clicked();

    void on_pushButton_MAINTENANCE_clicked();

    void on_pushButton_back_clicked();



    void on_pushButton_profile_clicked();

    void on_pushButton_profile_info_clicked();



    void on_pushButton_ABOUT_clicked();

    void on_pushButton_NOTEPAD_clicked();

    void on_pushButton_notepad_pic_clicked();

private:
    Ui::admin_after_login *ui;
};

#endif // ADMIN_AFTER_LOGIN_H
