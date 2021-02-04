#include "zapis.h"
#include "ui_zapis.h"
#include "mainwindow.h"
#include "klasa.h"
#include <QComboBox>
#include <QCompleter>
#include <QDirModel>

zapis::zapis(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::zapis)
{
    ui->setupUi(this);

    connOpen();
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("select danie from iksde");
    qry->exec();
    modal->setQuery(*qry);
    ModelCompleter = new QCompleter (this);
    ModelCompleter->setModel(modal);
    ui->lineEdit_danie->setCompleter(ModelCompleter);
    db.close();
}

zapis::~zapis()
{
    delete ui;
}

void zapis::on_pushButton_clicked()
{
    connOpen();
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("SELECT iksde.danie, przepisy.Przepisy FROM laczenie INNER JOIN iksde ON iksde.ID_dania = laczenie.ID_dania INNER JOIN przepisy ON przepisy.ID_przepisy = laczenie.ID_przepisy WHERE iksde.danie = :danie" );
    qry->bindValue(":danie", ui->lineEdit_danie->text());
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_3->setModel(modal);
    ui->tableView_3->resizeColumnsToContents();
    db.close();

}
