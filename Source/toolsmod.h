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
#ifndef TOOLSMOD_H
#define TOOLSMOD_H

#include <QDialog>

namespace Ui {
class ToolsMod;
}

class ToolsMod : public QDialog
{
    Q_OBJECT

public:
    explicit ToolsMod(QWidget *parent = nullptr);
    ~ToolsMod();

public:
    QString param;
    QString cat;
    QString prod;
    void settaPannello(QString param,QString cat,QString prod);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::ToolsMod *ui;
};

#endif // TOOLSMOD_H
