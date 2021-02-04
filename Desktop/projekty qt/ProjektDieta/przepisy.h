#ifndef PRZEPISY_H
#define PRZEPISY_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QString>
#include "mainwindow.h"

namespace Ui {
class przepisy;
}

class przepisy : public QDialog
{
    Q_OBJECT

public:
    explicit przepisy(QWidget *parent = nullptr);
    ~przepisy();

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

    QSqlQueryModel * modal = new QSqlQueryModel();


private slots:
    void on_sniadaniep_clicked();

    void on_sniadanie2p_clicked();

    void on_obiadp_clicked();

    void on_kolacjap_clicked();

private:
    Ui::przepisy *ui;
};

#endif // PRZEPISY_H
