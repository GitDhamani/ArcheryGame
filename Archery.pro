QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
RC_ICONS = "WindowIcon.ico"

SOURCES += \
    arrow.cpp \
    bow.cpp \
    main.cpp \
    mainwindow.cpp \
    score.cpp \
    sound.cpp \
    startbutton.cpp \
    target.cpp \
    view.cpp \
    volume.cpp

HEADERS += \
    arrow.h \
    bow.h \
    mainwindow.h \
    score.h \
    sound.h \
    startbutton.h \
    target.h \
    view.h \
    volume.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
