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
#include "toolsmod.h"
#include "ui_toolsmod.h"
#include "controlli.h"
#include "connessione.h"
#include "dati.h"

ToolsMod::ToolsMod(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ToolsMod)
{
    ui->setupUi(this);
}

ToolsMod::~ToolsMod()
{
    delete ui;
}


void ToolsMod::settaPannello(QString param,QString cat,QString prod)
{
    ui->label->setText(param);
    if(param == (tr("Modifica Categoria"))) {
        ui->label_2->setText(tr("Categoria : ")+cat+(tr(" - Inserisci Modifica :")));
        ui->label_3->setVisible(false);
        ui->lineEdit_3->setVisible(false);
    } else {
        ui->label_2->setText(tr("Categoria : ")+cat+(tr(" - Inserisci Modifica :")));
        ui->label_3->setText(tr("Prodotto : ")+prod+(tr(" - Inserisci Modifica :")));
    }
}

void ToolsMod::on_pushButton_2_clicked()
{
    param = ui->label->text();
    QString ef = "y";
    QString categoria = ui->lineEdit_2->text();
    QString prodotto;
    if(param == (tr("Modifica Prodotto"))) {
        prodotto = ui->lineEdit_3->text();
    }
    Controlli *co = new Controlli();
    if(param == (tr("Modifica Categoria"))) {
        ef = co->contrCat(categoria);
    } else {
        ef = co->contrModProd(categoria,prodotto);
    }
    if(ef == "y") {
        Connessione *c = new Connessione();
        QSqlDatabase db = c->conn();
        Dati *d = new Dati();
        ef = d->creTabTemp(db);
        if(ef == "y") {
            ef = d->insTabTemp(db,categoria,prodotto);
        }
        //db.close();
    }
    if(ef == "y") close();
}


void ToolsMod::on_pushButton_3_clicked()
{
    close();
}

