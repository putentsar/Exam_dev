QT += quick

SOURCES += \
        cryptocontroller.cpp \
        main.cpp \
        randomizer.cpp

resources.files = main.qml 
resources.prefix = /$${TARGET}
RESOURCES += resources

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    cryptocontroller.h \
    randomizer.h

win32 {
LIBS += C:\Qt\Tools\OpenSSL\Win_x64\lib\libssl.lib \
     C:\Qt\Tools\OpenSSL\Win_x64\lib\libcrypto.lib
    }
INCLUDEPATH += C:\Qt\Tools\OpenSSL\Win_x64\include\
