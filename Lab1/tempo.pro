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
        console \
        c++17

SOURCES += \
        Log.cpp \
        accepted.cpp \
        activities.cpp \
        activities_pipeline.cpp \
        add_activity.cpp \
        add_time.cpp \
        adjust_window.cpp \
        base.cpp \
        entries.cpp \
        file_pipeline.cpp \
        files_pipeline.cpp \
        jsonreader.cpp \
        login.cpp \
        main.cpp \
        mainwindow.cpp \
        project_pending_request.cpp \
        project_reports.cpp \
        request_data.cpp \
        request_report.cpp \
        subactivities_container.cpp \
        user.cpp \
        users.cpp \
        view_tempo.cpp \
        your_project.cpp \
        your_tempo.cpp

HEADERS += \
        Log.h \
        accepted.h \
        activities.h \
        activities_pipeline.h \
        add_activity.h \
        add_time.h \
        adjust_window.h \
        base.h \
        entries.h \
        exceptions.h \
        file_pipeline.h \
        files_pipeline.h \
        json_base.h \
        jsonreader.h \
        login.h \
        mainwindow.h \
        project_pending_request.h \
        project_reports.h \
        request_data.h \
        request_report.h \
        subactivities_container.h \
        user.h \
        users.h \
        view_tempo.h \
        your_project.h \
        your_tempo.h

FORMS += \
        add_activity.ui \
        add_time.ui \
        adjust_window.ui \
        login.ui \
        mainwindow.ui \
        project_pending_request.ui \
        project_reports.ui \
        request_data.ui \
        request_report.ui \
        subactivities_container.ui \
        view_tempo.ui \
        your_project.ui \
        your_tempo.ui
