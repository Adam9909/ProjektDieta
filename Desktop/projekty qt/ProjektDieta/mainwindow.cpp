#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QTableView>
#include <QDebug>
#include <QSqlQueryModel>
#include <QChar>
#include "dodawanie.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include "zapis.h"
#include <QLCDNumber>
#include "przepisy.h"
#include <QMessageBox>
#include "klasa.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_sniadanie_clicked()
{
    connOpen();
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("select danie, kalorie from iksde where typ='sniadanie'");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
}

void MainWindow::on_sniadanie2_clicked()
{
    connOpen();
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("select danie, kalorie from iksde where typ='sniadanie2'");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    db.close();
}

void MainWindow::on_obiad_clicked()
{
    connOpen();
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("select danie, kalorie from iksde where typ='obiad'");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    db.close();
}

void MainWindow::on_kolacja_clicked()
{
    connOpen();
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("select danie, kalorie from iksde where typ='kolacja'");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    db.close();
}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    QString val = ui->tableView->model()->data(index).toString();
    connOpen();
    QSqlQuery qry;
    QSqlQuery qry1;
    qry.prepare("select * from iksde where danie='"+val+"' or kalorie='"+val+"'" );
    qry1.prepare("SELECT iksde.danie, iksde.kalorie, przepisy.Przepisy FROM laczenie INNER JOIN iksde ON iksde.ID_dania = laczenie.ID_dania INNER JOIN przepisy ON przepisy.ID_przepisy = laczenie.ID_przepisy WHERE iksde.danie = '"+val+"'" );
    if(qry.exec(), qry1.exec())
{
       while (qry.next(), qry1.next())
        {
            if(qry.value(3)==("sniadanie"))
            {
            ui->lineEdit_sniadanie->setText(qry.value(2).toString());
            ui->lineEdit_sniadaniekcal->setText(qry.value(1).toString() + "kcal");
            ui->lineEdit_linksniadanie->setText(qry1.value(2).toString());
            } else if (qry.value(3)==("sniadanie2"))
            {
            ui->lineEdit_2sniadanie->setText(qry.value(2).toString());
            ui->lineEdit_sniadanie2kcal->setText(qry.value(1).toString() + "kcal");
            ui->lineEdit_link2sniadanie->setText(qry1.value(2).toString());
            } else if (qry.value(3)==("obiad"))
            {
            ui->lineEdit_obiad->setText(qry.value(2).toString());
            ui->lineEdit_obiadkcal->setText(qry.value(1).toString() + "kcal");
            ui->lineEdit_linkobiad->setText(qry1.value(2).toString());
            } else if (qry.value(3)==("kolacja"))
            {
            ui->lineEdit_kolacja->setText(qry.value(2).toString());
            ui->lineEdit_kolacjakcal->setText(qry.value(1).toString() + "kcal");
            ui->lineEdit_linkkolacja->setText(qry1.value(2).toString());
            }

            if(qry.value(3)==("sniadanie"))
            {
            dana1 = qry.value(1).toInt();
            ui->sumakcal->display(dana1);
            } else if (qry.value(3)==("sniadanie2"))
            {
            dana2 = qry.value(1).toInt();
            ui->sumakcal->display(dana1+dana2);
            } else if (qry.value(3)==("obiad"))
            {
            dana3 = qry.value(1).toInt();
            } else if (qry.value(3)==("kolacja"))
            {
            dana4 = qry.value(1).toInt();
            }
            ui->sumakcal->display(dana1+dana2+dana3+dana4);

        db.close();

}}
}

void MainWindow::on_zatwierdz_clicked()
{
    waga1 = ui->wagaaktualna->text();
    waga2 = ui->wagawymarzona->text();
    int waga1int = waga1.toInt();
    int waga2int = waga2.toInt();
    if(waga1int < waga2int){
        ui->sniadanie2->setEnabled(true);
    }else if(waga1int > waga2int){
        ui->sniadanie2->setEnabled(false);
    }
    qDebug()<<waga1;
}



void MainWindow::on_dodawanie_clicked()
{
    int a;
    dodawanie pd(this);
    a = pd.exec();
}

void MainWindow::on_actionzapisz_triggered()
{
    suma = dana1+dana2+dana3+dana4;

    auto filename = QFileDialog::getSaveFileName(this, "zapisz", QDir::rootPath(), "txt File (*.txt)");
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)){

    QTextStream xout(&file);

    xout << "Sniadanie:"<<"\n";
    xout << ui->lineEdit_sniadanie->text()<<", ";
    xout << ui->lineEdit_sniadaniekcal->text() <<"\n";
    xout << "Link do przepisu: " << ui->lineEdit_linksniadanie->text() << "\n";
    xout << " --------------"<<"\n";
    xout << "Sniadanie2:"<<"\n";
    xout << ui->lineEdit_2sniadanie->text()<<", ";
    xout << ui->lineEdit_sniadanie2kcal->text() <<"\n";
    xout << "Link do przepisu: " << ui->lineEdit_link2sniadanie->text() << "\n\n";
    xout << "Obiad:"<<"\n";
    xout << ui->lineEdit_obiad->text()<<", ";
    xout << ui->lineEdit_obiadkcal->text() <<"\n";
    xout << "Link do przepisu: " << ui->lineEdit_linkobiad->text() << "\n\n";
    xout << "Kolacja:"<<"\n";
    xout << ui->lineEdit_kolacja->text()<<", ";
    xout << ui->lineEdit_kolacjakcal->text() <<"\n";
    xout << "Link do przepisu: " << ui->lineEdit_linkkolacja->text() << "\n\n";
    xout << "SUMA KCAL:" << suma;
    xout.flush();
    file.close();
    qDebug()<<"zapisano";
}}

void MainWindow::on_actiono_daniach_triggered()
{
    int a;
    zapis pd(this);
    a = pd.exec();
}
