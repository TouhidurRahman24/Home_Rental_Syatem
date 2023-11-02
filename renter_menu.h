#ifndef RENTER_MENU_H
#define RENTER_MENU_H

#include <QDialog>

namespace Ui {
class renter_menu;
}

class renter_menu : public QDialog
{
    Q_OBJECT

public:
    explicit renter_menu(QWidget *parent = nullptr);
    ~renter_menu();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_back_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableWidget_activated(const QModelIndex &index);

    void on_pushButton_CLEAR_clicked();

    void on_pushButton_clear_2_clicked();

    void on_pushButton_ADMIT_clicked();


    void show();

private:
    Ui::renter_menu *ui;
};

#endif // RENTER_MENU_H
