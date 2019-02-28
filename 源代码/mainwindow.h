#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void newFile();   // 新建操作
    bool maybeSave(); // 判断是否需要保存
    bool save();      // 保存操作
    bool saveAs();    // 另存为操作
    bool saveFile(const QString &fileName); // 保存文件
private slots:
    void on_submitBtn_clicked();
    void on_ShowBtn_clicked();
    void on_revertBtn_clicked();
    void on_deletBtn_clicked();

    void on_insertBtn_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_selectBtn_clicked();

private:
    Ui::MainWindow *ui;
   QSqlTableModel *model;
};

#endif // MAINWINDOW_H
