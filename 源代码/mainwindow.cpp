#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>
#include <QSqlError>
#include <Qstring>
#include <QTableView>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QSqlTableModel(this);
    ui->userlabel->setVisible(false);
    ui->userNamelineEdit->setVisible(false);
    setWindowTitle("图书管理系统");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ShowBtn_clicked()
{
    QString text;
    model = new QSqlTableModel(this);
    text=ui->comboBox->currentText();
    if(!QString::compare(text,"图书信息"))
        model->setTable("books");
    else if(!QString::compare(text,"用户信息"))
        model->setTable("users");
    else if(!QString::compare(text,"借还记录"))
        model->setTable("bookbrowse");
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();
    ui->tableView->setModel(model);
}

void MainWindow::on_submitBtn_clicked()
{

        model->database().transaction(); //开始事务操作
        if (model->submitAll()) {
           model->database().commit(); //提交
        } else {
           model->database().rollback(); //回滚
           QMessageBox::warning(this, tr("tableModel"),
                                 tr("数据库错误: %1")
                                 .arg(model->lastError().text()));
        }
}

void MainWindow::on_revertBtn_clicked()
{

     model->revertAll();
}

void MainWindow::on_deletBtn_clicked()
{
    //获取选中的行
        int curRow = ui->tableView->currentIndex().row();

        //删除该行
        model->removeRow(curRow);

        int ok = QMessageBox::warning(this,tr("删除当前行!"),tr("你确定"
                                                     "删除当前行吗？"),
                                      QMessageBox::Yes,QMessageBox::No);
        if(ok == QMessageBox::No)
        {
           model->revertAll(); //如果不删除，则撤销
        }
        else model->submitAll(); //否则提交，在数据库中删除该行
}

void MainWindow::on_insertBtn_clicked()
{
    int rowNum = model->rowCount(); //获得表的行数
        model->insertRow(rowNum); //添加一行

}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    if(!QString::compare(arg1,"用户信息"))
    {
        ui->booklabel->setVisible(false);
        ui->bookNamelineEdit->setVisible(false);
        ui->authorlabel->setVisible(false);
        ui->authorNamelineEdit->setVisible(false);

        ui->bookNamelineEdit->clear();
        ui->authorNamelineEdit->clear();

        ui->userlabel->setVisible(true);
        ui->userNamelineEdit->setVisible(true);
    }
    else if(!QString::compare(arg1,"图书信息"))
    {
        ui->userlabel->setVisible(false);
        ui->userNamelineEdit->setVisible(false);

        ui->userNamelineEdit->clear();

        ui->booklabel->setVisible(true);
        ui->bookNamelineEdit->setVisible(true);
        ui->authorlabel->setVisible(true);
        ui->authorNamelineEdit->setVisible(true);
    }
     else if(!QString::compare(arg1,"借还记录"))
    {
        ui->userlabel->setVisible(false);
        ui->userNamelineEdit->setVisible(false);
        ui->booklabel->setVisible(false);
        ui->bookNamelineEdit->setVisible(false);
        ui->authorlabel->setVisible(false);
        ui->authorNamelineEdit->setVisible(false);

        ui->bookNamelineEdit->clear();
        ui->authorNamelineEdit->clear();
        ui->userNamelineEdit->clear();
    }
}

void MainWindow::on_selectBtn_clicked()
{
    QString sid = ui->idlineEdit->text();
    QString bookname = ui->bookNamelineEdit->text();
    QString authorname = ui->authorNamelineEdit->text();
    QString username = ui->userNamelineEdit->text();
    int nid = sid.toInt();
    if(!sid.isEmpty())
    model->setFilter(QString("id = %1").arg(nid));
    if(!bookname.isEmpty())
    model->setFilter(QString("bookname = '%1'").arg(bookname));
    if(!authorname.isEmpty())
    model->setFilter(QString("author = '%1'").arg(authorname));
    if(!username.isEmpty())
    model->setFilter(QString("username = '%1'").arg(username));
    //显示结果
    model->select();
}
