TEMPLATE = app
TARGET = client
DEPENDPATH += .
INCLUDEPATH += . ../shared

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Input
HEADERS += client.hpp            \
../shared/protocole.hpp          \
client_jeu.hpp                   \
client_debogage.hpp              \
config.hpp

SOURCES += main_program.cpp      \
client.cpp                       \
../shared/protocole.cpp          \
client_jeu.cpp                   \ 
client_debogage.cpp

QT += network
