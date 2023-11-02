#ifndef RENTER_ADD_H
#define RENTER_ADD_H

#include <QDialog>

namespace Ui {
class renter_add;
}

class renter_add : public QDialog
{
    Q_OBJECT

public:
    explicit renter_add(QWidget *parent = nullptr);
    ~renter_add();

private slots:
    void on_pushButton_ADD_clicked();

    void on_pushButton_back_clicked();

private:
    Ui::renter_add *ui;
};

#endif // RENTER_ADD_H
