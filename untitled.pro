QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    admin_after_login.cpp \
    admin_login.cpp \
    building_customize_menu.cpp \
    main.cpp \
    maintenance.cpp \
    notepad.cpp \
    profile.cpp \
    renter_menu.cpp \
    renter_search.cpp \
    signup_form.cpp \
    tc.cpp \
    tolet.cpp \
    transactions.cpp

HEADERS += \
    about.h \
    admin_after_login.h \
    admin_login.h \
    building_customize_menu.h \
    maintenance.h \
    notepad.h \
    profile.h \
    renter_menu.h \
    renter_search.h \
    signup_form.h \
    tc.h \
    tolet.h \
    transactions.h


FORMS += \
    about.ui \
    admin_after_login.ui \
    admin_login.ui \
    building_customize_menu.ui \
    maintenance.ui \
    notepad.ui \
    profile.ui \
    renter_menu.ui \
    renter_search.ui \
    signup_form.ui \
    tc.ui \
    tolet.ui \
    transactions.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    RESOURCE.qrc
