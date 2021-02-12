#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QString>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QLineEdit>
#include <QTableView>
#include <QDebug>
#include <QChar>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QLCDNumber>
#include <QMessageBox>
#include "zapis.h"
#include "dodawanie.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QSqlDatabase db;

    bool connOpen(){
        QSqlDatabase db= QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("127.0.0.1");
        db.setUserName("root");
        db.setPassword("");
        db.setDatabaseName("projekt2");
        if(!db.open())
        {
          qDebug()<<"Nie mozna otworzyc bazy";
          return false;
        }
        else {qDebug()<<"polaczono z baza"; return true;}
    }

    QSqlQueryModel * modal = new QSqlQueryModel();
    //QSqlQueryModel * modal1 = new QSqlQueryModel();

    QString waga1;
    QString waga2;

    QTableWidget *tablewidget= new QTableWidget(this);

    int dana1;
    int dana2;
    int dana3;
    int dana4;
    int suma;

    QString w;
    QString x;
    QString y;
    QString z;

    QVector< QVector<QString> > csv_file = QVector <QVector<QString> > (1); // tablica dwuwymiarowa rozmiar 1, jest fajniejszy
    QVector<QString>sniadania;
    QVector<QString>sniadania2;
    QVector<QString>obiad;
    QVector<QString>kolacja;

    void fill (QString); //wypełnienie pól dań

     void initCsvFile(); // inicjalizacja tablicy

private slots:
    void on_sniadanie_clicked();

    void on_sniadanie2_clicked();

    void on_obiad_clicked();

    void on_kolacja_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_zatwierdz_clicked();

    void on_dodawanie_clicked();

    void on_actionzapisz_triggered();

    void on_actiono_daniach_triggered();

    void on_zapiszdzien_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
