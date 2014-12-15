TEMPLATE = app
TARGET = client
DEPENDPATH += .
INCLUDEPATH += . ../shared ../../shared

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Input
HEADERS +=                                          \
afficheur_tapis.hpp                                 \
config.hpp                                          \
coquille.hpp                                        \
client_graphique.hpp                                \
journal.hpp                                         \
label_nom.hpp                                       \
liste_cartes.hpp                                    \
selecteur_carte.hpp                                 \
testeur_client.hpp                                  \
../shared/client.hpp                                \
../shared/client_jeu.hpp                            \
../shared/option.hpp                                \
../shared/partie_client.hpp                         \
../shared/transaction.hpp                           \
../../shared/carte.hpp                              \
../../shared/deboguer.hpp                           \
../../shared/debogueur.hpp                          \
../../shared/enchere.hpp                            \
../../shared/main.hpp                               \
../../shared/ne_pas_deboguer.hpp                    \
../../shared/partie.hpp                             \
../../shared/protocole.hpp                          \
../../shared/tapis.hpp       

# Sources
SOURCES +=                                          \
afficheur_tapis.cpp                                 \
coquille.cpp                                        \
client_graphique.cpp                                \
journal.cpp                                         \
label_nom.cpp                                       \
liste_cartes.cpp                                    \
main_program.cpp                                    \
selecteur_carte.cpp                                 \
testeur_client.cpp                                  \
../shared/client.cpp                                \
../shared/client_jeu.cpp                            \
../shared/option.cpp                                \
../shared/partie_client.cpp                         \
../shared/transaction.cpp                           \
../../shared/carte.cpp                              \
../../shared/debogueur.cpp                          \
../../shared/enchere.cpp                            \
../../shared/main.cpp                               \
../../shared/partie.cpp                             \
../../shared/protocole.cpp                          \
../../shared/tapis.cpp       

FORMS += client.ui 
FORMS += coquille.ui

QT += network
