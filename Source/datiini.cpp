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
#include "datiini.h"
#include <QSqlQuery>
#include <QSqlError>

DatiIni::DatiIni() {}


QString DatiIni::creTabProd(QSqlDatabase db)
{
    QString ef = "y";
    QSqlQuery query(db);
    query.prepare("CREATE TABLE IF NOT EXISTS Wd_prodotti(id INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT, prodotto varchar(255), categoria varchar(255), qta int(5))");
    if(!query.exec()) {
        ef = "n";
        qDebug() << "cre T Prodotti error:"
                 << query.lastError();
    }
    return ef;
}

QString DatiIni::creTabCat(QSqlDatabase db)
{
    QString ef = "y";
    QSqlQuery query(db);
    query.prepare("CREATE TABLE IF NOT EXISTS Wd_categorie(id INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT, nome varchar(255))");
    if(!query.exec()) {
        ef = "n";
        qDebug() << "cre T Categorie error:"
                 << query.lastError();
    }
    return ef;
}

