QT += quick xml opengl widgets
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    mainwindow.cpp \
    manipulatedframesetconstraint.cpp \
    object.cpp

RESOURCES +=

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



QMAKE_CXXFLAGS +=-DCGAL_USE_BASIC_VIEWER


HEADERS += \
    mainwindow.h \
    edge_collapse_recorder.h \
    manipulatedframesetconstraint.h \
    object.h



unix:!macx: LIBS += -L$$PWD/../../../lib64/ -lQGLViewer-qt5

INCLUDEPATH += $$PWD/../../../lib64
DEPENDPATH += $$PWD/../../../lib64

unix:!macx: LIBS += -L$$PWD/../../../lib64/ -lQt5OpenGL

INCLUDEPATH += $$PWD/../../../lib64
DEPENDPATH += $$PWD/../../../lib64

unix:!macx: LIBS += -L$$PWD/../../../lib64/ -lQt5Core

INCLUDEPATH += $$PWD/../../../lib64
DEPENDPATH += $$PWD/../../../lib64

unix:!macx: LIBS += -L$$PWD/../../../lib64/ -lgmp

INCLUDEPATH += $$PWD/../../../lib64
DEPENDPATH += $$PWD/../../../lib64

unix:!macx: LIBS += -L$$PWD/../CGAL-4.14-beta4/build/lib/ -lCGAL

INCLUDEPATH += $$PWD/../CGAL-4.14/build/include
DEPENDPATH += $$PWD/../CGAL-4.14/build/include


unix:!macx: LIBS += -L$$PWD/../CGAL-4.14-beta4/build/lib/ -lCGAL_ImageIO

INCLUDEPATH += $$PWD/../CGAL-4.14/build/include
DEPENDPATH += $$PWD/../CGAL-4.14/build/include



unix:!macx: LIBS += -L$$PWD/../CGAL-4.14-beta4/build/lib/ -lCGAL_Core

INCLUDEPATH += $$PWD/../CGAL-4.14/build/include
DEPENDPATH += $$PWD/../CGAL-4.14/build/include

unix:!macx: LIBS += -L$$PWD/../CGAL-4.14-beta4/build/lib/ -lCGAL_Qt5

INCLUDEPATH += $$PWD/../CGAL-4.14/build/include
DEPENDPATH += $$PWD/../CGAL-4.14/build/include
