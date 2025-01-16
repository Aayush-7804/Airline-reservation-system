QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addadmin.cpp \
    addcostomer.cpp \
    addflight.cpp \
    bookflight.cpp \
    form.cpp \
    main.cpp \
    loginform.cpp \
    mainwindow.cpp \
    registertionform.cpp \
    viewcustomer.cpp \
    viewticket.cpp

HEADERS += \
    addadmin.h \
    addcostomer.h \
    addflight.h \
    bookflight.h \
    form.h \
    loginform.h \
    mainwindow.h \
    registertionform.h \
    viewcustomer.h \
    viewticket.h

FORMS += \
    addadmin.ui \
    addcostomer.ui \
    addflight.ui \
    bookflight.ui \
    form.ui \
    loginform.ui \
    mainwindow.ui \
    registertionform.ui \
    viewcustomer.ui \
    viewticket.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc \
    img.qrc

RC_ICONS += Icon.ico

DISTFILES +=
