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
#include "situazdisp.h"
#include "ui_situazdisp.h"
#include "connessione.h"
#include "dati.h"
#include "messaggi.h"

SituazDisp::SituazDisp(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SituazDisp)
{
    ui->setupUi(this);
    settaPannello();
}

SituazDisp::~SituazDisp()
{
    delete ui;
}


void SituazDisp::settaPannello()
{
    QList<QString> nomeCategoria;
    QList<QString> nomeProdotto;
    QList<QString> datoQuantità;
    Connessione *c = new Connessione();
    QSqlDatabase db = c->conn();
    Dati *d = new Dati();
    QStringList matrice = d->selezGen(db);
    if(matrice.isEmpty()) {
        Messaggi *m = new Messaggi();
        QString fl = "a";
        QString stringa = (tr("Non sono presenti prodotti in Dispensa"));
        m->messaggio(fl,stringa);
    } else {
        for(int i = 0;i<matrice.size();i++) {
            QStringList lista = matrice[i].split(" - ");
            QString cat = lista[0];
            QString prod = lista[1];
            QString qtas = lista[2];
            nomeCategoria.append(cat);
            nomeProdotto.append(prod);
            datoQuantità.append(qtas);
        }
        TestModel *Dispensa = new TestModel(this);
        Dispensa->populateData(nomeCategoria,nomeProdotto,datoQuantità);
        ui->tableView->setModel(Dispensa);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->horizontalHeader()->setVisible(true);
        ui->tableView->show();
    }
    db.close();
}

TestModel::TestModel(QObject *parent) : QAbstractTableModel(parent)
{
}

void TestModel::populateData(const QList<QString> &nomeCategoria,const QList<QString> &nomeProdotto,
                            const QList<QString> &datoQuantità)
{
    tm_nome_categoria.clear();
    tm_nome_categoria = nomeCategoria;
    tm_nome_prodotto.clear();
    tm_nome_prodotto = nomeProdotto;
    tm_dato_quantità.clear();
    tm_dato_quantità = datoQuantità;
    return;
}

int TestModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return tm_nome_categoria.length();
}

int TestModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}

QVariant TestModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }
    if (index.column() == 0) {
        return tm_nome_categoria[index.row()];
    } else if (index.column() == 1) {
        return tm_nome_prodotto[index.row()];
    } else if (index.column() == 2) {
        return tm_dato_quantità[index.row()];
    }
    return QVariant();
}

QVariant TestModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section == 0) {
            return QString(tr("Categoria"));
        } else if (section == 1) {
            return QString(tr("Prodotto"));
        } else if (section == 2) {
            return QString(tr("Quantità"));
        }
    }
    return QVariant();
}

void SituazDisp::on_pushButton_4_clicked()
{
    close();
}

