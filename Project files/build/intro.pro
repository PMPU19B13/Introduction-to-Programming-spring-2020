QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = intropro
TEMPLATE = app
INCLUDEPATH += ../include

SOURCES += ../src/main.cpp \
   ../src/drawer.cpp \
   ../src/controller.cpp \
   ../src/geometry.cpp \
   ../src/id.cpp



HEADERS  += \
    ../include/controller.h \
    ../include/drawer.h \
    ../include/error.h \
    ../include/geometry.h \
    ../include/id.h \
    ../include/list.h \
    ../include/mmap.h \
    ../include/mmapavl.h \
    ../include/pair.h \
    ../include/storage.h
    
    

#LIBS += -lsfml



