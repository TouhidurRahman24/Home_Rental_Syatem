#ifndef PROFILE_H
#define PROFILE_H

#include <QDialog>

namespace Ui {
class profile;
}

class profile : public QDialog
{
    Q_OBJECT
public:
     bool accept= false,found=false;
     QString username;
public:
    explicit profile(QWidget *parent = nullptr);
    ~profile();

private slots:
    void on_pushButton_BACK_clicked();
    void show();
    void on_pushButton_EDIT_clicked();

    void on_pushButton_DELETE_clicked();

private:
    Ui::profile *ui;
};

#endif // PROFILE_H
