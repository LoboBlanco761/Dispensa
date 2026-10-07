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
#include "connessione.h"
#include <QCoreApplication>
#include <QSqlError>

Connessione::Connessione() {}

QSqlDatabase Connessione::conn()
{
    QSqlDatabase db;
    QString currentExecDir(QCoreApplication::applicationDirPath());
    if (QSqlDatabase::contains()) {
        db = QSqlDatabase::database(QLatin1String(QSqlDatabase::defaultConnection), false);
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE");
    }
    db.setDatabaseName(currentExecDir+"/Dispensa.db");
    if (!db.open()) {
        qDebug() << "db open error:"
                 << db.lastError();
    }
    return db;
}
