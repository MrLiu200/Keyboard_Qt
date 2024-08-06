QT += widgets

TARGET              = Keyboard
TEMPLATE            = app
MOC_DIR             = temp/moc
RCC_DIR             = temp/rcc
UI_DIR              = temp/ui
OBJECTS_DIR         = temp/obj
DESTDIR             = bin
RC_FILE            += keyboard.rc
FORMS += \
    keyboardform.ui

HEADERS += \
    keyboardform.h

SOURCES += \
    keyboardform.cpp \
    main.cpp

RESOURCES += \
    keyboard.qrc
