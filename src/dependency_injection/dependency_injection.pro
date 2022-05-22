DI_OUT_ROOT = $${OUT_PWD}/../

CONFIG += c++14
CONFIG += debug_and_release
TARGET = $$qtLibraryTarget(di)
DEFINES += QT_DEPRECATED_WARNINGS
TEMPLATE = lib
DESTDIR = $${DI_OUT_ROOT}/lib
QT += core gui widgets

!diBuildStatic {
        CONFIG += shared
    DEFINES += DI_SHARED_EXPORT
}
diBuildStatic {
        CONFIG += staticlib
    DEFINES += DI_STATIC
}

windows {
        # MinGW
        *-g++* {
                QMAKE_CXXFLAGS += -Wall -Wextra -pedantic
        }
        # MSVC
        *-msvc* {
                QMAKE_CXXFLAGS += /utf-8
        }
}


HEADERS += \
    iinstantiationservice.h \
    instantiationservice.h



SOURCES += \
    instantiationservice.cpp


isEmpty(PREFIX){
        PREFIX=../installed
        warning("Install Prefix not set")
}
headers.path=$$PREFIX/include
headers.files=$$HEADERS
target.path=$$PREFIX/lib
INSTALLS += headers target

DISTFILES += \
    dependency_injection.pri
