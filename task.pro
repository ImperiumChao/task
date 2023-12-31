#-------------------------------------------------
#
# Project created by QtCreator 2019-05-02T14:22:48
#
#-------------------------------------------------

QT       += core gui widgets sql multimedia

TARGET = task
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
    addtask.cpp \
    buttonimage.cpp \
    editTimecategory.cpp \
        main.cpp \
    planning.cpp \
    statistic.cpp \
    info.cpp \
    notificationpause.cpp \
    task.cpp \
    timecategorys.cpp

HEADERS += \
    addtask.h \
    buttonimage.h \
    editTimecategory.h \
    planning.h \
    statistic.h \
    info.h \
    notificationpause.h \
    task.h \
    timecategorys.h

FORMS += \
    addtask.ui \
    editTimecategory.ui \
    planning.ui \
    statistic.ui \
    info.ui \
    notificationpause.ui \
    task.ui \
    timecategorys.ui

RC_ICONS = "D:/5. QT/task/icon.ico"

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc



