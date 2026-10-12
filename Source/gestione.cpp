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
#include "gestione.h"
#include "ui_gestione.h"
#include "connessione.h"
#include "dati.h"
#include "messaggi.h"
#include "movimenta.h"

Gestione::Gestione(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Gestione)
{
    ui->setupUi(this);
    caricaCombo();
    ui->pushButton_3->setEnabled(false);
}

Gestione::~Gestione()
{
    delete ui;
}

void Gestione::on_pushButton_2_clicked()
{
    ui->listWidget->clear();
    cat = ui->comboBox->currentText();
    Connessione *c = new Connessione();
    QSqlDatabase db = c->conn();
    Dati *d = new Dati();
    QStringList matrice = d->selezCat(db,cat);
    ui->label_3->setText(tr("Categoria : ")+cat);
    if(matrice.isEmpty()) {
        Messaggi *m = new Messaggi();
        QString fl = "a";
        QString stringa = (tr("Non sono presenti Prodotti nella Categoria selezionata"));
        m->messaggio(fl,stringa);
    } else {
        ui->pushButton_3->setEnabled(true);
        for(int i = 0;i<matrice.size();i++) {
            QListWidgetItem *item = new QListWidgetItem(matrice[i], ui->listWidget);
            ui->listWidget->insertItem(i, item);
        }
    }
    db.close();
}


void Gestione::on_pushButton_3_clicked()
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
        QString stringa = (tr("Nessuna Selezione"));
        m->messaggio(fl,stringa);
    } else {
        QString param = (cat+" - "+name_sel);
        Movimenta *mo = new Movimenta();
        mo->setAttribute(Qt::WA_DeleteOnClose);
        mo->settaPannello(param);
        mo->exec();
    }
}


void Gestione::on_pushButton_4_clicked()
{
    close();
}


void Gestione::caricaCombo()
{
    Connessione *c = new Connessione();
    QSqlDatabase db = c->conn();
    Dati *d = new Dati();
    QStringList matrice = d->preCarCat(db);
    for(int i = 0;i<matrice.size();i++) {
        QString dato = matrice[i];
        ui->comboBox->addItem(dato);
    }
    db.close();
}

