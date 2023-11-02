#ifndef RENTER_DELETE_H
#define RENTER_DELETE_H

#include <QDialog>

namespace Ui {
class renter_delete;
}

class renter_delete : public QDialog
{
    Q_OBJECT

public:
    explicit renter_delete(QWidget *parent = nullptr);
    ~renter_delete();

private slots:
    void on_pushButton_DELETE_clicked();

private:
    Ui::renter_delete *ui;
};

#endif // RENTER_DELETE_H
