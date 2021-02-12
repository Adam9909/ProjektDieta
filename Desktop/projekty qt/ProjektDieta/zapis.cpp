#include "zapis.h"
#include "ui_zapis.h"
#include "mainwindow.h"
#include "klasa.h"
#include <QComboBox>
#include <QCompleter>
#include <QDirModel>
#include <QDesktopServices>
#include <QUrl>


zapis::zapis(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::zapis)
{
    ui->setupUi(this);

    //connOpen();

    init();
}

zapis::~zapis()
{
    delete ui;
}

void zapis::init()
{
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("select danie from iksde");
    qry->exec();
    modal->setQuery(*qry);

    ModelCompleter = new QCompleter (this);
    ModelCompleter->setModel(modal);
    ModelCompleter->setCaseSensitivity(Qt::CaseInsensitive); // czułość na wielkość liter
    ModelCompleter->setCompletionMode(QCompleter::PopupCompletion); // typ podpowiadania
    ui->lineEdit_danie->setCompleter(ModelCompleter);

    db.close();
}

void zapis::ingredients(QString val)
{
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("SELECT skladniki.Składniki, skladnikidaniarelacje.ilosc \
                 FROM skladnikidaniarelacje \
                 INNER JOIN iksde ON iksde.ID_dania = skladnikidaniarelacje.daniaID \
                 INNER JOIN skladniki ON skladniki.ID_skladniki = skladnikidaniarelacje.skladnikiID \
                 WHERE iksde.danie = :danie" );
    qry->bindValue(":danie", ui->lineEdit_danie->text());
    qry->exec();

    while (qry->next())
    {
        ui->textEdit->append(qry->value(0).toString() + "\t" + qry->value(1).toString());   // \t - tabulacja,  append - rozszerza o skladniki (dodaje do tego co juz jest)
    }
    db.close();

}

void zapis::on_pushButton_clicked()
{
   // connOpen();
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("SELECT iksde.danie, przepisy.Przepisy FROM polaczenie INNER JOIN iksde ON iksde.ID_dania = polaczenie.ID_dania INNER JOIN przepisy ON przepisy.ID_przepisy = polaczenie.ID_przepisy WHERE iksde.danie = :danie" );
    qry->bindValue(":danie", ui->lineEdit_danie->text());
    qry->exec();
    qry->next();
    QString link = qry->value(1).toString();
    ui->lineEdit_link->setText(link);
    db.close();
    init();
    ingredients(ui->lineEdit_danie->text());

}

void zapis::on_pushButton_przegladarka_clicked()
{
    QString val = ui->lineEdit_link->text();
    QDesktopServices::openUrl(QUrl(val));
}
