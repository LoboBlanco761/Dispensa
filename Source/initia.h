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
#ifndef INITIA_H
#define INITIA_H

#include <QDialog>

namespace Ui {
class Initia;
}

class Initia : public QDialog
{
    Q_OBJECT

public:
    explicit Initia(QWidget *parent = nullptr);
    ~Initia();

public:
    QString ef;
    void updateProgress();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_progressBar_valueChanged(int value);

private:
    Ui::Initia *ui;
};

#endif // INITIA_H
