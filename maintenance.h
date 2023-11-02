#ifndef MAINTENANCE_H
#define MAINTENANCE_H

#include <QDialog>

namespace Ui {
class MAINTENANCE;
}

class MAINTENANCE : public QDialog
{
    Q_OBJECT

public:
    explicit MAINTENANCE(QWidget *parent = nullptr);
    ~MAINTENANCE();
private slots:


    void on_pushButton_ADD_clicked();

    void on_pushButton_back_clicked();

    void on_pushButton_clear_2_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_ADMIT_clicked();

private:
    Ui::MAINTENANCE *ui;
};

#endif // MAINTENANCE_H
