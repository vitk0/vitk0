#-------------------------------------------------
#
# Project created by QtCreator 2016-03-28T19:20:45
#
#-------------------------------------------------

QT       += core gui sql axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ReportMaker
TEMPLATE = app


SOURCES += main.cpp\
    database/class.cpp \
    database/classes_professors.cpp \
    database/classtype.cpp \
    database/connect.cpp \
    database/database.cpp \
    database/discipline.cpp \
    database/extraduty.cpp \
    database/platoon.cpp \
    database/professor.cpp \
    database/thematicplan.cpp \
    gui/classeditwindow.cpp \
    gui/planwindow.cpp \
    gui/windowchange.cpp \
    database/trainingsession.cpp \
    gui/connectionsettings.cpp

HEADERS  += database/class.h \
    database/classes_professors.h \
    database/classtype.h \
    database/connect.h \
    database/database.h \
    database/discipline.h \
    database/extraduty.h \
    database/platoon.h \
    database/professor.h \
    database/thematicplan.h \
    gui/classeditwindow.h \
    gui/planwindow.h \
    gui/windowchange.h \
    database/trainingsession.h \
    gui/connectionsettings.h

FORMS    += gui/classeditwindow.ui \
    gui/planwindow.ui \
    gui/windowchange.ui \
    gui/connectionsettings.ui
