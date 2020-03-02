QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    mynetwork.cpp \
    room21.cpp

HEADERS += \
    login.h \
    mainwindow.h \
    mynetwork.h \
    player.h \
    room21.h

FORMS += \
    login.ui \
    mainwindow.ui \
    room21.ui

TRANSLATIONS += \
    myfirst_zh_TW.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../Downloads/resource/desk.jpg \
    ../Downloads/resource/jetton/100.xcf \
    ../Downloads/resource/jetton/25.xcf \
    ../Downloads/resource/jetton/50.xcf \
    ../Downloads/resource/photo/deer.jpg \
    ../Downloads/resource/photo/fox.jpg \
    ../Downloads/resource/puke/1.jpg \
    ../Downloads/resource/puke/10.jpg \
    ../Downloads/resource/puke/11.jpg \
    ../Downloads/resource/puke/12.jpg \
    ../Downloads/resource/puke/13.jpg \
    ../Downloads/resource/puke/14.jpg \
    ../Downloads/resource/puke/15.jpg \
    ../Downloads/resource/puke/16.jpg \
    ../Downloads/resource/puke/17.jpg \
    ../Downloads/resource/puke/18.jpg \
    ../Downloads/resource/puke/19.jpg \
    ../Downloads/resource/puke/2.jpg \
    ../Downloads/resource/puke/20.jpg \
    ../Downloads/resource/puke/21.jpg \
    ../Downloads/resource/puke/22.jpg \
    ../Downloads/resource/puke/23.jpg \
    ../Downloads/resource/puke/24.jpg \
    ../Downloads/resource/puke/25.jpg \
    ../Downloads/resource/puke/26.jpg \
    ../Downloads/resource/puke/27.jpg \
    ../Downloads/resource/puke/28.jpg \
    ../Downloads/resource/puke/29.jpg \
    ../Downloads/resource/puke/3.jpg \
    ../Downloads/resource/puke/30.jpg \
    ../Downloads/resource/puke/31.jpg \
    ../Downloads/resource/puke/32.jpg \
    ../Downloads/resource/puke/33.jpg \
    ../Downloads/resource/puke/34.jpg \
    ../Downloads/resource/puke/35.jpg \
    ../Downloads/resource/puke/36.jpg \
    ../Downloads/resource/puke/37.jpg \
    ../Downloads/resource/puke/38.jpg \
    ../Downloads/resource/puke/39.jpg \
    ../Downloads/resource/puke/4.jpg \
    ../Downloads/resource/puke/40.jpg \
    ../Downloads/resource/puke/41.jpg \
    ../Downloads/resource/puke/42.jpg \
    ../Downloads/resource/puke/43.jpg \
    ../Downloads/resource/puke/44.jpg \
    ../Downloads/resource/puke/45.jpg \
    ../Downloads/resource/puke/46.jpg \
    ../Downloads/resource/puke/47.jpg \
    ../Downloads/resource/puke/48.jpg \
    ../Downloads/resource/puke/49.jpg \
    ../Downloads/resource/puke/5.jpg \
    ../Downloads/resource/puke/50.jpg \
    ../Downloads/resource/puke/51.jpg \
    ../Downloads/resource/puke/52.jpg \
    ../Downloads/resource/puke/53.jpg \
    ../Downloads/resource/puke/54.jpg \
    ../Downloads/resource/puke/6.jpg \
    ../Downloads/resource/puke/7.jpg \
    ../Downloads/resource/puke/8.jpg \
    ../Downloads/resource/puke/9.jpg \
    ../Downloads/resource/puke/puke_back.jpg \
    ../Downloads/resource/puke/puke_total.jpg
