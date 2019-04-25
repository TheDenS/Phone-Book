#ifndef ADD_H
#define ADD_H

#include <QDialog>

namespace Ui {
class Add;
}

class Add : public QDialog
{
    Q_OBJECT

public:
    explicit Add(QWidget *parent = nullptr);
    ~Add();
    void setC(QString last, QString first, QString phone, int id);
    QString Last,First,Phone;
    int ID;

private slots:
    void on_pushButton_d_clicked();

    void on_pushButton_s_clicked();

    void on_pushButton_a_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_3_textChanged(const QString &arg1);

private:
    Ui::Add *ui;
    int i,a,b,c;
};

#endif // ADD_H
