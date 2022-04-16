    ADS_OUT_ROOT = $${OUT_PWD}/../..

QT       += core gui widgets sql

TARGET = CentralWidgetExample
DESTDIR = $${ADS_OUT_ROOT}/lib
TEMPLATE = app
CONFIG += c++14
CONFIG += debug_and_release

adsBuildStatic {
    DEFINES += ADS_STATIC
}

animationsBuildStatic {
   DEFINES += ANIMATIONS_STATIC
}

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    database/dbmanager.cpp \
    database/repositories/usersrepository.cpp \
    models/user.cpp \
    views/about.cpp \
    views/login.cpp \
    views/main.cpp \
    views/mainwindow.cpp \
    views/properties.cpp

HEADERS += \
    database/dbmanager.h \
    database/repositories/repository.h \
    database/repositories/usersrepository.h \
    models/user.h \
    views/about.h \
    views/login.h \
    views/mainwindow.h \
    views/properties.h

FORMS += \
    views/about.ui \
    views/login.ui \
    views/mainwindow.ui \
    views/properties.ui

LIBS += -L$${ADS_OUT_ROOT}/lib

include(../rexpress.pri)
INCLUDEPATH += ../dock \
               ../animations

DEPENDPATH += ../dock \
              ../animations

DISTFILES += \
    src/CMakeLists.txt \
    src/qtadvanceddockingConfig.cmake

RESOURCES += \
    rexpress.qrc


