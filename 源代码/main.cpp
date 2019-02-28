#include "mainwindow.h"
#include <QApplication>
#include "logindialog.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QtSql>
#include <QtGui>
#include <QString>
#include <QSqlQueryModel>
#include "ui_mainwindow.h"

void OpenDatabase() //打开数据库
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName(QString("DRIVER={SQL SERVER};"
                               "SERVER=%1;" //服务器名称
                               "DATABASE=%2;"//数据库名
                               "UID=%3;"           //登录名
                               "PWD=%4;"        //密码
                               ).arg("DESKTOP-05HT9SO\\MYSQLSERVER")
                       .arg("BM")
                       .arg("ZHD")
                       .arg("123456")
                       );
    if (!db.open())
    {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              db.lastError().databaseText(), QMessageBox::Cancel);

    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    LoginDialog dlg;
        if (dlg.exec() == QDialog::Accepted)
        {
           w.show();
           //打开数据库
           OpenDatabase();

           return a.exec();
        }
        else return 0;
}
