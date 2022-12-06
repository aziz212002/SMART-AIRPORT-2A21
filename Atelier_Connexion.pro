QT       += core gui sql
QT       += widgets
QT       += multimedia
QT       += core gui  serialport charts



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Atelier_Connexion
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    arduino.cpp \
        main.cpp \
        mainwindow.cpp \
    connection.cpp \
    piechartwidget.cpp \
    produit.cpp \
    stat_produit.cpp

HEADERS += \
    arduino.h \
        mainwindow.h \
    connection.h \
    piechartwidget.h \
    produit.h \
    qcustomplot.h \
    stat_produit.h

FORMS += \
        mainwindow.ui \
        stat_produit.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    fin_stock.qrc \
    sound.qrc