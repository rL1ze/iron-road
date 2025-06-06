#ifndef DATABASE_H
#define DATABASE_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qtableview.h"
#include <qsqldatabase.h>

class database
{
public:
    database();
    ~database();
    void connect(Ui::MainWindow *ui);
    void read(QTableView *view);
    void addData(Ui::MainWindow *ui);
    void deleteData(Ui::MainWindow *ui);
    void updateData(Ui::MainWindow *ui);
    void searchData(Ui::MainWindow *ui);

private:
    QSqlDatabase db;
};


#endif // DATABASE_H
