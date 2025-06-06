#include "database.h"
#include "qmessagebox.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QHostInfo>
#include <QSqlQueryModel>

database::database() : db(QSqlDatabase::addDatabase("QODBC")) {}

database::~database() {
    db.close();
}

void database::connect(Ui::MainWindow *ui){
    QString connectString = "Driver={SQL Server};";                     // Driver is now {SQL Server Native Client 11.0}
    connectString.append("Server=lpc:"+QHostInfo::localHostName()+"\\SQLEXPRESS;");   // Hostname,SQL-Server Instance
    connectString.append("Database=schedule;");  // Schema
    db.setDatabaseName(connectString);
    if(db.open()) {
        ui->statusbar->showMessage("Connected");
    } else {
        ui->statusbar->showMessage("Not connected");
        qDebug() << "Ошибка подключения к базе данных:";
    }
}

void database::read(QTableView *view){
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT Destination, DepartureTime, JourneyTime, AvailableSeats FROM Trains");
    model->setHeaderData(0, Qt::Horizontal, "Пункт назначения");
    model->setHeaderData(1, Qt::Horizontal, "Время отправления");
    model->setHeaderData(2, Qt::Horizontal, "Время в пути");
    model->setHeaderData(3, Qt::Horizontal, "Свободные места");
    view->setModel(model);
    view->resizeColumnsToContents();
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void database::addData(Ui::MainWindow *ui) {
    QMessageBox *mess = new QMessageBox();
    QSqlQuery *query = new QSqlQuery();

    query->prepare("INSERT INTO Trains(TrainID, Destination, DepartureTime, JourneyTime, AvailableSeats) VALUES (:tid, :dest, :dt, :jt, :avas)");

    int rowCount = ui->mainViewDB->model()->rowCount();
    if(ui->trainIDAddEdit->text().toInt() <= rowCount){
        mess->setText("Произошла ошибка! ID не должен быть меньше значения ID прерыдущей строки!");
        mess->exec();
        return;
    }else{
        query->bindValue(":tid", ui->trainIDAddEdit->text().toInt());
    }

    query->bindValue(":dest", ui->destinationEdit->text());
    query->bindValue(":dt", ui->departureTimeEdit->text());
    query->bindValue(":jt", ui->JorneyTimeEdit->text());
    query->bindValue(":avas", ui->AvaiableSeatsEdit->text().toInt());

    if (!query->exec()) {
        mess->setText("Произошла ошибка! Попробуйте снова!");
    } else {
        mess->setText("Запись успешна добавлена!");
    }
    mess->exec();
}

void database::updateData(Ui::MainWindow *ui){
    QMessageBox *mess = new QMessageBox();
    QSqlQuery *query = new QSqlQuery();

    query->prepare("UPDATE Trains SET TrainID = :tid, Destination = :dest, DepartureTime = :dt, JourneyTime = :jt, AvailableSeats = :avas WHERE TrainID = :tid");

    if(ui->trainIDUpdateEdit->text().toInt() <= 0){
        mess->setText("Произошла ошибка! ID не должен быть меньше ID существующих записей");
        mess->exec();
        return;
    }else{
        query->bindValue(":tid", ui->trainIDUpdateEdit->text().toInt());
    }

    query->bindValue(":dest", ui->destinationEdit_2->text());
    query->bindValue(":dt", ui->departureTimeEdit_2->text());
    query->bindValue(":jt", ui->JorneyTimeEdit_2->text());
    query->bindValue(":avas", ui->AvaiableSeatsEdit_2->text().toInt());

    if (!query->exec()) {
        mess->setText("Произошла ошибка! Попробуйте снова!");
    }
    else {
        mess->setText("Запись успешна обновлена!");
    }
    mess->exec();
}

void database::deleteData(Ui::MainWindow *ui){
    QMessageBox *mess = new QMessageBox();
    QSqlQuery *query = new QSqlQuery();

    query->prepare("DELETE FROM Trains WHERE TrainID = :tid");

    if(ui->trainIDeleteEdit->text().toInt() <= 0){
        mess->setText("Произошла ошибка! ID не должен быть меньше ID существующих записей");
        mess->exec();
        return;
    }else{
        query->bindValue(":tid", ui->trainIDeleteEdit->text().toInt());
    }

    if (!query->exec()) {
        mess->setText("Произошла ошибка! Попробуйте снова!");
    }
    else {
        mess->setText("Запись успешна удалена!");
    }
    mess->exec();
}

void database::searchData(Ui::MainWindow *ui){
    QSqlQueryModel *model = new QSqlQueryModel();
    QMessageBox *mess = new QMessageBox();
    QSqlQuery query;
    QString subquery = "SELECT * FROM Trains ";
    subquery.append("WHERE TrainID LIKE :search OR ");
    subquery.append("Destination LIKE :search OR ");
    subquery.append("DepartureTime LIKE :search OR ");
    subquery.append("JourneyTime LIKE :search OR ");
    subquery.append("AvailableSeats LIKE :search");
    query.prepare(subquery);
    query.bindValue(":search", ui->searchEdit->text() + "%");

    if (query.exec()) {
        model->setQuery(std::move(query));
        model->setHeaderData(0, Qt::Horizontal, "ID Поезда");
        model->setHeaderData(1, Qt::Horizontal, "Пункт назначения");
        model->setHeaderData(2, Qt::Horizontal, "Время отправления");
        model->setHeaderData(3, Qt::Horizontal, "Время в пути");
        model->setHeaderData(4, Qt::Horizontal, "Свободные места");
        ui->resViewSearching->setModel(model);
        ui->resViewSearching->resizeColumnsToContents();
        mess->setText("Запись найдена!");
    }
    else {
        mess->setText("Произошла ошибка! Попробуйте снова!");
    }
    mess->exec();
}

