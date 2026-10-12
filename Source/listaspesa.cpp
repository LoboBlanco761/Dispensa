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
#include "listaspesa.h"
#include "ui_listaspesa.h"
#include "connessione.h"
#include "dati.h"
#include "messaggi.h"
#include <QFile>
#include <QPrinter>
#include <QPrintDialog>

ListaSpesa::ListaSpesa(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ListaSpesa)
{
    ui->setupUi(this);
    ui->label_3->setVisible(false);
    ui->textEdit->setVisible(false);
    ui->pushButton_3->setVisible(false);
}

ListaSpesa::~ListaSpesa()
{
    delete ui;
}

void ListaSpesa::on_pushButton_2_clicked()
{
    Connessione *c = new Connessione();
    QSqlDatabase db = c->conn();
    Dati *d = new Dati();
    QStringList matrice = d->selezLista(db);
    QString currentExecDir (QCoreApplication::applicationDirPath());
    QFile file_l (currentExecDir+"/lista.txt");
    if(matrice.isEmpty()) {
        Messaggi *m = new Messaggi();
        QString fl = "a";
        QString stringa = (tr("Non è stato possibile creare la Lista"));
        m->messaggio(fl,stringa);
    } else {
        ui->label_3->setVisible(true);
        ui->textEdit->clear();
        ui->textEdit->setVisible(true);
        ui->pushButton_3->setVisible(true);
        file_l.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream out(&file_l);
        int i = 0;
        QString riga;
        QString riga_2;
        while(i<matrice.size()){
            riga = (matrice[i]+"   ,");
            i++;
            if(i == matrice.size()) {
                riga_2 = " ";
            } else {
            riga_2 = (matrice[i]+"   ,");
            }
            QString o = (riga+riga_2);
            out<<o;
            i++;
        }
        file_l.close();
        file_l.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&file_l);
        ui->textEdit->setPlainText(in.readAll());
        file_l.close();
    }
    db.close();
    file_l.remove();
}


void ListaSpesa::on_pushButton_3_clicked()
{
    QString currentExecDir(QCoreApplication::applicationDirPath());
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(currentExecDir+"/output.pdf");
    printer.setPageSize(QPageSize::A4);
    QPrintDialog dialog (&printer,this);
    ui->textEdit->print(&printer);
    QPrinter pri;
    if (dialog.exec() == QDialog::Accepted) {
        ui->textEdit->print(&pri);
        return;
    }
}


void ListaSpesa::on_pushButton_4_clicked()
{
    close();
}

