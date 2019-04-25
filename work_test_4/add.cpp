#include "add.h"
#include "ui_add.h"

Add::Add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add)
{
    ui->setupUi(this);

    ui->pushButton_d->hide();
    ui->pushButton_s->setText("Add");
    ui->pushButton_s->setEnabled(false);
    i=0;

    ui->lineEdit->setStyleSheet("border : 1px solid red");
    ui->lineEdit_2->setStyleSheet("border : 1px solid red");
    ui->lineEdit_3->setStyleSheet("border : 1px solid red");
    activateWindow();
}

Add::~Add()
{
    delete ui;
}

void Add::on_pushButton_d_clicked()
{
    done(2);

}

void Add::on_pushButton_s_clicked()
{

    done(1);
}

void Add::on_pushButton_a_clicked()
{
    done(0);
}

void Add::setC(QString last, QString first, QString phone, int id)
{
    ui->lineEdit->setStyleSheet("border : 1px solid black");
    ui->lineEdit_2->setStyleSheet("border : 1px solid black");
    ui->lineEdit_3->setStyleSheet("border : 1px solid black");

    ui->pushButton_s->setText("Save");

    ui->lineEdit->setText(last);
    Last = last;
    ui->lineEdit_2->setText(first);
    First = first;
    ui->lineEdit_3->setText(phone);
    Phone=phone;

    ui->pushButton_d->show();
    ui->pushButton_s->setDisabled(true);
    ui->pushButton_d->setEnabled(true);


    ID=id;
}




void Add::on_lineEdit_textChanged(const QString &arg1)
{
    a=1;
    ui->pushButton_d->setEnabled(false);
    if(!Last.isEmpty())
    {
        ui->lineEdit->setStyleSheet("border : 1px solid black");
    }
    Last=ui->lineEdit->text();
    if(a==1&&b==1&&c==1)
    {
        ui->pushButton_s->setEnabled(true);
    }
}

void Add::on_lineEdit_2_textChanged(const QString &arg1)
{
    b=1;
    ui->pushButton_d->setEnabled(false);
    if(!First.isEmpty())
    {
        ui->lineEdit_2->setStyleSheet("border : 1px solid black");
    }
    First=ui->lineEdit_2->text();

    if(a==1&&b==1&&c==1)
    {
        ui->pushButton_s->setEnabled(true);
    }
}

void Add::on_lineEdit_3_textChanged(const QString &arg1)
{
    c=1;
    ui->pushButton_d->setEnabled(false);
    if(!Phone.isEmpty())
    {
        ui->lineEdit_3->setStyleSheet("border : 1px solid black");
        ;
    }
    Phone=ui->lineEdit_3->text();

    if(a==1&&b==1&&c==1)
    {
        ui->pushButton_s->setEnabled(true);
    }
}
