#-------------------------------------------------
#
# Project created by QtCreator 2016-03-28T19:20:45
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ReportMaker
TEMPLATE = app


SOURCES +=     connect.cpp\
main.cpp\
        planwindow.cpp \
    database.cpp \
    discipline.cpp \
    thematicplan.cpp \
    platoon.cpp \
    classes_professors.cpp \
    class.cpp \
    classtype.cpp \
    classeditwidget.cpp \
    classeditwindow.cpp

HEADERS  +=     connect.h \
planwindow.h \
    database.h \
    discipline.h \
    thematicplan.h \
    platoon.h \
    classes_professors.h \
    class.h \
    classtype.h \
    classeditwidget.h \
    classeditwindow.h

FORMS    += planwindow.ui \
    classeditwidget.ui \
    classeditwindow.ui
