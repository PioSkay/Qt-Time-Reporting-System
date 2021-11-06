#-------------------------------------------------
#
# Project created by QtCreator 2021-10-21T18:37:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tempo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += \
        console

SOURCES += \
        Log.cpp \
        accepted.cpp \
        activities.cpp \
        activities_pipeline.cpp \
        add_activity.cpp \
        add_time.cpp \
        base.cpp \
        entries.cpp \
        error_msg.cpp \
        file_pipeline.cpp \
        files_pipeline.cpp \
        jsonreader.cpp \
        login.cpp \
        main.cpp \
        mainwindow.cpp \
        subactivities_container.cpp \
        user.cpp \
        users.cpp \
        your_project.cpp \
        your_tempo.cpp

HEADERS += \
        Log.h \
        accepted.h \
        activities.h \
        activities_pipeline.h \
        add_activity.h \
        add_time.h \
        base.h \
        entries.h \
        error_msg.h \
        exceptions.h \
        file_pipeline.h \
        files_pipeline.h \
        json_base.h \
        jsonreader.h \
        login.h \
        mainwindow.h \
        subactivities_container.h \
        user.h \
        users.h \
        your_project.h \
        your_tempo.h

FORMS += \
        add_activity.ui \
        add_time.ui \
        error_msg.ui \
        login.ui \
        mainwindow.ui \
        subactivities_container.ui \
        your_project.ui \
        your_tempo.ui
