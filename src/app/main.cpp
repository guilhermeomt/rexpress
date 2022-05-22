#include "mainwindow.h"
#include "login.h"
#include <QApplication>
#include <QFile>

#include "database/dbmanager.h"
#include "../../dependency_injection/instantiationservice.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QPixmap(":/images/logo.png"));


    QFile stylesheet_file(":/gui/stylesheets/Combinear.qss");
    stylesheet_file.open(QFile::ReadOnly);

    auto settings = new QSettings(":/settings/settings.ini", QSettings::IniFormat);
    auto dbmanager = new DBManager("QMYSQL", settings);
    IInstantiationService *iis = new InstantiationService(nullptr);

    iis->registerSingleton<UsersRepository>(new UsersRepository(dbmanager));
    iis->registerSingleton<ProjectsRepository>(new ProjectsRepository(dbmanager));
    iis->registerSingleton<InvitationsRepository>(new InvitationsRepository(dbmanager));

    QString stylesheet = QLatin1String(stylesheet_file.readAll());
    a.setStyleSheet(stylesheet);

    Login w;
    w.show();
    return a.exec();
}
