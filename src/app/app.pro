ADS_OUT_ROOT = $${OUT_PWD}/../
ANIMATIONS_OUT_ROOT = $${OUT_PWD}/../

QT += core gui widgets sql

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

diBuildStatic {
    DEFINES += DI_STATIC
}

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    database/dbmanager.cpp \
    database/repositories/invitationsrepository.cpp \
    database/repositories/projectsrepository.cpp \
    database/repositories/requirementsrepository.cpp \
    database/repositories/usersrepository.cpp \
    main.cpp \
    models/conversation.cpp \
    models/invitation.cpp \
    models/message.cpp \
    models/permission.cpp \
    models/project.cpp \
    models/requirement.cpp \
    models/role.cpp \
    models/user.cpp \
    views/about.cpp \
    views/invites.cpp \
    views/inviteuser.cpp \
    views/login.cpp \
    views/mainwindow.cpp \
    views/openproject.cpp \
    views/properties.cpp \
    views/registration.cpp

HEADERS += \
    database/dbmanager.h \
    database/repositories/invitationsrepository.h \
    database/repositories/irepository.h \
    database/repositories/projectsrepository.h \
    database/repositories/requirementsrepository.h \
    database/repositories/usersrepository.h \
    models/conversation.h \
    models/invitation.h \
    models/message.h \
    models/permission.h \
    models/project.h \
    models/requirement.h \
    models/role.h \
    models/user.h \
    views/about.h \
    views/invites.h \
    views/inviteuser.h \
    views/login.h \
    views/mainwindow.h \
    views/openproject.h \
    views/properties.h \
    views/registration.h

FORMS += \
    views/about.ui \
    views/invites.ui \
    views/inviteuser.ui \
    views/login.ui \
    views/mainwindow.ui \
    views/openproject.ui \
    views/properties.ui \
    views/registration.ui

LIBS += -L$${ADS_OUT_ROOT}/lib \
        -L$${ANIMATIONS_OUT_ROOT}/lib \



include(../../rexpress.pri)
include(../dependency_injection/dependency_injection.pri)
INCLUDEPATH += ../dock \
               ../animations

DEPENDPATH += ../dock \
              ../animations

DISTFILES += \
    src/CMakeLists.txt \
    src/qtadvanceddockingConfig.cmake

RESOURCES += \
    rexpress.qrc
