#include "dodawanie.h"
#include "ui_dodawanie.h"
#include <QSqlQuery>
#include "mainwindow.h"
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include "ui_mainwindow.h"

dodawanie::dodawanie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dodawanie)
{
    ui->setupUi(this);
}

dodawanie::~dodawanie()
{
    delete ui;
}

void dodawanie::on_zatwierdz_clicked()
{
    connOpen();
    QSqlQuery* qry = new QSqlQuery(db);
    qry->prepare("INSERT INTO iksde (typ, danie, kalorie) " "VALUES (:typ, :danie, :kalorie)");
    qry->bindValue(":typ", ui->comboBox_typdania->currentText());
    qry->bindValue(":danie", ui->lineEdit_wybordania->text());
    qry->bindValue(":kalorie", ui->spinBox_kcaldania->text());
    qry->exec();
    db.close();
}
