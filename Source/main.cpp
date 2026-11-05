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
#include <QStandardPaths>
#include <QElapsedTimer>
#include "initia.h"

static void process_line(const QByteArray &)
{
}
static void process_line(const QString &)
{
}
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


#ifdef Q_OS_WIN
    const QStringList languages = QLocale::system().uiLanguages();
    const QLocale locale(languages.isEmpty() ? QStringLiteral("it") : languages.first());
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

    QElapsedTimer timer;
    timer.start();
    QString ef = "y";
    const QString dataDir =
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    if (!QDir().mkpath(dataDir)) {
        qFatal("Impossibile creare la cartella dati: %s", qPrintable(dataDir));
    }
    const QString userInit = QDir(dataDir).filePath("init.dat");

    const bool primoAvvio = !QFile::exists(userInit);
    if (primoAvvio) {
        if (!QFile::copy(":/init.dat", userInit)) {
            qFatal("Impossibile copiare init.dat");
        }
    }

    if (!QFile::setPermissions(userInit,
                               QFileDevice::ReadOwner | QFileDevice::WriteOwner)) {
        qWarning() << "Impossibile impostare i permessi su" << userInit;
    }

    QFile file_i (userInit);
    if(!file_i.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning()<< "impossibile aprire per la lettura:"
                   << userInit << file_i.errorString();
    }
    QTextStream in(&file_i);
    QString line = in.readLine();
    process_line(line);
    file_i.close();
    if(line == "N") {
        ef = "n";
    }
    MainWindow w;
    splash.activateWindow();
    while (timer.elapsed() < 5000) {
        a.processEvents(QEventLoop::AllEvents,50);
    }
    splash.finish(&w);
    if (ef == "n") {
        Initia *i = new Initia();
        i->setAttribute(Qt::WA_DeleteOnClose);
        i->exec();
    }
    w.show();
    return a.exec();
}
