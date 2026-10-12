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
#include "prodotti.h"
#include "ui_prodotti.h"
#include "controlli.h"
#include "connessione.h"
#include "dati.h"
#include "messaggi.h"

Prodotti::Prodotti(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Prodotti)
{
    ui->setupUi(this);
    ui->lineEdit_2->setFocus();
}

Prodotti::~Prodotti()
{
    delete ui;
}

void Prodotti::on_pushButton_2_clicked()
{
    QString ef = "y";
    QString ec = "y";
    QString cat = ui->lineEdit_2->text();
    QString prod = ui->lineEdit->text();
    QString qtas = ui->lineEdit_3->text();
    Controlli *cr = new Controlli();
    ef = cr->contrCat(cat);
    if(ef == "y") ef = cr->contrProd(prod);
    if(ef == "y") ef = cr->contrQta(qtas);
    if(ef == "y") ec = "n";
    if(ef == "y") {
        Connessione *c = new Connessione();
        QSqlDatabase db = c->conn();
        Dati *d = new Dati();
        ef = d->insProd(db,cat,prod,qtas);
        Messaggi *m = new Messaggi();
        QString fl;
        QString stringa;
        if(ef == "y") {
            fl = "s";
            stringa = (tr("Inserimento prodotto avvenuto con successo"));
            m->messaggio(fl,stringa);
        } else {
            fl = "e";
            stringa = (tr("Inserimento prodotto fallito"));
            m->messaggio(fl,stringa);
        }
        db.close();
    }
    if(ec == "n") close();
}


void Prodotti::on_pushButton_3_clicked()
{
    close();
}


