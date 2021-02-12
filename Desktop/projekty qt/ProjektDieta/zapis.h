#ifndef ZAPIS_H
#define ZAPIS_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QString>
#include <QCompleter>
#include <QDirModel>

namespace Ui {
class zapis;
}

class zapis : public QDialog
{
    Q_OBJECT

public:
    explicit zapis(QWidget *parent = nullptr);
    ~zapis();


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
    QSqlQueryModel * modal1 = new QSqlQueryModel();
    QCompleter *ModelCompleter;

    void init();

    void ingredients(QString);

private slots:

    void on_pushButton_clicked();

    void on_pushButton_przegladarka_clicked();

private:
    Ui::zapis *ui;
};

#endif // ZAPIS_H
