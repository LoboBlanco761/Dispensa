/* Copyright 2026 LoboBlanco761<waltgiri@proton.me>
 * This file is part of Dispensa.

    Dispensa is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Dispensa is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Dispensa.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "prodotti.h"
#include "visualizza.h"
#include "gestione.h"
#include <QFile>
#include "situazdisp.h"
#include "about.h"
#include "listaspesa.h"
#include "tools.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    settaImg();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::settaImg()
{
    QString currentExecDir(QCoreApplication::applicationDirPath());
    ui->label_2->setPixmap(QPixmap(":/Immagini/Dispensa256.png"));
}


void MainWindow::on_action_EliminaCategoria_triggered()
{
    QString param = (tr("Elimina Categoria"));
    Tools *t = new Tools();
    t->setAttribute(Qt::WA_DeleteOnClose);
    t->settaPannello(param);
    t->exec();
}


void MainWindow::on_pushButton_clicked()
{
    Prodotti *p = new Prodotti();
    p->setAttribute(Qt::WA_DeleteOnClose);
    p->exec();
}


void MainWindow::on_pushButton_2_clicked()
{
    Visualizza *v = new Visualizza();
    v->setAttribute(Qt::WA_DeleteOnClose);
    v->exec();
}


void MainWindow::on_pushButton_3_clicked()
{
    Gestione *g = new Gestione();
    g->setAttribute(Qt::WA_DeleteOnClose);
    g->exec();
}


void MainWindow::on_action_Stato_Dispensa_triggered()
{
    SituazDisp *sd = new SituazDisp();
    sd->setAttribute(Qt::WA_DeleteOnClose);
    sd->exec();
}


void MainWindow::on_action_Esci_triggered()
{
    QApplication::quit();
}


void MainWindow::on_action_About_triggered()
{
    About *a = new About();
    a->setAttribute(Qt::WA_DeleteOnClose);
    a->exec();
}


void MainWindow::on_action_ListaSpesa_triggered()
{
    ListaSpesa *ls = new ListaSpesa();
    ls->setAttribute(Qt::WA_DeleteOnClose);
    ls->exec();
}



void MainWindow::on_action_ModificaCategoria_triggered()
{
    QString param = (tr("Modifica Categoria"));
    Tools *t = new Tools();
    t->setAttribute(Qt::WA_DeleteOnClose);
    t->settaPannello(param);
    t->exec();
}


void MainWindow::on_action_EliminaProdotto_triggered()
{
    QString param = (tr("Elimina Prodotto"));
    Tools *t = new Tools();
    t->setAttribute(Qt::WA_DeleteOnClose);
    t->settaPannello(param);
    t->exec();
}


void MainWindow::on_action_ModificaProdotto_triggered()
{
    QString param = (tr("Modifica Prodotto"));
    Tools *t = new Tools();
    t->setAttribute(Qt::WA_DeleteOnClose);
    t->settaPannello(param);
    t->exec();
}

