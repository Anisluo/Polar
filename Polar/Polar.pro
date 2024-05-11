QT       += core gui serialport sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    axedialog.cpp \
    createtmpdialog.cpp \
devdialog.cpp \
#    include/LoadDll.cpp \
main.cpp \
mainwindow.cpp \
    movectrl.cpp \
    showtmpdialog.cpp \
    sqlhelper.cpp \
    templatedialog.cpp \
    workThrd.cpp
HEADERS += \
Conifg.h \
    axedialog.h \
    createtmpdialog.h \
devdialog.h \
#    include/LoadDll.h \
    include/MPC.H \
mainwindow.h \
    movectrl.h \
    showtmpdialog.h \
    sqlhelper.h \
    templatedialog.h \
    workThrd.h

FORMS += \
    axedialog.ui \
    createtmpdialog.ui \
devdialog.ui \
mainwindow.ui \
    showtmpdialog.ui


CONFIG(debug, debug|release) {

INCLUDEPATH-=$$PWD/include
SOURCES -= \
include/MvCamera.cpp\

HEADERS -= \
include/MvCameraControl.h \
include/MvCamera.h\

LIBS-= -L$$PWD/lib -lMvCameraControl
LIBS+= -L$$PWD/lib -lMPC08
}




CONFIG(release, debug|release) {

INCLUDEPATH+=$$PWD/include
SOURCES += \
include/MvCamera.cpp\

HEADERS += \
include/MvCameraControl.h \
include/MvCamera.h\

LIBS+= -L$$PWD/lib -lMvCameraControl
LIBS+= -L$$PWD/lib -lMPC08
}


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
