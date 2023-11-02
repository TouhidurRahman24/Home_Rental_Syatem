#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QDialog>

namespace Ui {
class notepad;
}

class notepad : public QDialog
{
    Q_OBJECT

public:
    explicit notepad(QWidget *parent = nullptr);
    ~notepad();

private slots:
    void on_pushButton_BACK_clicked();

    void on_pushButton_ADD_clicked();

    void on_tableWidget_list_activated(const QModelIndex &index);

    void on_pushButton_UPDATE_clicked();

    void on_pushButton_DELETE_clicked();

    void on_pushButton_CLEAR_clicked();

    void on_pushButtonDELETE_ALL_clicked();

    void show();

private:
    Ui::notepad *ui;
};

#endif // NOTEPAD_H
