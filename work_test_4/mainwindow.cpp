#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QTableView>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

#include <QString>
#include <QMessageBox>

#include "add.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setMinimumSize(320, 350);
    setMaximumSize(320, 350);
    setWindowTitle(tr("Contacts book"));

    db=QSqlDatabase::addDatabase("QSQLITE");

    QString pathToDB =QString(PRO_FILE_PWD)+QString("/contacts.sqlite");

    db.setDatabaseName(pathToDB);

    dbadd();
    showTable("");
}

MainWindow::~MainWindow()
{
    if(db.isOpen())
        db.close();
    delete ui;
}

void MainWindow:: dbadd(){
    QMessageBox qms;

    if ((!db.open())) {
        qms.setText(db.lastError().databaseText()+db.lastError().driverText());
        qms.exec();
    }

}


void MainWindow::showTable(QString lastName)
{
    QSqlQuery sql;
    if(model==nullptr)
    {
        model = new QStandardItemModel;
    }
    else
    {
        model->clear();
    }

    QStringList horizontalHeader;
    horizontalHeader.append("First name");
    horizontalHeader.append("Last name");
    horizontalHeader.append("Phone");
    model->setHorizontalHeaderLabels(horizontalHeader);

    if(lastName=="")
    {
        sql.prepare("select Count(*) from Contacts;");
    }
    else
    {
        sql.prepare("select Count(*) from Contacts WHERE Last=?;");
        sql.bindValue(0,lastName);
    }
    sql.exec();
    sql.next();
    int count = sql.value(0).toInt();

    model->setRowCount(count);
    model->setColumnCount(4);

    if(lastName=="")
    {
        sql.prepare("select * from Contacts;");
    }
    else
    {
        sql.prepare("select * from Contacts WHERE Last=?;");
        sql.bindValue(0,lastName);
    }
    sql.exec();
    int row=0;
    int id;
    while(sql.next())
    {
        QString L = sql.value(1).toString();
        QString F = sql.value(2).toString();
        QString P = sql.value(3).toString();
        id=sql.value(0).toInt();

        model->setItem(row,0,new QStandardItem(L));
        model->setItem(row,1,new QStandardItem(F));
        model->setItem(row,2,new QStandardItem(P));
        model->setItem(row,3,new QStandardItem(QString::number(id)));
        row++;
    }

    ui->tableView->setModel(model);
    ui->tableView->hideColumn(3);
    ui->tableView->resizeRowsToContents();

}

void MainWindow::on_lineEdit_editingFinished()
{
    showTable(ui->lineEdit->text());
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    QMessageBox msgBox;
    QSqlQuery sql;
    Add *addContact=new Add();
    int c,id;
    QString L,F,P;
    L = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString();
    F = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),1)).toString();
    P = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),2)).toString();
    id = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),3)).toInt();

    addContact->setC(L,F,P,id);
    c=addContact->exec();
    switch (c)
    {

    case 1:

        sql.prepare("UPDATE Contacts SET Last = :ln, First = :fn, Phone = :ph WHERE id = :ID");
        sql.bindValue(":ln",addContact->Last);
        sql.bindValue(":fn",addContact->First);
        sql.bindValue(":ph",addContact->Phone);
        sql.bindValue(":ID",addContact->ID);
        sql.exec();

        break;

    case 2:
        sql.prepare("DELETE FROM Contacts WHERE id = :ID ");
        sql.bindValue(":ID", addContact->ID);
        sql.exec();
        break;
    default:
        break;
    }
    delete addContact;
    showTable("");

}

void MainWindow::on_pushButton_clicked()
{
    QSqlQuery sql;
    Add *addContact=new Add();

    if(addContact->exec()==1)
    {
        sql.prepare("INSERT INTO Contacts (Last, First, Phone)"
                    "VALUES (?, ?, ?)");
        sql.bindValue(0,addContact->Last);
        sql.bindValue(1,addContact->First);
        sql.bindValue(2,addContact->Phone);
        sql.exec();

    }
    delete addContact;
    showTable("");
}
