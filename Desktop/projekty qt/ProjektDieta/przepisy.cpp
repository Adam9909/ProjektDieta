#include "przepisy.h"
#include "ui_przepisy.h"
#include "mainwindow.h"

przepisy::przepisy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::przepisy)
{
    ui->setupUi(this);
}

przepisy::~przepisy()
{
    delete ui;
}

void przepisy::on_sniadaniep_clicked()
{
    connOpen();
    QSqlQuery * qry = new QSqlQuery(db);

    qry->prepare("SELECT iksde.danie, przepisy.Przepisy, skladniki.Składniki FROM iksde, laczenie, przepisy, skladniki WHERE laczenie.ID_dania = iksde.ID_dania AND laczenie.ID_przepisy = przepisy.ID_przepisy AND laczenie.ID_skladniki = skladniki.ID_skladniki");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_przepisy->setModel(modal);
    db.close();
}
//select iksde.danie, iksde.kalorie from iksde ((inner JOIN laczenie on laczenie.IDdania = iksde.ID
void przepisy::on_sniadanie2p_clicked()
{

}

void przepisy::on_obiadp_clicked()
{

}

void przepisy::on_kolacjap_clicked()
{

}
