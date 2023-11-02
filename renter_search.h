#ifndef RENTER_SEARCH_H
#define RENTER_SEARCH_H

#include <QDialog>

namespace Ui {
class renter_search;
}

class renter_search : public QDialog
{
    Q_OBJECT

public:
    explicit renter_search(QWidget *parent = nullptr);
    ~renter_search();

private slots:



    void on_pushButton_search_clicked();

    void on_pushButton_BACK_clicked();

private:
    Ui::renter_search *ui;
};

#endif // RENTER_SEARCH_H
