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
#ifndef SITUAZDISP_H
#define SITUAZDISP_H

#include <QDialog>
#include <QAbstractTableModel>

namespace Ui {
class SituazDisp;
}
class TestModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TestModel(QObject *parent = 0);

    void populateData(const QList<QString> &nomeCategoria,const QList<QString> &nomeProdotto,const QList<QString> &datoQuantità);

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

private:
    QList<QString> tm_nome_categoria;
    QList<QString> tm_nome_prodotto;
    QList<QString> tm_dato_quantità;

};

class SituazDisp : public QDialog
{
    Q_OBJECT

public:
    explicit SituazDisp(QWidget *parent = nullptr);
    ~SituazDisp();

public:
    void settaPannello();

private slots:
    void on_pushButton_4_clicked();

private:
    Ui::SituazDisp *ui;
};

#endif // SITUAZDISP_H
