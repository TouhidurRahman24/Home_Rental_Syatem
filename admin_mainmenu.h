#ifndef ADMIN_MAINMENU_H
#define ADMIN_MAINMENU_H

#include <QDialog>

namespace Ui {
class admin_mainmenu;
}

class admin_mainmenu : public QDialog
{
    Q_OBJECT

public:
    explicit admin_mainmenu(QWidget *parent = nullptr);
    ~admin_mainmenu();

private slots:
    void on_pushButton_SIGNUP_clicked();

    void on_pushButton_SIGNIN_clicked();

     void on_pushButton_SELLALL_clicked();

private:
    Ui::admin_mainmenu *ui;
};

#endif // ADMIN_MAINMENU_H
