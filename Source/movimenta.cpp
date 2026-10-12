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
#include "movimenta.h"
#include "ui_movimenta.h"
#include "controlli.h"
#include "connessione.h"
#include "dati.h"
#include "messaggi.h"

Movimenta::Movimenta(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Movimenta)
{
    ui->setupUi(this);
}

Movimenta::~Movimenta()
{
    delete ui;
}

void Movimenta::on_pushButton_2_clicked()
{
    QString qtasPrel = ui->lineEdit_2->text();
    QString qtasDep = ui->lineEdit_3->text();
    QString qtas = ui->label_5->text();
    int qta = qtas.toInt();
    QString ids = ui->label_6->text();
    int id = ids.toInt();
    QString ef = "y";
    QString ec = "y";
    Controlli *co = new Controlli();
    ef = co->contrMov(qtasPrel,qtasDep);
    if(ef == "y") {
        if(!qtasPrel.isEmpty()) {
            int qtaPrel = qtasPrel.toInt();
            ef = co->contrMovLog(qta,qtaPrel);
        }
    }
    if(ef == "y") ec = "n";
    if(ef == "y") {
        Connessione *c = new Connessione();
        QSqlDatabase db = c->conn();
        Dati *d = new Dati();
        if(!qtasPrel.isEmpty()) {
            QString tipo = "prel";
            int qtaPrel = qtasPrel.toInt();
            ef = d->updProd(db,qta,qtaPrel,tipo,id);
        }
        if(!qtasDep.isEmpty()) {
            QString tipo = "dep";
            int qtaDep = qtasDep.toInt();
            ef = d->updProd(db,qta,qtaDep,tipo,id);
        }
        delete(d);
        db.close();
        Messaggi *m = new Messaggi();
        QString fl;
        QString stringa;
        if(ef == "y") {
            fl = "s";
            stringa = (tr("Movimentazione Dispensa avvenuta con Successo"));
            m->messaggio(fl,stringa);
        } else {
            fl = "e";
            stringa = (tr("Movimentazione Dispensa Fallita"));
            m->messaggio(fl,stringa);
        }
    }
    if(ec == "n") close();
}


void Movimenta::on_pushButton_3_clicked()
{
    close();
}


void Movimenta::settaPannello(QString param)
{
    QStringList listp = param.split(" - ");
    QString cat = listp[0];
    QString prod = listp[1];
    QString qtas = listp[2];
    ui->label_2->setText(cat+" : "+prod+(tr("  Quantità : "))+qtas);
    ui->label_5->setText(qtas);
    Connessione *c = new Connessione();
    QSqlDatabase db = c->conn();
    Dati *d = new Dati();
    int id = d->cercaId(db,cat,prod,qtas);
    QString ids = QString::number(id);
    ui->label_6->setText(ids);
    db.close();
}

