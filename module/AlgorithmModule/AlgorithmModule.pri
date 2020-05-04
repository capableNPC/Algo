INCLUDEPATH +=$$PWD algoCfgWindow
include(algoCfgWindow/algoCfgWindow.pri)
INCLUDEPATH +=$$PWD algoExplain
include(algoExplain/algoExplain.pri)
INCLUDEPATH +=$$PWD algoCompute
include(algoCompute/algoCompute.pri)

HEADERS += \
    $$PWD/abstractfactory.h

SOURCES += \
    $$PWD/abstractfactory.cpp
