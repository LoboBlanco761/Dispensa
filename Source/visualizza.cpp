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
#include "visualizza.h"
#include "ui_visualizza.h"
#include "visualelenco.h"

Visualizza::Visualizza(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Visualizza)
{
    ui->setupUi(this);
}

Visualizza::~Visualizza()
{
    delete ui;
}

void Visualizza::on_pushButton_2_clicked()
{
    QString param;
    if(ui->radioButton->isChecked()) param = "tutto";
    if(ui->radioButton_2->isChecked()) param = "cat";
    VisualElenco *ve = new VisualElenco();
    ve->setAttribute(Qt::WA_DeleteOnClose);
    ve->settaPannello(param);
    ve->exec();
}


void Visualizza::on_pushButton_3_clicked()
{
    close();
}

