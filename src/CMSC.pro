QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

RC_ICONS = ossim.ico

INCLUDEPATH += "C:/Program Files (x86)/Visual Leak Detector/include/"
LIBS      += -L"C:/Program Files (x86)/Visual Leak Detector/lib/Win32"
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
    CPU.cpp \
    PCB.cpp \
    core.cpp \
    fileoptionsdialog.cpp \
    instruction.cpp \
    kernel.cpp \
    loadfiledialog.cpp \
    longtermscheduler.cpp \
    mailbox.cpp \
    main.cpp \
    mainmemory.cpp \
    mainwindow.cpp \
    mutex.cpp \
    page.cpp \
    pagetable.cpp \
    programfilegenerator.cpp \
    randomfileoptionsdialog.cpp \
    resource.cpp \
    shorttermscheduler.cpp

HEADERS += \
    CPU.hpp \
    PCB.hpp \
    core.h \
    fileoptionsdialog.h \
    instruction.hpp \
    kernel.h \
    loadfiledialog.h \
    longtermscheduler.h \
    mailbox.h \
    main.hpp \
    mainmemory.h \
    mainwindow.h \
    mutex.h \
    page.h \
    pagetable.h \
    programfilegenerator.h \
    queue.hpp \
    randomfileoptionsdialog.h \
    resource.h \
    shorttermscheduler.h

FORMS += \
    fileoptionsdialog.ui \
    loadfiledialog.ui \
    mainwindow.ui \
    randomfileoptionsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    resources.qrc
