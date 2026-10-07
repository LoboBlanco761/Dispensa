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
#include "visualelenco.h"
#include "ui_visualelenco.h"
#include "connessione.h"
#include "dati.h"
#include "messaggi.h"

VisualElenco::VisualElenco(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VisualElenco)
{
    ui->setupUi(this);
}

VisualElenco::~VisualElenco()
{
    delete ui;
}


void VisualElenco::settaPannello(QString param)
{
    Connessione *c = new Connessione();
    QSqlDatabase db = c->conn();
    Dati *d = new Dati();
    if(param == "tutto") {
        ui->label->setText("Elenco Generale");
        ui->label_2->setVisible(false);
        ui->label_3->setVisible(false);
        ui->line_2->setVisible(false);
        ui->comboBox->setVisible(false);
        ui->pushButton_2->setVisible(false);
        QStringList matrice = d->selezGen(db);
        if(matrice.isEmpty()) {
            Messaggi *m = new Messaggi();
            QString fl = "a";
            QString stringa = "Non sono presenti Prodotti";
            m->messaggio(fl,stringa);
        } else {
            QString elenco = matrice.join("\n");
            ui->textBrowser->setPlainText(elenco);
        }
    } else {
        ui->label->setText("Elenco Categoria");
        QStringList matrice = d->preCarCat(db);
        caricaCombo(matrice);
        ui->textBrowser->setVisible(false);
    }
    db.close();
}


void VisualElenco::caricaCombo(QStringList matrice)
{
    for(int i = 0;i<matrice.size();i++) {
        QString dato = matrice[i];
        ui->comboBox->addItem(dato);
    }
}

void VisualElenco::on_pushButton_3_clicked()
{
    close();
}


void VisualElenco::on_pushButton_2_clicked()
{
    QString categoria = ui->comboBox->currentText();
    ui->label_3->setText("Categoria : "+categoria);
    ui->textBrowser->setVisible(true);
    Connessione *c = new Connessione();
    QSqlDatabase db = c->conn();
    Dati *d = new Dati();
    QStringList matrice = d->selezCat(db,categoria);
    if(matrice.isEmpty()) {
        Messaggi *m = new Messaggi();
        QString fl = "a";
        QString stringa = "Non sono presenti Prodotti in questa categoria";
        m->messaggio(fl,stringa);
    } else {
        QString elenco = matrice.join("\n");
        ui->textBrowser->setPlainText(elenco);
    }
    db.close();
}

