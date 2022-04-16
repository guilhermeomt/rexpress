ANIMATIONS_OUT_ROOT = $${OUT_PWD}/../../
CONFIG += c++14
CONFIG += debug_and_release
TARGET = $$qtLibraryTarget(animations)
DEFINES += QT_DEPRECATED_WARNINGS
TEMPLATE = lib
DESTDIR = $${ANIMATIONS_OUT_ROOT}/lib
QT += core gui widgets

!animationsBuildStatic {
    CONFIG += shared
    DEFINES += ANIMATIONS_SHARED_EXPORT
}
animationsBuildStatic {
    CONFIG += staticlib
    DEFINES += ANIMATIONS_STATIC
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
    src/AbstractAnimator.h \
    src/Animation/Animation.h \
    src/Animation/AnimationPrivate.h \
    src/Animation/Slide/SlideAnimator.h \
    src/Animation/Slide/SlideForegroundDecorator.h \
    src/StackedWidgetAnimation/StackedWidgetAnimation.h \
    src/StackedWidgetAnimation/StackedWidgetAnimationPrivate.h \
    src/WAF.h \
    src/StackedWidgetAnimation/StackedWidgetSlide/StackedWidgetSlideAnimator.h \
    src/StackedWidgetAnimation/StackedWidgetSlide/StackedWidgetSlideDecorator.h \
    src/StackedWidgetAnimation/StackedWidgetSlideOver/StackedWidgetSlideOverDecorator.h \
    src/StackedWidgetAnimation/StackedWidgetSlideOver/StackedWidgetSlideOverAnimator.h \
    src/StackedWidgetAnimation/StackedWidgetFadeIn/StackedWidgetFadeInDecorator.h \
    src/StackedWidgetAnimation/StackedWidgetFadeIn/StackedWidgetFadeInAnimator.h \
    src/Animation/CircleFill/CircleFillAnimator.h \
    src/Animation/CircleFill/CircleFillDecorator.h \
    src/Animation/Expand/ExpandAnimator.h \
    src/Animation/Expand/ExpandDecorator.h \
    src/Animation/SideSlide/SideSlideDecorator.h \
    src/Animation/SideSlide/SideSlideAnimator.h

SOURCES += src/Animation/Animation.cpp \
    src/Animation/Slide/SlideAnimator.cpp \
    src/Animation/Slide/SlideForegroundDecorator.cpp \
    src/StackedWidgetAnimation/StackedWidgetAnimation.cpp \
    src/StackedWidgetAnimation/StackedWidgetSlide/StackedWidgetSlideAnimator.cpp \
    src/StackedWidgetAnimation/StackedWidgetSlide/StackedWidgetSlideDecorator.cpp \
    src/StackedWidgetAnimation/StackedWidgetSlideOver/StackedWidgetSlideOverAnimator.cpp \
    src/StackedWidgetAnimation/StackedWidgetSlideOver/StackedWidgetSlideOverDecorator.cpp \
    src/StackedWidgetAnimation/StackedWidgetFadeIn/StackedWidgetFadeInAnimator.cpp \
    src/StackedWidgetAnimation/StackedWidgetFadeIn/StackedWidgetFadeInDecorator.cpp \
    src/Animation/CircleFill/CircleFillAnimator.cpp \
    src/Animation/CircleFill/CircleFillDecorator.cpp \
    src/Animation/Expand/ExpandAnimator.cpp \
    src/Animation/Expand/ExpandDecorator.cpp \
    src/Animation/SideSlide/SideSlideDecorator.cpp \
    src/Animation/SideSlide/SideSlideAnimator.cpp

isEmpty(PREFIX){
        PREFIX=../installed
        warning("Install Prefix not set")
}
headers.path=$$PREFIX/include
headers.files=$$HEADERS
target.path=$$PREFIX/lib
INSTALLS += headers target

DISTFILES +=
