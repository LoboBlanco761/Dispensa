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
#include "tools.h"
#include "ui_tools.h"
#include "connessione.h"
#include "dati.h"
#include "messaggi.h"
#include "toolsmod.h"

Tools::Tools(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Tools)
{
    ui->setupUi(this);
}

Tools::~Tools()
{
    delete ui;
}


void Tools::settaPannello(QString param)
{
    ui->label->setText(param);
    Connessione *c = new Connessione();
    QSqlDatabase db = c->conn();
    Dati *d = new Dati();
    QStringList matrice;
    if((param == "Elimina Categoria") || (param == "Modifica Categoria")) {
        ui->label_2->setText("Seleziona Categoria");
        matrice = d->listaCat(db);
    }
    if((param == "Elimina Prodotto") || (param == "Modifica Prodotto")) {
        ui->label_2->setText("Seleziona Prodotto");
        matrice = d->listaProd(db);
    }
    if((param == "Elimina Categoria") || (param == "Elimina Prodotto"))
        ui->pushButton_2->setText("Elimina");
    if((param == "Modifica Categoria") || (param == "Modifica Prodotto"))
        ui->pushButton_2->setText("Modifica");
    caricaLista(matrice);
    delete(d);
    db.close();
}


void Tools::caricaLista(QStringList matrice)
{
    if(matrice.isEmpty()) {
        Messaggi *m = new Messaggi();
        QString fl = "a";
        QString stringa = "Nessun risultato";
        m->messaggio(fl,stringa);
        ui->pushButton_2->setEnabled(false);
    } else {
        for(int i = 0;i<matrice.size();i++) {
            QListWidgetItem *item = new QListWidgetItem(matrice[i], ui->listWidget);
            ui->listWidget->insertItem(i, item);
        }
    }
}

void Tools::on_pushButton_2_clicked()
{
    QString name_sel;
    for(int i = 0;i<50;i++) {
        if(!ui->listWidget->item(i)) {
            break;
        } else {
            if(ui->listWidget->item(i)->isSelected()) {
                name_sel = ui->listWidget->item(i)->text();
                break;
            }
        }
    }
    if (name_sel.isEmpty()) {
        Messaggi *m = new Messaggi();
        QString fl = "a";
        QString stringa = "Nessuna Selezione";
        m->messaggio(fl,stringa);
    } else {
        param = ui->label->text();
        Connessione *c = new Connessione();
        QSqlDatabase db = c->conn();
        QStringList listt = name_sel.split(" - ");
        QString ids = listt[0];
        QString cat = listt[1];
        QString prod;
        if(param == "Modifica Prodotto")
            prod = listt[2];
        int id = ids.toInt();
        Dati *d = new Dati();
        QString ef = "y";
        QString ec = "y";
        QString stringa;
        if(param == "Elimina Categoria"){
            ef = d->cancCat(db,id);
            if(ef == "y") {
                stringa = "Eliminazione Categoria avvenuta con Successo";
            } else {
                stringa = "Eliminazione Categoria Fallita";
            }
        }
        if(param == "Modifica Categoria") {
            ToolsMod *tm = new ToolsMod();
            tm->setAttribute(Qt::WA_DeleteOnClose);
            QString prod = "";
            tm->settaPannello(param,cat,prod);
            tm->exec();
            ef = d->testTemp(db);
            if(ef == "n") ec = "n";
            if(ef == "y") {
                QStringList mat = d->leggiTemp(db);
                QStringList listc = mat[0].split(" - ");
                cat = listc[1];
                ef = d->modCat(db,id,cat);
            }
            if(ef == "y") {
                stringa = "Modifica Categoria avvenuta con Successo";
            } else {
                stringa = "Modifica Categoria Fallita";
            }
        }
        if(param == "Elimina Prodotto") {
            ef = d->cancProd(db,id);
            if(ef == "y") {
                stringa = "Eliminazione Prodotto avvenuta con Successo";
            } else {
                stringa = "Eliminazione Prodotto Fallita";
            }
        }
        if(param == "Modifica Prodotto") {
            ToolsMod *tm = new ToolsMod();
            tm->setAttribute(Qt::WA_DeleteOnClose);
            tm->settaPannello(param,cat,prod);
            tm->exec();
            ef = d->testTemp(db);
            if(ef == "n") ec = "n";
            if(ef == "y") {
                QStringList mat = d->leggiTemp(db);
                QStringList listc = mat[0].split(" - ");
                cat = listc[1];
                prod = listc[0];
                ef = d->modProd(db,id,cat,prod);
            }
            if(ef == "y") {
                stringa = "Modifica Prodotto avvenuta con Successo";
            } else {
                stringa = "Modifica Prodotto Fallita";
            }
        }
        d->cancTemp(db);
        db.close();
        Messaggi *m = new Messaggi();
        QString fl;
        if(ec == "y") {
            if(ef == "y") {
                fl = "s";
                m->messaggio(fl,stringa);
            } else {
                fl = "e";
                m->messaggio(fl,stringa);
            }
        }
        delete(m);
        if(ec == "y") close();
    }
}


void Tools::on_pushButton_3_clicked()
{
    close();
}

