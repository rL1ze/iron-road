#include "mainwindow.h"
#include "database.h"
#include "qcalendarwidget.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

database *db = new database;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->selectAct, &QComboBox::activated, this, &MainWindow::on_selectAct_activated);
    ui->stackedActionsWidget->setCurrentIndex(0);
    ui->departureTimeEdit->setCalendarPopup(true);
    ui->departureTimeEdit->calendarWidget()->setLocale(QLocale(QLocale::Russian));
    ui->departureTimeEdit_2->setCalendarPopup(true);
    ui->departureTimeEdit_2->calendarWidget()->setLocale(QLocale(QLocale::Russian));

    setFixedSize(size());
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    db->connect(ui);
    db->read(ui->mainViewDB);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_selectAct_activated(int index)
{
    ui->stackedActionsWidget->setCurrentIndex(index);
}

void MainWindow::on_buttonAdd_clicked()
{
    if(ui->AvaiableSeatsEdit->text().isEmpty()
        || ui->departureTimeEdit->text().isEmpty()
        || ui->destinationEdit->text().isEmpty()){
        QMessageBox::warning(this, "Оповещение", "Заполните все поля!");
    }
    else{
        db->addData(ui);
        db->read(ui->mainViewDB);
    }
}

void MainWindow::on_buttonUpdate_clicked()
{
    if(ui->AvaiableSeatsEdit_2->text().isEmpty()
        || ui->departureTimeEdit_2->text().isEmpty()
        || ui->destinationEdit_2->text().isEmpty()){
        QMessageBox::warning(this, "Оповещение", "Заполните все поля!");
    }
    else{
        db->updateData(ui);
        db->read(ui->mainViewDB);
    }
}


void MainWindow::on_buttonDelete_clicked()
{
    if(ui->trainIDeleteEdit->text().isEmpty()){
        QMessageBox::warning(this, "Оповещение", "Заполните все поля!");
    }
    else{
        db->deleteData(ui);
        db->read(ui->mainViewDB);
    }
}


void MainWindow::on_buttonSearch_clicked()
{
    if(ui->searchEdit->text().isEmpty()){
        QMessageBox::warning(this, "Оповещение", "Заполните поля поиска!");
    }
    else{
        db->searchData(ui);
    }
}

