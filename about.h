#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

namespace Ui {
class ABOUT;
}

class ABOUT : public QDialog
{
    Q_OBJECT

public:
    explicit ABOUT(QWidget *parent = nullptr);
    ~ABOUT();

private slots:
    void on_pushButton_BACK_clicked();

private:
    Ui::ABOUT *ui;
};

#endif // ABOUT_H
