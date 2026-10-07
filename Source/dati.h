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
#ifndef DATI_H
#define DATI_H

#include <QObject>
#include <QWidget>
#include <QSqlDatabase>

class Dati
{
public:
    Dati();
    QStringList preCarCat(QSqlDatabase db);
    QString insProd(QSqlDatabase db,QString cat,
                    QString prod,QString qta);
    QStringList selezGen(QSqlDatabase db);
    QStringList selezCat(QSqlDatabase db,QString cat);
    QString updProd(QSqlDatabase db,int qta,int dato,
                    QString tipo,int id);
    int cercaId(QSqlDatabase db,QString cat,
                QString prod,QString qtas);
    QStringList selezLista(QSqlDatabase db);
    QStringList listaCat(QSqlDatabase db);
    QStringList listaProd(QSqlDatabase db);
    QString cancCat(QSqlDatabase db,int id);
    QString modCat(QSqlDatabase db,int id,QString cat);
    QString cancProd(QSqlDatabase db,int id);
    QString modProd(QSqlDatabase db,int id,QString cat,QString prod);
    QString creTabTemp(QSqlDatabase db);
    QString insTabTemp(QSqlDatabase db,QString cat,QString prod);
    QStringList leggiTemp(QSqlDatabase db);
    QString testTemp(QSqlDatabase db);
    void cancTemp(QSqlDatabase db);
};

#endif // DATI_H
