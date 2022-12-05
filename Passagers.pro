QT       += core gui
QT += sql
QT += printsupport network
QT += serialport

QT += printsupport
QT       += core gui sql charts
QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    arduinouno.cpp \
    authentification.cpp \
    avion.cpp \
    calendrier.cpp \
    connection.cpp \
    dialog.cpp \
    exportexcelobject.cpp \
    main.cpp \
    mainwindow.cpp \
    mapping.cpp \
    passagers.cpp \
    personnel.cpp \
    produit.cpp \
    qcustomplot.cpp \
    qrcodegen.cpp \
    smtp.cpp \
    vols.cpp

HEADERS += \
    arduino.h \
    arduinouno.h \
    authentification.h \
    avion.h \
    calendrier.h \
    connection.h \
    dialog.h \
    exportexcelobject.h \
    mainwindow.h \
    mapping.h \
    passagers.h \
    personnel.h \
    produit.h \
    qcustomplot.h \
    qrcodegen.hpp \
    smtp.h \
    vols.h

FORMS += \
    dialog.ui \
    dialogperso.ui \
    mainwindow.ui \
    mapping.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
