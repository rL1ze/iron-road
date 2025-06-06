#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_selectAct_activated(int index);

    void on_buttonAdd_clicked();

    void on_buttonUpdate_clicked();

    void on_buttonDelete_clicked();

    void on_buttonSearch_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
