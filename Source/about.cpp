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
#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::About)
{
    ui->setupUi(this);
    settaIcona();
}

About::~About()
{
    delete ui;
}


void About::settaIcona()
{
    QString currentExecDir(QCoreApplication::applicationDirPath());
    ui->label_2->setPixmap(QPixmap(":/Immagini/dispensa128.png"));
    ui->label_5->setPixmap(QPixmap(":/Immagini/logow 2.png"));
}

void About::on_pushButton_3_clicked()
{
    close();
}

