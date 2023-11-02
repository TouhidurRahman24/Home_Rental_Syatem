#ifndef RENTER_EDIT_H
#define RENTER_EDIT_H

#include <QDialog>

namespace Ui {
class renter_edit;
}

class renter_edit : public QDialog
{
    Q_OBJECT

public:
    explicit renter_edit(QWidget *parent = nullptr);
    ~renter_edit();

private slots:
    void on_pushButton_edit_clicked();

private:
    Ui::renter_edit *ui;
};

#endif // RENTER_EDIT_H
