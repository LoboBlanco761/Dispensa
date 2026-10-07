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
#include "controlli.h"
#include "messaggi.h"

Controlli::Controlli() {}


QString Controlli::contrCat(QString categoria)
{
    QString ef = "y";
    if(categoria.isEmpty()) {
        ef = "n";
        Messaggi *m = new Messaggi();
        QString fl = "a";
        QString stringa = "Categoria obbligatoria";
        m->messaggio(fl,stringa);
    }
    return ef;
}


QString Controlli::contrProd(QString prod)
{
    QString ef = "y";
    if(prod.isEmpty()) {
        ef = "n";
        Messaggi *m = new Messaggi();
        QString fl = "a";
        QString stringa = "Prodotto obbligatorio";
        m->messaggio(fl,stringa);
    }
    return ef;
}


QString Controlli::contrQta(QString qtas)
{
    QString ef = "y";
    Messaggi *m = new Messaggi();
    if(qtas.isEmpty()) {
        ef = "n";
        QString fl = "a";
        QString stringa = "Inserire Quantità";
        m->messaggio(fl,stringa);
    }
    if(ef == "y") {
        bool ok;
        int qta = qtas.toInt(&ok);
        if(!ok) {
            QString fl = "a";
            QString stringa = "Quantità non numerica";
            m->messaggio(fl,stringa);
            ef = "n";
        }
    }
    delete(m);
    return ef;
}


QString Controlli::contrMov(QString qtasPrel,QString qtasDep)
{
    QString ef = "y";
    bool ok;
    Messaggi *m = new Messaggi();
    if((qtasPrel.isEmpty()) && (qtasDep.isEmpty())) {
        QString fl = "a";
        QString stringa = "Nessuna Movimentazione";
        m->messaggio(fl,stringa);
        ef = "n";
    }
    if(ef == "y") {
        if((!qtasPrel.isEmpty()) && (!qtasDep.isEmpty())) {
            QString fl = "a";
            QString stringa = "Possibile una sola Movimentazione";
            m->messaggio(fl,stringa);
            ef = "n";
        }
    }
    if(ef == "y") {
        if(!qtasPrel.isEmpty()) {
            int qtaPrel = qtasPrel.toInt(&ok);
            if(!ok) {
                QString fl = "a";
                QString stringa = "Quantità prelevata non numerica";
                m->messaggio(fl,stringa);
                ef = "n";
            }
        }
    }
    if(ef == "y") {
        if(!qtasDep.isEmpty()) {
            int qtaDep = qtasDep.toInt(&ok);
            if(!ok) {
                QString fl = "a";
                QString stringa = "Quantità depositata non numerica";
                m->messaggio(fl,stringa);
                ef = "n";
            }
        }
    }
    delete(m);
    return ef;
}


QString Controlli::contrMovLog(int qta,int qtaPrel)
{
    QString ef = "y";
    if(qtaPrel > qta) {
        Messaggi *m = new Messaggi();
        QString fl = "a";
        QString stringa = "Quantità Prelevata maggiore di quantità dispensa";
        m->messaggio(fl,stringa);
        ef = "n";
    }
    return ef;
}


QString Controlli::contrModProd(QString categoria,QString prod)
{
    QString ef = "y";
    if((categoria.isEmpty()) && (prod.isEmpty())) {
        Messaggi *m = new Messaggi();
        QString fl = "a";
        QString stringa = "Nessuna Modifica";
        m->messaggio(fl,stringa);
        ef = "n";
    }
    return ef;
}
