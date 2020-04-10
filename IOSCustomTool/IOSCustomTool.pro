QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IOSCustomTool
TEMPLATE = app
CONFIG += c++11 link_pkgconfig
PKGCONFIG += dtkwidget

SOURCES += \
        main.cpp \
    mainwindow.cpp \
    seatchisofile.cpp \
    searcharchitecture.cpp \
    programconfig.cpp \
    searchkernel.cpp \
    print.cpp \
    sharedclass.cpp

RESOURCES += \        
    resource.qrc

HEADERS += \
    mainwindow.h \
    seatchisofile.h \
    searcharchitecture.h \
    programconfig.h \
    searchkernel.h \
    print.h \
    sharedclass.h

DISTFILES +=
