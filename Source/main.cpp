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
    along with Dispensa.  If not, see <http://www.gnu.org/licenses/>
*/
#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QSplashScreen>
#include <QTimer>
#include <QDir>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("Dispensa");
    QApplication a(argc, argv);

    QFontDatabase::addApplicationFont(":/Fonts/NotoSans-Regular.ttf");
    QFontDatabase::addApplicationFont(":/Fonts/NotoSans-Bold.ttf");

    const QString iconPath =
        QDir(QCoreApplication::applicationDirPath()).filePath("Dispensa.png");
    a.setWindowIcon(QIcon(iconPath));

#if defined(Q_OS_WIN) || defined(Q_OS_LINUX)
    QCoreApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);
#endif

    QTranslator translator;

//#ifdef Q_OS_WIN
    /*    const QLocale locale = QLocale::system();

    if (locale.language() != QLocale::Italian
        && translator.load(locale, "Dispensa", "_", ":/i18n")) {
        a.installTranslator(&translator);
    }*/
#ifdef Q_OS_WIN
    const QStringList languages = QLocale::system().uiLanguages();
    const QLocale locale(languages.isEmpty() ? QStringLiteral("it") : languages.first());
    //qDebug() << "lingue ui : " <<QLocale::system().uiLanguages();
    if (translator.load(locale, "Dispensa", "_", ":/i18n")) {
        a.installTranslator(&translator);
    }
#else
    //Lingua del sistema:
    if (translator.load(QLocale::system(), "Dispensa", "_", ":/i18n")) {
        a.installTranslator(&translator);
    }
#endif

    /*if (translator.load(QLocale("ru"), "Dispensa", "_", ":/i18n")) {
        a.installTranslator(&translator);
    }*/

    QString imagePath = (":/Immagini/Dispensa600.png");
    QPixmap pixmap(imagePath);
    QSplashScreen  splash(pixmap,  Qt :: WindowStaysOnTopHint);
    splash.show();

    MainWindow w;
    splash.activateWindow();
    QTimer::singleShot(5000, [&splash, &w]() {
        w.show();
        splash.finish(&w);
    });
    return a.exec();
}
