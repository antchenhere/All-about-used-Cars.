#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;
struct CarInfo {
    string url = "";
    string region = "";
    int price = -1;
    short year = 0;
    string make = "";
    string model = "";
    short condition = -1;
    int cylinders = 0;
    short fuel = -1;
    unsigned int miles = 0;
    short titleStat = -1;
    short transmission = -1;
    string VIN = "";
    short drive = 0;
    string color = "";
    string image = "";
    string state = "";
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool checkLegit(CarInfo*);
    string getFunctionVal();

    void printTable2();
    void printTableBack();



private slots:

    void on_FindButton_clicked();

    void on_CBMake_clicked();

    void on_CBYear_clicked();

    void on_CBOdometer_clicked();

    void on_CBCost_clicked();

    void on_CBState_clicked();

    void on_CbSpecialParameters_clicked();

    void on_pushButtonNext_clicked();

    void on_pushButtonPrev_clicked();

    void on_pushButtonAdd_clicked();

    void on_pushButtonRemove_clicked();

    void on_pushButtonNext_2_clicked();

    void on_pushButtonPrev_2_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_tableWidget_2_cellClicked(int row, int column);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
