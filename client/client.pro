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
config.hpp                       \
../shared/partie.hpp             \
../shared/partie_client.hpp      \
../shared/tapis.hpp              \
../shared/enchere.hpp            \
../shared/carte.hpp              \
../shared/main.hpp               \
../shared/debogueur.hpp

SOURCES += main_program.cpp      \
client.cpp                       \
../shared/protocole.cpp          \
client_jeu.cpp                   \ 
client_debogage.cpp              \
../shared/partie.cpp             \
../shared/partie_client.cpp      \
../shared/tapis.cpp              \
../shared/enchere.cpp            \
../shared/carte.cpp              \
../shared/main.cpp               \
../shared/debogueur.cpp

QT += network
