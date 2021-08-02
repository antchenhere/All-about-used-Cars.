#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <set>
#include <chrono>
#include <stack>
#include <stdio.h>
#include <QMessageBox>

using namespace std;

vector<CarInfo*> dataStrucVec;
vector<CarInfo*> dataStrucVec2;
vector<string> hereStates;
map<string,vector<CarInfo*>> carMap;

map<int,string>mapCondition;
map<int,string>mapFuel;
map<int,string>mapTitle;
map<int,string>mapDrive;
map<int,string>mapTransmission;
int page = 0;
int page2 = 0;
string Userfunction = "";
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->EditMake->setEnabled(false);
    ui->EditCostMax->setEnabled(false) ;
    ui->EditCostMin->setEnabled(false) ;
    ui->EditOdoMax->setEnabled(false) ;
    ui->EditOdoMin->setEnabled(false) ;
    ui->EditYearMax->setEnabled(false) ;
    ui->EditYearMin->setEnabled(false) ;

    ui->comboBoxState->setEnabled(false);
    ui->pushButtonAdd->setEnabled(false);
    ui->pushButtonRemove->setEnabled(false);
    ui->EditFunction->setEnabled(false);

    mapCondition.emplace(-1, "");
    mapCondition.emplace(0, "like new");
    mapCondition.emplace(1, "excellent");
    mapCondition.emplace(2, "new");
    mapCondition.emplace(3, "good");
    mapCondition.emplace(4, "fair");
    mapCondition.emplace(5, "salvage");
    mapFuel.emplace(-1, "");
    mapFuel.emplace(0, "gas");
    mapFuel.emplace(1, "diesel");
    mapFuel.emplace(2, "hybrid");
    mapFuel.emplace(3, "electric");
    mapFuel.emplace(4, "other");
    mapTitle.emplace(-1, "");
    mapTitle.emplace(0, "clean");
    mapTitle.emplace(1, "salvage");
    mapTitle.emplace(2, "rebuilt");
    mapTitle.emplace(3, "parts only");
    mapTitle.emplace(4, "lien");
    mapTitle.emplace(5, "missing");
    mapTransmission.emplace(-1, "");
    mapTransmission.emplace(0, "manual");
    mapTransmission.emplace(1, "automatic");
    mapTransmission.emplace(2, "other");
    mapDrive.emplace(-1,"");
    mapDrive.emplace(0,"fwd");
    mapDrive.emplace(1,"rwd");
    mapDrive.emplace(2,"4wd");


    ifstream inFS;
    ofstream oFS;
    inFS.open("E:/UF School Work/2021 Summer/FinProj/Files/vehicles2.csv");
    cout << "hi";
    string data = "";
    string state = "";
    int count = 0;
    bool addData = true;

    for (int i = 0; i < 24; i++) {
        getline(inFS, data, ',');
        cout << data << ", ";
    }
    getline(inFS, data);
    CarInfo* stats;

    while (!inFS.eof()) {
        if (count == 0) {
            stats = new CarInfo;

        }

        switch (count) {
        case 0:
            getline(inFS, state, ',');
            if (carMap.find(state) == carMap.end()) {
                carMap.emplace(state, vector<CarInfo*>{});
            }
            carMap.at(state).push_back(stats);
            carMap.at(state).back()->state = state;
            break;
        case 1:
            getline(inFS, data, ',');
            carMap.at(state).back()->url = data;

            break;
        case 2:
            getline(inFS, data, ',');
            carMap.at(state).back()->region = data;
            break;

        case 3:
            getline(inFS, data, ',');
            break;
        case 4:
            getline(inFS, data, ',');

            try {
            if (data != "0") {

                carMap.at(state).back()->price = stoi(data);
            }
            else {
                addData = false;

                carMap.at(state).pop_back();
            }
        }
            catch(exception e){
                addData = false;

                carMap.at(state).pop_back();
            }

            break;
            if (data != "0") {

                carMap.at(state).back()->price = stoi(data);
            }
            else {
                addData = false;

                carMap.at(state).pop_back();
            }
            break;
        case 5:
            getline(inFS, data, ',');
            if (!addData)
                break;
            if (data != "") {
                carMap.at(state).back()->year = stoi(data);

            }

            break;
        case 6:

            getline(inFS, data, ',');
            if (!addData)
                break;
            carMap.at(state).back()->make = data;

            break;
        case 7:
            getline(inFS, data, ',');
            if (!addData)
                break;
            carMap.at(state).back()->model = data;

            break;
        case 8:
            getline(inFS, data, ',');
            if (!addData)
                break;
            if (data._Equal("like new"))
                carMap.at(state).back()->condition = 0;
            else if (data._Equal("excellent"))
                carMap.at(state).back()->condition = 1;
            else if (data._Equal("new"))
                carMap.at(state).back()->condition = 2;
            else if (data._Equal("good"))
                carMap.at(state).back()->condition = 3;
            else if (data._Equal("fair"))
                carMap.at(state).back()->condition = 4;
            else if (data._Equal("salvage"))
                carMap.at(state).back()->condition = 5;
            break;
        case 9:
            getline(inFS, data, ',');
            if (!addData)
                break;
            break;
        case 10:
            getline(inFS, data, ',');
            if (!addData)
                break;
            if (data._Equal("gas"))
                carMap.at(state).back()->fuel = 0;
            else if (data._Equal("diesel"))
                carMap.at(state).back()->fuel = 1;
            else if (data._Equal("hybrid"))
                carMap.at(state).back()->fuel = 2;
            else if (data._Equal("electric"))
                carMap.at(state).back()->fuel = 3;
            else if (data._Equal("other"))
                carMap.at(state).back()->fuel = 4;
            break;
        case 11:
            getline(inFS, data, ',');

            if (!addData)
                break;
            if (data != "")

                carMap.at(state).back()->miles = stoi(data);


            break;
        case 12:
            getline(inFS, data, ',');
            if (!addData)
                break;
            if (data._Equal("clean"))
                carMap.at(state).back()->titleStat = 0;
            else if (data._Equal("salvage"))
                carMap.at(state).back()->titleStat = 1;
            else if (data._Equal("rebuilt"))
                carMap.at(state).back()->titleStat = 2;
            else if (data._Equal("parts only"))
                carMap.at(state).back()->titleStat = 3;
            else if (data._Equal("lien"))
                carMap.at(state).back()->titleStat = 4;
            else if (data._Equal("missing"))
                carMap.at(state).back()->titleStat = 5;
            break;
        case 13:
            getline(inFS, data, ',');
            if (!addData)
                break;
            if (data._Equal("manual"))
                carMap.at(state).back()->transmission = 0;
            else if (data._Equal("automatic"))
                carMap.at(state).back()->transmission = 1;
            else if (data._Equal("other"))
                carMap.at(state).back()->transmission = 2;
            break;
        case 14:
            getline(inFS, data, ',');
            if (!addData)
                break;

            carMap.at(state).back()->VIN = data;
            break;
        case 15:
            getline(inFS, data, ',');
            if (!addData)
                break;
            if (data._Equal("fwd"))
                carMap.at(state).back()->drive = 0;
            else if (data._Equal("rwd"))
                carMap.at(state).back()->drive = 0;
            else if (data._Equal("4wd"))
                carMap.at(state).back()->drive = 0;
            break;
        case 16:
            getline(inFS, data, ',');
            break;
        case 17:
            getline(inFS, data, ',');

            break;
        case 18:
            getline(inFS, data, ',');
            if (!addData)
                break;

            carMap.at(state).back()->color = data;
            break;
        case 19:
            getline(inFS, data, ',');
            if (!addData)
                break;

            carMap.at(state).back()->image = data;
            break;
        case 20:
            getline(inFS, data, ',');
            break;
        case 21:
            getline(inFS, data, ',');
            if (!addData)
                break;
            break;
        case 22:
            getline(inFS, data, ',');
            break;
        case 23:
            getline(inFS, data, ',');
            break;

        case 24:
            getline(inFS, data);
            count = -1;
            addData = true;

        }
        count++;
    }
    carMap.erase("");
    inFS.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}
double solve(string s, int c, int y, int m) {
    double result = 0.0;
    vector <double> vals;
    vector <char> op;
    string send = "";
    stack<bool> stk;
    for (int i = 0; i < s.length(); i++) {
        if (stk.size() > 0)send += s.at(i);

        if (s.at(i) == '(') {
            stk.push(true);
        }
        else if (s.at(i) == ')') {
            if (stk.top() == true) {
                stk.pop();
                if (stk.size() == 0) {
                    send = send.substr(0, send.length() - 1);
                    vals.push_back(solve(send, c, y, m));
                }
            }
        }
        else if (stk.size() == 0) {
            if (s.at(i) == 'C') {
                vals.push_back(c);
            }
            else if (s.at(i) == 'M') {
                vals.push_back(m);
            }
            else if (s.at(i) == 'Y') {
                vals.push_back(y);
            }
            else if (s.at(i) == '+') {
                op.push_back('+');
            }
            else if (s.at(i) == '-') {
                op.push_back('-');
            }
            else if (s.at(i) == '*') {
                op.push_back('*');
            }
            else if (s.at(i) == '/') {
                op.push_back('/');
            }
            else {
                vals.push_back(stoi(s.substr(i)));
                int digits = 0;
                int backcopy = vals.back();
                backcopy /= 10;
                while (backcopy != 0) {
                    backcopy /= 10;
                    digits++;
                }
                i += digits;
            }

        }


    }
    cout << endl;
    for (int i = 0; i < op.size(); i++) {
        cout << op.at(i) << " ";
    }
    cout << endl;
    for (int i = 0; i < vals.size(); i++) {
        cout << vals.at(i) << " ";
    }
    cout << endl;
    bool priority = true;
    while (op.size() >0) {

        while (priority) {

            priority = false;

            for (int i = 0; i < op.size(); i++) {
                if ((op.at(i) == '*' || op.at(i) == '/' )&& !priority) {
                    priority = true;
                    if (op.at(i) == '*') {
                        cout << vals.at(i) << "*" << vals.at(i+1);
                        vals.at(i) *= (double)vals.at(i + 1);

                    }
                    else if (op.at(i) == '/') {
                         cout << vals.at(i) << "/" << vals.at(i+1);
                        vals.at(i) /= (double)vals.at(i + 1);

                    }
                }
                else if (priority) {
                        op.at(i - 1) = op.at(i);
                        vals.at(i ) = vals.at(i+1);
                }
            }
            if (priority) {
                op.pop_back();
                vals.pop_back();
            }
            cout << endl;
            for (int i = 0; i < op.size(); i++) {
                cout << op.at(i) << " ";
            }
            cout << endl;
            for (int i = 0; i < vals.size(); i++) {
                cout << vals.at(i) << " ";
            }
            cout << endl;
        }
        if (op.size() == 0)break;
        if (op.at(0) == '+') {
            vals.at(0) += (double)vals.at(1);
        }
        else if (op.at(0) == '-') {
            vals.at(0) -= (double)vals.at(1);
        }
        if (op.size()!=1) {
            for (int i = 2; i < op.size(); i++) {
                op.at(i - 1) = op.at(i);
                vals.at(i - 1) = vals.at(i);
            }
        }
            op.pop_back();
            vals.pop_back();
            cout << endl;
            for (int i = 0; i < op.size(); i++) {
                cout << op.at(i) << " ";
            }
            cout << endl;
            for (int i = 0; i < vals.size(); i++) {
                cout << vals.at(i) << " ";
            }
            cout << endl;

    }
    cout << endl;
    return vals.at(0);
}


string MainWindow::getFunctionVal(){
    string function = ui->EditFunction->text().toStdString();
    return function;
}

double getCorrectVal(CarInfo* v, int i){
    if(i == 0){
        return v->year;
    }if(i==1){
        return v->miles;
    }
    if(i==2){
        return v->price;
    }if(i==3){
        return  solve(Userfunction, v->price, v->year, v->miles);
    }

}

void Shellsort(vector<CarInfo*> &v, int t){
    CarInfo* temp;
    int gap = v.size()/2;
    int currentIndex = 0;
    while(gap > 0){
        for(int i = 0; i < v.size()-gap; i++){
            if(getCorrectVal(v.at(i),t)>getCorrectVal(v.at(i+gap),t)){
                temp = v.at(i);
                v.at(i) = v.at(i+gap);
                v.at(i+gap) = temp;
                currentIndex = i;
                while(currentIndex - gap >= 0&& getCorrectVal(v.at(currentIndex),t) < getCorrectVal(v.at(currentIndex-gap),t)){
                    temp = v.at(currentIndex);
                    v.at(currentIndex) = v.at(currentIndex - gap);
                    v.at(currentIndex-gap) = temp;
                    currentIndex -=gap;

                }
            }
        }
        gap/=2;
    }

}

void merge(vector<CarInfo*>& v,int start, int middle, int end, int data){
    int n1 = middle - start + 1;
    int n2 = end - middle;
    vector<CarInfo*> X(n1), Y(n2);
    for (int i = 0; i < n1; i++) {
        X.at(i) = v.at(start + i);
    }
    for (int i = 0; i < n2; i++) {
        Y.at(i) = v.at(i + middle + 1);
    }
    int i = 0, j = 0, k = start;
    while (i < n1 && j < n2) {
        if (getCorrectVal(X.at(i), data) <= getCorrectVal(Y.at(j), data)) {
            v.at(k) = X.at(i);
            i++;
        }
        else {
            v.at(k) = Y.at(j);
            j++;
        }
        k++;

    }
    while (i < n1) {
        v.at(k) = X.at(i);
        i++;
        k++;
    }
    while (j < n2) {
        v.at(k) = Y.at(j);
        j++;
        k++;
    }
}

void Mergesort(vector<CarInfo*>& v, int start, int end, int data){
    if(start < end){
        int middle = (start+end)/2;
        Mergesort(v,start, middle, data);
        Mergesort(v, middle+1, end, data);
        merge(v,start, middle, end, data);
    }
}

bool MainWindow::checkLegit(CarInfo* a){
    int maxCost = 214748367;
    int minCost = 0;
    int maxYear = 2022;
    int minYear = 0;
    int maxMiles = 214748367;
    int minMiles = 0;
    string make = "";
    if(ui->CBMake->isChecked()){
        if(ui->EditMake->text() != ""){
            make = ui->EditMake->text().toStdString();

            if(make != a->make)return false;
        }
    }
    if(ui->CBYear->isChecked()){
        if(ui->EditYearMax->text() != ""){
            maxYear = ui->EditYearMax->text().toInt();

        }if(ui->EditYearMin->text() != ""){
            minYear = ui->EditYearMin->text().toInt();
        }

        if(a->year > maxYear || a->year < minYear)return false;
    }
    if(ui->CBOdometer->isChecked()){
        if(ui->EditOdoMax->text() != ""){
            maxMiles = ui->EditOdoMax->text().toInt();

        }if(ui->EditOdoMin->text() != ""){
            minMiles = ui->EditOdoMin->text().toInt();
        }

        if(a->miles>maxMiles||a->miles<minMiles)return false;
    }
    if(ui->CBCost->isChecked()){
        if(ui->EditCostMax->text() != ""){
            maxCost = ui->EditCostMax->text().toInt();
        }if(ui->EditCostMin->text() != ""){
            minCost = ui->EditCostMin->text().toInt();
        }
        if(a->price>maxCost||a->price<minCost)return false;
    }

    return true;
}

void MainWindow::printTable2(){
    int pagesize = 10;
    int increment = pagesize;
    int start = 0;
    int end = dataStrucVec2.size()-1;
    if(dataStrucVec2.size()-(page*10)<10){
        pagesize = dataStrucVec2.size()-(page*10);
    }
    if (ui->RBMax->isChecked()){
        increment*=-1;
        start = end;
        end = 0;
    }
    for(int i = 0; i< pagesize; i++){
        QTableWidgetItem *itemMake = new QTableWidgetItem();
        itemMake->setText(QString::fromStdString(dataStrucVec2.at(start+(i*increment/10)+(page2*increment))->make) + " " + QString::fromStdString(dataStrucVec2.at(start+(i*increment/10)+(page*increment))->model));
        ui->tableWidget_2->setItem(i,0, itemMake);
        QTableWidgetItem *itemYear = new QTableWidgetItem();
        itemYear->setText(QString::number(dataStrucVec2.at(start+(i*increment/10)+(page2*increment))->year));
        ui->tableWidget_2->setItem(i,1, itemYear);
        QTableWidgetItem *itemOdo = new QTableWidgetItem();
        itemOdo->setText(QString::number(dataStrucVec2.at(start+(i*increment/10)+(page2*increment))->miles));
        ui->tableWidget_2->setItem(i,2, itemOdo);
        QTableWidgetItem *itemPrice = new QTableWidgetItem();
        itemPrice->setText(QString::number(dataStrucVec2.at(start+(i*increment/10)+(page2*increment))->price));
        ui->tableWidget_2->setItem(i,3, itemPrice);
    }if(pagesize<10){
        for(int i = 0; i< 10-pagesize; i++){
            QTableWidgetItem *itemMake = new QTableWidgetItem();
            itemMake->setText(" ");
            ui->tableWidget_2->setItem(i+pagesize,0, itemMake);
            QTableWidgetItem *itemYear = new QTableWidgetItem();
            itemYear->setText(" ");
            ui->tableWidget_2->setItem(i+pagesize,1, itemYear);
            QTableWidgetItem *itemOdo = new QTableWidgetItem();
            itemOdo->setText(" ");
            ui->tableWidget_2->setItem(i+pagesize,2, itemOdo);
            QTableWidgetItem *itemPrice = new QTableWidgetItem();
            itemPrice->setText(" ");
            ui->tableWidget_2->setItem(i+pagesize,3, itemPrice);
        }

    }
}

void MainWindow::printTableBack(){
    int pagesize = 10;
    int increment = pagesize;
    int start = 0;
    int end = dataStrucVec.size()-1;
    if(dataStrucVec.size()-(page*10)<10){
        pagesize = dataStrucVec.size()-(page*10);
    }
    if (ui->RBMax->isChecked()){
        increment*=-1;
        start = end;
        end = 0;
    }
    for(int i = 0; i< pagesize; i++){
        QTableWidgetItem *itemMake = new QTableWidgetItem();
        itemMake->setText(QString::fromStdString(dataStrucVec.at(start+(i*increment/10)+(page*increment))->make) + " " + QString::fromStdString(dataStrucVec.at(start+(i*increment/10)+(page*increment))->model));
        ui->tableWidget->setItem(i,0, itemMake);
        QTableWidgetItem *itemYear = new QTableWidgetItem();
        itemYear->setText(QString::number(dataStrucVec.at(start+(i*increment/10)+(page*increment))->year));
        ui->tableWidget->setItem(i,1, itemYear);
        QTableWidgetItem *itemOdo = new QTableWidgetItem();
        itemOdo->setText(QString::number(dataStrucVec.at(start+(i*increment/10)+(page*increment))->miles));
        ui->tableWidget->setItem(i,2, itemOdo);
        QTableWidgetItem *itemPrice = new QTableWidgetItem();
        itemPrice->setText(QString::number(dataStrucVec.at(start+(i*increment/10)+(page*increment))->price));
        ui->tableWidget->setItem(i,3, itemPrice);
    }if(pagesize<10){
        for(int i = 0; i< 10-pagesize; i++){
            QTableWidgetItem *itemMake = new QTableWidgetItem();
            itemMake->setText(" ");
            ui->tableWidget->setItem(i+pagesize,0, itemMake);
            QTableWidgetItem *itemYear = new QTableWidgetItem();
            itemYear->setText(" ");
            ui->tableWidget->setItem(i+pagesize,1, itemYear);
            QTableWidgetItem *itemOdo = new QTableWidgetItem();
            itemOdo->setText(" ");
            ui->tableWidget->setItem(i+pagesize,2, itemOdo);
            QTableWidgetItem *itemPrice = new QTableWidgetItem();
            itemPrice->setText(" ");
            ui->tableWidget->setItem(i+pagesize,3, itemPrice);
        }

    }

}

void MainWindow::on_FindButton_clicked()
{

    dataStrucVec2.clear();
    dataStrucVec.clear();
    if(ui->CBState->isChecked()){
        for(int i = 0; i < hereStates.size(); i++){
            //dataStrucVec.insert(dataStrucVec.end(), carMap.at(hereStates.at(i)).begin(), carMap.at(hereStates.at(i)).end());
            //dataStrucVec2.insert(dataStrucVec2.end(), carMap.at(hereStates.at(i)).begin(), carMap.at(hereStates.at(i)).end());
            for(int a = 0; a <  carMap.at(hereStates.at(i)).size();a++){
                if(checkLegit(carMap.at(hereStates.at(i)).at(a)))dataStrucVec.push_back(carMap.at(hereStates.at(i)).at(a));
            }
        }
    }else{
        for(auto it = carMap.begin(); it != carMap.end(); it++){
            //dataStrucVec.insert(dataStrucVec.end(), it->second.begin(), it->second.end());
            //dataStrucVec2.insert(dataStrucVec2.end(), it->second.begin(), it->second.end());
            for(int a = 0; a <  it->second.size();a++){
                if(checkLegit(it->second.at(a)))dataStrucVec.push_back(it->second.at(a));
            }
        }

    }

    dataStrucVec2.insert(dataStrucVec2.end(), dataStrucVec.begin(), dataStrucVec.end());
    page = 0;

    auto begin = std::chrono::high_resolution_clock::now();
    if(ui->RBYear->isChecked()){
        Shellsort(dataStrucVec, 0);
    }else if(ui->RBOdo->isChecked()){
        Shellsort(dataStrucVec, 1);
    }else if(ui->RBCost->isChecked()){
        Shellsort(dataStrucVec, 2);
    }else if(ui->RBFunction->isChecked()){
        Userfunction = getFunctionVal();
        Shellsort(dataStrucVec, 3);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    ui->lbltime1->setText(QString::fromStdString("Computational Time: " + to_string(elapsed.count())));

    printTableBack();
    ui->lblTotalCarsSorted->setText("Total Cars Sorted through: " + QString::number(dataStrucVec.size()));
    ui->lblPage->setText("Page: " + QString::number(page+1));

    begin = std::chrono::high_resolution_clock::now();
    if(ui->RBYear->isChecked()){
        Mergesort(dataStrucVec2,0,dataStrucVec2.size()-1,0);
    }else if(ui->RBOdo->isChecked()){
        Mergesort(dataStrucVec2,0,dataStrucVec2.size()-1,1);
    }else if(ui->RBCost->isChecked()){
        Mergesort(dataStrucVec2,0,dataStrucVec2.size()-1,2);
    }else if(ui->RBFunction->isChecked()){
        Userfunction = getFunctionVal();
        Mergesort(dataStrucVec2,0,dataStrucVec2.size()-1, 3);
    }


    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    ui->lbltime2->setText(QString::fromStdString("Computational Time: " + to_string(elapsed.count())));

    printTable2();

}

void MainWindow::on_CBMake_clicked()
{
    if(ui->CBMake->isChecked()){
        ui->EditMake->setEnabled(true);
    }else{
        ui->EditMake->setEnabled(false);

    }
}

void MainWindow::on_CBYear_clicked()
{
    if(ui->CBYear->isChecked()){
        ui->EditYearMax->setEnabled(true);
        ui->EditYearMin->setEnabled(true);

    }else{
        ui->EditYearMax->setEnabled(false);
        ui->EditYearMin->setEnabled(false);


    }
}

void MainWindow::on_CBOdometer_clicked()
{
    if(ui->CBOdometer->isChecked()){
        ui->EditOdoMax->setEnabled(true);
        ui->EditOdoMin->setEnabled(true);

    }else{
        ui->EditOdoMax->setEnabled(false);
        ui->EditOdoMin->setEnabled(false);
    }
}

void MainWindow::on_CBCost_clicked()
{
    if(ui->CBCost->isChecked()){
        ui->EditCostMax->setEnabled(true);
        ui->EditCostMin->setEnabled(true);
    }else{
        ui->EditCostMax->setEnabled(false);
        ui->EditCostMin->setEnabled(false);
    }
}

void MainWindow::on_CBState_clicked()
{
    if(ui->CBState->isChecked()){
        ui->comboBoxState->setEnabled(true);
        ui->pushButtonAdd->setEnabled(true);
        ui->pushButtonRemove->setEnabled(true);
        ui->lblStates->setText("States: none");
        hereStates.clear();
    }else{
        ui->comboBoxState->setEnabled(false);
        ui->pushButtonAdd->setEnabled(false);
        ui->pushButtonRemove->setEnabled(false);
        ui->lblStates->setText("States: ALL");
    }
}

void MainWindow::on_CbSpecialParameters_clicked()
{
    if(ui->CbSpecialParameters->isChecked()){
        ui->EditFunction->setEnabled(true);
        ui->RBFunction->setEnabled(true);

    }else{
        ui->EditFunction->setEnabled(false);
        ui->RBFunction->setEnabled(false);
    }
}

void MainWindow::on_pushButtonNext_clicked()
{
    bool max;
    max = ui->RBMax->isChecked();
    if(dataStrucVec.size()>(10*(page+1))){
        page++;
        printTableBack();
        ui->lblPage->setText("Page: " + QString::number(page+1));
    }
}

void MainWindow::on_pushButtonPrev_clicked()
{
    if(page-1>=0){
        page--;
        printTableBack();
        ui->lblPage->setText("Page: " + QString::number(page+1));
    }
}

void MainWindow::on_pushButtonAdd_clicked()
{
    QString s = ui->comboBoxState ->currentText();
    bool found = false;
    s = "States: ";
    for(int i = 0; i < hereStates.size(); i++){
        if(hereStates[i] == ui->comboBoxState ->currentText().toStdString()){
            found = true;
        }
        s+=QString::fromStdString(hereStates.at(i) + " ");
    }
    if(!found){
        hereStates.push_back(ui->comboBoxState ->currentText().toStdString());
        s+=ui->comboBoxState ->currentText() + " ";
    }
    ui->lblStates->setText(s);
}

void MainWindow::on_pushButtonRemove_clicked()
{
    QString s;
    if(hereStates.size()!=0){
        hereStates.pop_back();
    }if(hereStates.size()!=0){
        s = "States: ";
        for(int i = 0; i < hereStates.size(); i++){
            s+=QString::fromStdString(hereStates.at(i) + " ");
        }
        ui->lblStates->setText(s);
    }else{
        ui->lblStates->setText("States: None");
    }
}

void MainWindow::on_pushButtonNext_2_clicked()
{
    if(dataStrucVec2.size()>(10*(page2+1))){
        page2++;
        printTable2();
        ui->lblPage_2->setText("Page: " + QString::number(page2+1));
    }
}


void MainWindow::on_pushButtonPrev_2_clicked()
{

    if(page2-1>=0){
        page2--;
        printTable2();
        ui->lblPage_2->setText("Page: " + QString::number(page2+1));
    }
}





void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    QString s = "";
    CarInfo *v;
    if(ui->RBMin->isChecked()){
        v = dataStrucVec.at(page*10+row);

    }else{
        v = dataStrucVec.at(dataStrucVec.size()-1-row-page*10);

    }
     s+= "ImageURL: " + QString::fromStdString(v->image);
      s+= "\nCraigslist url: " + QString::fromStdString(v->url);
     s+= "\nVIN: " + QString::fromStdString(v->VIN);
    s+= "\nCar: " + QString::fromStdString(v->make);
    s+= " " + QString::fromStdString(v->model);
    s+= "\nColor: " + QString::fromStdString(v->color);
    s+= "\nYear:" + QString::number(v->year);
    s+= "\nOdometer:" + QString::number(v->miles);
    s+= "\nPrice:" + QString::number(v->price);
    s+= "\nRegion: " + QString::fromStdString(v->region) + " " + QString::fromStdString(v->state);
    s+= "\nCondition: " + QString::fromStdString(mapCondition.at(v->condition));
    s+= "\nFuel: " + QString::fromStdString(mapFuel.at(v->fuel));
    s+= "\nTitle: " + QString::fromStdString(mapTitle.at(v->titleStat));
    s+= "\nTransmission: " + QString::fromStdString(mapTransmission.at(v->transmission));
    s+= "\nDrive: " + QString::fromStdString(mapDrive.at(v->drive));
    QMessageBox msg;
        msg.setText(s);
        msg.exec();
}


void MainWindow::on_tableWidget_2_cellClicked(int row, int column)
{
    QString s = "";
    CarInfo *v;
    if(ui->RBMin->isChecked()){
        v = dataStrucVec2.at(page2*10+row);

    }else{
        v = dataStrucVec2.at(dataStrucVec2.size()-1-row-page2*10);

    }
     s+= "ImageURL: " + QString::fromStdString(v->image);
      s+= "\nCraigslist url: " + QString::fromStdString(v->url);
     s+= "\nVIN: " + QString::fromStdString(v->VIN);
    s+= "\nCar: " + QString::fromStdString(v->make);
    s+= " " + QString::fromStdString(v->model);
    s+= "\nColor: " + QString::fromStdString(v->color);
    s+= "\nYear:" + QString::number(v->year);
    s+= "\nOdometer:" + QString::number(v->miles);
    s+= "\nPrice:" + QString::number(v->price);
    s+= "\nRegion: " + QString::fromStdString(v->region) + " " + QString::fromStdString(v->state);
    s+= "\nCondition: " + QString::fromStdString(mapCondition.at(v->condition));
    s+= "\nFuel: " + QString::fromStdString(mapFuel.at(v->fuel));
    s+= "\nTitle: " + QString::fromStdString(mapTitle.at(v->titleStat));
    s+= "\nTransmission: " + QString::fromStdString(mapTransmission.at(v->transmission));
    s+= "\nDrive: " + QString::fromStdString(mapDrive.at(v->drive));
    QMessageBox msg;
        msg.setText(s);
        msg.exec();
}

