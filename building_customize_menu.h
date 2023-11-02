#ifndef BUILDING_CUSTOMIZE_MENU_H
#define BUILDING_CUSTOMIZE_MENU_H

#include <QDialog>

namespace Ui {
class building_customize_menu;
}

class building_customize_menu : public QDialog
{
    Q_OBJECT

public:
    explicit building_customize_menu(QWidget *parent = nullptr);
    ~building_customize_menu();

private slots:


    void on_pushButton_ADMIT_clicked();

    void on_pushButton_back_clicked();

    void on_pushButton_EDIT_clicked();

    void on_pushButton_info_clicked();

private:
    Ui::building_customize_menu *ui;
};

#endif // BUILDING_CUSTOMIZE_MENU_H
