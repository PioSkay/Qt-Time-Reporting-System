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
        sources/Log.cpp \
        sources/accepted.cpp \
        sources/activities.cpp \
        sources/activities_pipeline.cpp \
        sources/add_activity.cpp \
        sources/add_time.cpp \
        sources/adjust_window.cpp \
        sources/base.cpp \
        sources/entries.cpp \
        sources/file_pipeline.cpp \
        sources/files_pipeline.cpp \
        sources/jsonreader.cpp \
        sources/login.cpp \
        sources/main.cpp \
        sources/mainwindow.cpp \
        sources/project_pending_request.cpp \
        sources/project_reports.cpp \
        sources/request_data.cpp \
        sources/request_report.cpp \
        sources/subactivities_container.cpp \
        sources/user.cpp \
        sources/users.cpp \
        sources/view_tempo.cpp \
        sources/your_project.cpp \
        sources/your_tempo.cpp

HEADERS += \
        headers/Log.h \
        headers/accepted.h \
        headers/activities.h \
        headers/activities_pipeline.h \
        headers/add_activity.h \
        headers/add_time.h \
        headers/adjust_window.h \
        headers/base.h \
        headers/entries.h \
        headers/exceptions.h \
        headers/file_pipeline.h \
        headers/files_pipeline.h \
        headers/json_base.h \
        headers/jsonreader.h \
        headers/login.h \
        headers/mainwindow.h \
        headers/project_pending_request.h \
        headers/project_reports.h \
        headers/request_data.h \
        headers/request_report.h \
        headers/subactivities_container.h \
        headers/user.h \
        headers/users.h \
        headers/view_tempo.h \
        headers/your_project.h \
        headers/your_tempo.h

FORMS += \
        ui/add_activity.ui \
        ui/add_time.ui \
        ui/adjust_window.ui \
        ui/login.ui \
        ui/mainwindow.ui \
        ui/project_pending_request.ui \
        ui/project_reports.ui \
        ui/request_data.ui \
        ui/request_report.ui \
        ui/subactivities_container.ui \
        ui/view_tempo.ui \
        ui/your_project.ui \
        ui/your_tempo.ui
