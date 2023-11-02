#ifndef TC_H
#define TC_H

#include <QDialog>

namespace Ui {
class tc;
}

class tc : public QDialog
{
    Q_OBJECT

public:
    explicit tc(QWidget *parent = nullptr);
    ~tc();

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_PRINT_clicked();

private:
    Ui::tc *ui;
};

#endif // TC_H
