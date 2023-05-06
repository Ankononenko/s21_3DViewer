QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        backend.c \
        main.cc \
        mainwindow.cc \
        glwidget.cc \
        my_getline.c

HEADERS += \
        backend.h \
        mainwindow.h \
        glwidget.h \
        my_getline.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



# TO ADD LIBRARY ON WINDOWS OR LINUX OR MACOS. Libraries are named differently

QMAKE_SPEC_T = $$[QMAKE_SPEC]
contains(QMAKE_SPEC_T,.*win32.*){
    IS_WINDOWS = 1
}
contains(QMAKE_SPEC_T,.*macx.*){
    IS_MACOS = 1
}
contains(QMAKE_SPEC_T,.*linux.*){
    IS_LINUX = 1
}
#and then anywhere to check:

!isEmpty(IS_WINDOWS): LIBS += -lOpenGL32
!isEmpty(IS_LINUX): LIBS += -lGL
#!isEmpty(IS_MAC):