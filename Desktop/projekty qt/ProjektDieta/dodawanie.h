#ifndef DODAWANIE_H
#define DODAWANIE_H

#include <QDialog>
#include "mainwindow.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QString>

namespace Ui {
class dodawanie;
}

class dodawanie : public QDialog
{
    Q_OBJECT

public:
    explicit dodawanie(QWidget *parent = nullptr);
    ~dodawanie();

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

    QSqlDatabase db;


private slots:
    void on_zatwierdz_clicked();

private:
    Ui::dodawanie *ui;
};

#endif // DODAWANIE_H
