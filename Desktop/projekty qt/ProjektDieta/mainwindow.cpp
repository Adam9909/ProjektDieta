#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initCsvFile();
    ui->lineEdit_sniadanie->setReadOnly(true);
    ui->lineEdit_sniadaniekcal->setReadOnly(true);
    ui->lineEdit_2sniadanie->setReadOnly(true);
    ui->lineEdit_sniadanie2kcal->setReadOnly(true);
    ui->lineEdit_obiad->setReadOnly(true);
    ui->lineEdit_obiadkcal->setReadOnly(true);
    ui->lineEdit_kolacja->setReadOnly(true);
    ui->lineEdit_kolacjakcal->setReadOnly(true);
    ui->lineEdit_linksniadanie->setReadOnly(true);
    ui->lineEdit_link2sniadanie->setReadOnly(true);
    ui->lineEdit_linkobiad->setReadOnly(true);
    ui->lineEdit_linkkolacja->setReadOnly(true);
    connOpen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fill(QString val)
{
    QSqlQuery qry;
    QSqlQuery qry1;
    qry.prepare("select * from iksde where danie='"+val+"'" );
    qry1.prepare("SELECT iksde.danie, iksde.kalorie, przepisy.Przepisy FROM polaczenie INNER JOIN iksde ON iksde.ID_dania = polaczenie.ID_dania INNER JOIN przepisy ON przepisy.ID_przepisy = polaczenie.ID_przepisy WHERE iksde.danie = '"+val+"'" );
    if(qry.exec(), qry1.exec())
{
       if(qry.size()==0 && qry1.size()==0){
           qDebug()<<"nie zwrócono żadnych rekordóW";
           return;
       }
       while (qry.next(), qry1.next()) // wykonuje poki nie skoncza sie rekordy
        {
            if(qry.value(3)==("sniadanie"))
            {
            ui->lineEdit_sniadanie->setText(qry.value(2).toString());
            ui->lineEdit_sniadaniekcal->setText(qry.value(1).toString() + "kcal");
            ui->lineEdit_linksniadanie->setText(qry1.value(2).toString());
           // ui->lineEdit_linksniadanie->setToolTip(qry1.value(2).toString()); // ???
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

        db.close();

    }}else{qDebug()<<"błędne zapytanie";}

    dana1 = ui->lineEdit_sniadaniekcal->text().replace("kcal","").toInt();

    dana2 = ui->lineEdit_sniadanie2kcal->text().replace("kcal","").toInt();

    dana3 = ui->lineEdit_obiadkcal->text().replace("kcal","").toInt();

    dana4 = ui->lineEdit_kolacjakcal->text().replace("kcal","").toInt();

    ui->sumakcal->display(dana1+dana2+dana3+dana4);
}

void MainWindow::initCsvFile()
{
        csv_file[0].push_back(","); // csv_file[x][y] - x- rząd y-kolumna   push back-dodanie na koniec tablicy
        csv_file[0].push_back("Poniedziałek,");
        csv_file[0].push_back("Wtorek,");
        csv_file[0].push_back("Środa,");
        csv_file[0].push_back("Czwartek,");
        csv_file[0].push_back("Piątek,");
        csv_file[0].push_back("Sobota,");
        csv_file[0].push_back("Niedziela,");

        sniadania.push_back("Śniadanie,");  // wypełniamy rząd przecinkami, potem go wypełniamy, tworzymy nowe rzędy
        for(int i = 1; i < 8; ++i)
        {
            sniadania.push_back(",");
        }
        csv_file.push_back(sniadania);

        sniadania2.push_back("Śniadanie2,");
        for(int i = 1; i < 8; ++i)
        {
            sniadania2.push_back(",");
        }
        csv_file.push_back(sniadania2);

        obiad.push_back("Obiad,");
        for(int i = 1; i < 8; ++i)
        {
            obiad.push_back(",");
        }
        csv_file.push_back(obiad);

        kolacja.push_back("Kolacja,");
        for(int i = 1; i < 8; ++i)
        {
            kolacja.push_back(",");
        }
        csv_file.push_back(kolacja);
}

void MainWindow::on_sniadanie_clicked()
{
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("select danie, kalorie from iksde where typ='sniadanie'");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    db.close();
}

void MainWindow::on_sniadanie2_clicked()
{
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("select danie, kalorie from iksde where typ='sniadanie2'");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    db.close();
}

void MainWindow::on_obiad_clicked()
{
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("select danie, kalorie from iksde where typ='obiad'");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    db.close();
}

void MainWindow::on_kolacja_clicked()
{
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("select danie, kalorie from iksde where typ='kolacja'");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    db.close();
}

void MainWindow::on_tableView_activated(const QModelIndex &index) // przejmuje indeks po kliknieciu na kwadracik
{
    QString val = ui->tableView->model()->data(index).toString();  // wyciaga dane pod indeksem do stringa
    fill(val);
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
}

void MainWindow::on_dodawanie_clicked()
{
    int a;
    dodawanie pd(this);
    a = pd.exec();
}

void MainWindow::on_actionzapisz_triggered()
{
    auto filename = QFileDialog::getSaveFileName(this, "zapisz", QDir::rootPath(), "CSV File (*.csv)");   // auto-automatycznie dobierany typ, zwraca scieszke do którego wybrałem
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) //tylko do zapisu i jako tekst
    {
    QTextStream xout(&file);

    for(int i = 0; i < csv_file.size(); ++i) // do ilosci rzędów
    {
        for(int j = 0; j < csv_file[i].size(); ++j) // ilość kolumn w rzędzie [i]
        {
            xout << csv_file[i][j];
        }
        xout << "\n";
    }
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

void MainWindow::on_zapiszdzien_clicked()
{
    int dzien = ui->comboBox->currentIndex()+1;  // bez jedynki poniedziałek bedzie na A2
    csv_file[1][dzien] = (ui->lineEdit_sniadanie->text() !="")?ui->lineEdit_sniadanie->text() + "," : ",";   //(stat)?true:false;
//    if(ui->lineEdit_sniadanie->text() != "")
//    {
//        csv_file[1][dzien] = ui->lineEdit_sniadanie->text() + ",";
//    }
//    else
//    {
//        csv_file[1][dzien] = ",";
//    }
    csv_file[2][dzien] = (ui->lineEdit_2sniadanie->text() != "")?ui->lineEdit_2sniadanie->text() + "," : ",";
    csv_file[3][dzien] = (ui->lineEdit_obiad->text() != "")?ui->lineEdit_obiad->text() + "," : ",";
    csv_file[4][dzien] = (ui->lineEdit_kolacja->text() != "")?ui->lineEdit_kolacja->text() + "," : ",";
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(csv_file[1][index+1]==","){ // jesli puste uzupełnij pustymi
        ui->lineEdit_sniadanie->setText("");
        ui->lineEdit_sniadaniekcal->setText("");
        ui->lineEdit_linksniadanie->setText("");
    }else {
        fill( csv_file[1][index+1].replace(",","") ); // jesli nie puste pobierz z bazy
    }
    if(csv_file[2][index+1]==","){
        ui->lineEdit_2sniadanie->setText("");
        ui->lineEdit_sniadanie2kcal->setText("");
        ui->lineEdit_link2sniadanie->setText("");
    }else {
        fill( csv_file[2][index+1].replace(",","") );
    }
    if(csv_file[3][index+1]==","){
        ui->lineEdit_obiad->setText("");
        ui->lineEdit_obiadkcal->setText("");
        ui->lineEdit_linkobiad->setText("");
    }else {
        fill( csv_file[3][index+1].replace(",","") );
    }
    if(csv_file[4][index+1]==","){
        ui->lineEdit_kolacja->setText("");
        ui->lineEdit_kolacjakcal->setText("");
        ui->lineEdit_linkkolacja->setText("");
    }else {
        fill( csv_file[4][index+1].replace(",","") );
    }
}
