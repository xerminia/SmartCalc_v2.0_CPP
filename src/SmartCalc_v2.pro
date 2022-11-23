QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    SmartCalc/Controller/SmartCalcController.cpp \
    SmartCalc/Model/CreditCalcModel.cpp \
    SmartCalc/Model/SmartCalcModel.cpp \
    SmartCalc/View/CreditCalcView.cpp \
    SmartCalc/View/DrawingGraph.cpp \
    SmartCalc/View/SmartCalcView.cpp \
    SmartCalc/main.cpp \
    qcustomplot.cpp

HEADERS += \
    SmartCalc/Controller/SmartCalcController.h \
    SmartCalc/Model/CreditCalcModel.h \
    SmartCalc/Model/SmartCalcModel.h \
    SmartCalc/View/CreditCalcView.h \
    SmartCalc/View/DrawingGraph.h \
    SmartCalc/View/SmartCalcView.h \
    qcustomplot.h

FORMS += \
    SmartCalc/View/CreditCalcView.ui \
    SmartCalc/View/DrawingGraph.ui \
    SmartCalc/View/SmartCalcView.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
