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
#include "messaggi.h"
#include <QMessageBox>
#include <QSoundEffect>
#include "QtWidgets/qabstractbutton.h"

Messaggi::Messaggi() {}

void Messaggi::messaggio(QString fl,QString stringa)
{
    QSoundEffect effect;
    /*if (fl == "a") effect.setSource(QUrl::fromLocalFile("attenzione.wav"));
    if (fl == "s") effect.setSource(QUrl::fromLocalFile("successo.wav"));
    if (fl == "e") effect.setSource(QUrl::fromLocalFile("error.wav"));*/
    if (fl == "a")effect.setSource(QUrl("qrc:/Sound/attenzione.wav"));
    if (fl == "s")effect.setSource(QUrl("qrc:/Sound/successo.wav"));
    if (fl == "e")effect.setSource(QUrl("qrc:/Sound/error.wav"));
    effect.setLoopCount(1);
    effect.setVolume(0.30f);
    QMessageBox *msg = new QMessageBox();
    if (fl == "a") {
        msg->setWindowTitle("Attenzione");
        msg->setIcon(QMessageBox::Warning);
        msg->setStyleSheet("background-color:#3399FF;color:yellow");
    }
    if (fl == "s") {
        msg->setWindowTitle("Successo");
        msg->setIcon(QMessageBox::Information);
        msg->setStyleSheet("background-color:green;color:white");
    }
    if (fl == "e") {
        msg->setWindowTitle("Errore");
        msg->setIcon(QMessageBox::Critical);
        msg->setStyleSheet("background-color:#FFCCCC;color:darkred");
    }
    QFont serifFont("Lucida Grande", 18, QFont::Bold);
    msg->setFont(serifFont);
    msg->setStandardButtons(QMessageBox::Ok);
    QAbstractButton *button = msg->button(QMessageBox::Ok);
    button->setStyleSheet("background-color:gray");
    button->setFont(serifFont);
    effect.play();
    msg->setText(stringa);
    msg->exec();
}

