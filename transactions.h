#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <QDialog>

namespace Ui {
class TRANSACTIONS;
}

class TRANSACTIONS : public QDialog
{
    Q_OBJECT
public:
    QString rec_name,rec_address,rec_phone,rec_month,rec_amount,rec_paidby,rec_apart_name;


public:
    explicit TRANSACTIONS(QWidget *parent = nullptr);
    ~TRANSACTIONS();

private slots:

    void on_pushButton_BACK_clicked();

    void on_pushButton_PAYMENT_clicked();

    void on_pushButton_SEARCH_clicked();

    void show();

private:
    Ui::TRANSACTIONS *ui;
};

#endif // TRANSACTIONS_H
