QT += network widgets

CONFIG += c++11 console
CONFIG -= app_bundle

HEADERS       = server.h
SOURCES       = server.cpp \
                main.cpp

DEFINES += QT_DEPRECATED_WARNINGS

# install
target.path = $$[QT_INSTALL_EXAMPLES]/network/fortuneserver
INSTALLS += target
