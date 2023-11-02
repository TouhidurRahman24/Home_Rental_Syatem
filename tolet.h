#ifndef TOLET_H
#define TOLET_H

#include <QDialog>

namespace Ui {
class TOLET;
}

class TOLET : public QDialog
{
    Q_OBJECT

public:
    explicit TOLET(QWidget *parent = nullptr);
    ~TOLET();

private slots:
    void on_pushButton_BACK_clicked();

private:
    Ui::TOLET *ui;
};

#endif // TOLET_H
