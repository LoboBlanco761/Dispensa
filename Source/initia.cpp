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
#include "initia.h"
#include "ui_initia.h"
#include <QFile>
#include <QTimer>
#include "connessione.h"
#include "datiini.h"

Initia::Initia(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Initia)
{
    ui->setupUi(this);
    ui->pushButton_3->setEnabled(false);
    Initia::setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint );
    QString pb = ("QProgressBar::chunk { background-color:blue }");
    ui->progressBar->setStyleSheet(pb);
}

Initia::~Initia()
{
    delete ui;
}

void Initia::on_pushButton_2_clicked()
{
    Connessione *c = new Connessione();
    QSqlDatabase db = c->conn();
    DatiIni *d = new DatiIni();
    ef = d->creTabCat(db);
    if(ef == "y") ef = d->creTabProd(db);
    db.close();
    QString currentExecDir(QCoreApplication::applicationDirPath());
    if(ef == "y") {
        QFile file_i (currentExecDir+"/init.dat");
       // file_i.remove();
        file_i.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file_i);
        QString o = "Y";
        out<<o;
        file_i.close();
    }
    ui->pushButton_2->setEnabled(false);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Initia::updateProgress);
    timer->start(1000);
}


void Initia::on_pushButton_3_clicked()
{
    close();
}


void Initia::on_progressBar_valueChanged(int value)
{
    if (value == 100) {
        QString lab;
        if(ef == "y") {
            lab = ("color: green");
            ui->label_3->setStyleSheet(lab);
            ui->pushButton_3->setEnabled(true);
            ui->label_3->setText(tr("Successo"));
        } else {
            lab = ("color: red");
            ui->label_3->setStyleSheet(lab);
            ui->label_3->setText(tr("Fallito"));
        }
    }
}


void Initia::updateProgress()
{
    ui->progressBar->setValue(ui->progressBar->value()+10);
}

