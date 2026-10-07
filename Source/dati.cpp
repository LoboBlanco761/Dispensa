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
#include "dati.h"
#include <QSqlQuery>
#include <QSqlError>

Dati::Dati() {}

QStringList Dati::preCarCat(QSqlDatabase db)
{
    QStringList matrice;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Wd_categorie");
    query.exec();
    while (query.next()) {
        QString nome = query.value(1).toString();
        matrice.append(nome);
    }
    return matrice;
}


QString Dati::insProd(QSqlDatabase db,QString cat,
                QString prod,QString qta)
{
    QString ef = "y";
    int qua = qta.toInt();
    QSqlQuery query(db);
    query.prepare("INSERT INTO Wd_prodotti(prodotto,categoria,qta)"
                  "VALUES(:prodotto,:categoria,:qta)");
    query.bindValue(":prodotto",prod);
    query.bindValue(":categoria",cat);
    query.bindValue(":qta",qua);
    if(!query.exec()) {
        ef = "n";
        qDebug()<<"ins prodotti error : "
                 <<query.lastError();
    }
    if(ef == "y") {
        query.prepare("SELECT COUNT(*) ctr FROM Wd_categorie WHERE nome = ? ");
        query.bindValue(0,cat);
        query.exec();
        query.next();
        int ctr = query.value(0).toInt();
        if(ctr == 0) {
            query.prepare("INSERT INTO Wd_categorie(nome)"
                          "VALUES(:nome)");
            query.bindValue(":nome",cat);
            if(!query.exec()) {
                ef = "n";
                qDebug()<<"ins categoria error : "
                         <<query.lastError();
            }
        }
    }
    return ef;
}


QStringList Dati::selezGen(QSqlDatabase db)
{
    QStringList matrice;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Wd_prodotti ORDER BY categoria");
    if(!query.exec()) {
        qDebug()<<"selezione generale error : "
                 <<query.lastError();
    } else {
        while (query.next()) {
            QString cat = query.value(2).toString();
            QString prod = query.value(1).toString();
            int qta = query.value(3).toInt();
            QString qtas = QString::number(qta);
            QString ele = (cat+" - "+prod+" - "+qtas);
            matrice.append(ele);
        }
    }
    return matrice;
}


QStringList Dati::selezCat(QSqlDatabase db,QString cat)
{
    QStringList matrice;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Wd_prodotti WHERE categoria = ?");
    query.bindValue(0,cat);
    if(!query.exec()) {
        qDebug()<<"selezione categoria error : "
                 <<query.lastError();
    } else {
        while(query.next()) {
            QString prod = query.value(1).toString();
            int qta = query.value(3).toInt();
            QString qtas = QString::number(qta);
            QString ele = (prod+" - "+qtas);
            matrice.append(ele);
        }
    }
    return matrice;
}


QString Dati::updProd(QSqlDatabase db,int qta,int dato,
                      QString tipo,int id)
{
    QString ef = "y";
    int numero = 0;
    if(tipo == "prel") numero = qta - dato;
    if(tipo == "dep") numero = qta + dato;
    QSqlQuery query(db);
    query.prepare("UPDATE Wd_prodotti SET qta = ? WHERE id = ?");
    query.bindValue(0,numero);
    query.bindValue(1,id);
    if(!query.exec()) {
        qDebug()<<"movimentazione error : "
                 <<query.lastError();
        ef = "n";
    }
    return ef;
}


int Dati::cercaId(QSqlDatabase db,QString cat,
            QString prod,QString qtas)
{
    int id = 0;
    int qta = qtas.toInt();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Wd_prodotti WHERE categoria = ? AND prodotto = ? AND qta = ?");
    query.bindValue(0,cat);
    query.bindValue(1,prod);
    query.bindValue(2,qta);
    if(!query.exec()) {
        qDebug()<<"ricerca id error : "
                 <<query.lastError();
    } else {
        query.next();
        id = query.value(0).toInt();
    }
    return id;
}


QStringList Dati::selezLista(QSqlDatabase db)
{
    QStringList matrice;
    QSqlQuery query(db);
    int qta = 0;
    query.prepare("SELECT * FROM Wd_prodotti WHERE qta = ? ORDER BY categoria");
    query.bindValue(0,qta);
    if(!query.exec()) {
        qDebug()<<"selezione lista error : "
                 <<query.lastError();
    } else {
        while(query.next()) {
            QString prod = query.value(1).toString();
            QString ele = (prod);
            matrice.append(ele);
        }
    }
    return matrice;
}


QStringList Dati::listaCat(QSqlDatabase db)
{
    QStringList matrice;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Wd_categorie");
    query.exec();
    while (query.next()) {
        int id = query.value(0).toInt();
        QString ids = QString::number(id);
        QString nome = query.value(1).toString();
        matrice.append(ids+" - "+nome);
    }
    return matrice;
}


QStringList Dati::listaProd(QSqlDatabase db)
{
    QStringList matrice;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Wd_prodotti ORDER BY categoria");
    query.exec();
    while (query.next()) {
        int id = query.value(0).toInt();
        QString ids = QString::number(id);
        QString cat = query.value(2).toString();
        QString prod = query.value(1).toString();
        QString ele = (ids+" - "+cat+" - "+prod);
        matrice.append(ele);
    }
    return matrice;
}


QString Dati::cancCat(QSqlDatabase db,int id)
{
    QString ef = "y";
    QSqlQuery query(db);
    query.prepare("DELETE FROM Wd_categorie where id = ?");
    query.bindValue(0,id);
    if(!query.exec()) {
        qDebug()<<"delete Cat error : "
                 <<query.lastError();
        ef = "n";
    }
    return ef;
}


QString Dati::modCat(QSqlDatabase db,int id,QString cat)
{
    QString ef = "y";
    QSqlQuery query(db);
    query.prepare("UPDATE Wd_categorie SET nome = ? WHERE id = ?");
    query.bindValue(0,cat);
    query.bindValue(1,id);
    if(!query.exec()) {
        qDebug()<<"modifica Categoria error : "
                 <<query.lastError();
        ef = "n";
    }
    return ef;
}


QString Dati::cancProd(QSqlDatabase db,int id)
{
    QString ef = "y";
    QSqlQuery query(db);
    query.prepare("DELETE FROM Wd_prodotti where id = ?");
    query.bindValue(0,id);
    if(!query.exec()) {
        qDebug()<<"delete Prod error : "
                 <<query.lastError();
        ef = "n";
    }
    return ef;
}


QString Dati::modProd(QSqlDatabase db,int id,QString cat,QString prod)
{
    QString ef = "y";
    QString mm;
    QSqlQuery query(db);
    if((!cat.isEmpty()) && (!prod.isEmpty())) {
        query.prepare("UPDATE Wd_prodotti SET categoria = ? , prodotto = ? WHERE id = ?");
        query.bindValue(0,cat);
        query.bindValue(1,prod);
        query.bindValue(2,id);
        mm = "c";
    }
    if((!cat.isEmpty()) && (prod.isEmpty())) {
        query.prepare("UPDATE Wd_prodotti SET categoria = ? WHERE id = ?");
        query.bindValue(0,cat);
        query.bindValue(1,id);
        mm = "c";
    }
    if((cat.isEmpty()) && (!prod.isEmpty())) {
        query.prepare("UPDATE Wd_prodotti SET prodotto = ? WHERE id = ?");
        query.bindValue(0,prod);
        query.bindValue(1,id);
        mm = "p";
    }
    if(!query.exec()) {
        ef = "n";
        qDebug() << "mod prod error:"
                 << query.lastError();
    }
    if(ef == "y") {
        if(mm == "c") {
            query.prepare("SELECT COUNT(*) ctr FROM Wd_categorie WHERE nome = ? ");
            query.bindValue(0,cat);
            query.exec();
            query.next();
            int ctr = query.value(0).toInt();
            if(ctr == 0) {
                query.prepare("INSERT INTO Wd_categorie(nome)"
                              "VALUES(:nome)");
                query.bindValue(":nome",cat);
                query.exec();
            }
        }
    }
    return ef;
}


QString Dati::creTabTemp(QSqlDatabase db)
{
    QString ef = "y";
    QSqlQuery query(db);
    query.prepare("CREATE TABLE IF NOT EXISTS Wd_tabTemp(id INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT, prodotto varchar(255), categoria varchar(255))");
    if(!query.exec()) {
        ef = "n";
        qDebug() << "cre T Temp error:"
                 << query.lastError();
    }
    return ef;
}


QString Dati::insTabTemp(QSqlDatabase db,QString cat,QString prod)
{
    QString ef = "y";
    QSqlQuery query(db);
    query.prepare("INSERT INTO Wd_tabTemp(prodotto,categoria)"
                  "VALUES(:prodotto,:categoria)");
    query.bindValue(":prodotto",prod);
    query.bindValue(":categoria",cat);
    if(!query.exec()) {
        ef = "n";
        qDebug()<<"ins temp error : "
                 <<query.lastError();
    }
    return ef;
}


QStringList Dati::leggiTemp(QSqlDatabase db)
{
    QStringList mat;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Wd_tabTemp");
    query.exec();
    query.next();
    QString prod = query.value(1).toString();
    QString cat = query.value(2).toString();
    QString testo = (prod+" - "+cat);
    mat.append(testo);
    return mat;
}


QString Dati::testTemp(QSqlDatabase db)
{
    QString ef = "y";
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) ctr FROM sqlite_master WHERE type = ? AND name = ?");
    query.bindValue(0,"table");
    query.bindValue(1,"Wd_tabTemp");
    query.exec();
    query.next();
    int ctr = query.value(0).toInt();
    if(ctr == 0) ef = "n";
    return ef;
}


void Dati::cancTemp(QSqlDatabase db)
{
    QSqlQuery query(db);
    query.prepare("DROP TABLE IF EXISTS Wd_tabTemp");
    query.exec();
}
