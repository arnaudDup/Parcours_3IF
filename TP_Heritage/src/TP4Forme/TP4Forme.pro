TEMPLATE = app
CONFIG += console
CONFIG += c++11
QMAKE_CXXFLAGS+= -std=c++11
QMAKE_LFLAGS +=  -std=c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ActionAjout.cpp \
    ActionClear.cpp \
    ActionDeplacer.cpp \
    ActionEffacer.cpp \
    Composite.cpp \
    Controleur.cpp \
    Modele.cpp \
    ParserEntre.cpp \
    Point.cpp \
    Polygone.cpp \
    Rectangle.cpp \
    Segment.cpp \
    Vecteur.cpp \
    Vue.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    ActionAjout.h \
    ActionClear.h \
    ActionDeplacer.h \
    ActionEffacer.h \
    Composite.h \
    Controleur.h \
    IAction.h \
    IComposant.h \
    IFigure.h \
    Modele.h \
    ParserEntre.h \
    Point.h \
    Polygone.h \
    Rectangle.h \
    Segment.h \
    Vecteur.h \
    Vue.h

