#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QTableView>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

#include <QString>
#include <QMessageBox>

#include <QStandardItemModel>
#include <QStandardItem>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void dbadd();
    void closedb();

    void ShowContact(QString LastName="");
    void showTable(QString lastName);

private slots:
    void on_lineEdit_editingFinished();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QStandardItemModel *model=nullptr;
    QStandardItem *item;
};

#endif // MAINWINDOW_H
