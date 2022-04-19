#include "mainwindow.h"
#include "login.h"
#include <QApplication>
#include <QFile>

#include "database/dbmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QPixmap(":/images/logo.png"));


    QFile stylesheet_file(":/gui/stylesheets/Combinear.qss");
    stylesheet_file.open(QFile::ReadOnly);

    QString stylesheet = QLatin1String(stylesheet_file.readAll());
    a.setStyleSheet(stylesheet);

    Login w;
    w.show();
    return a.exec();
}
