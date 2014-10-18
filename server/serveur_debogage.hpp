#ifndef SERVEUR_DEBOGAGE_DEFINI
#define SERVEUR_DEBOGAGE_DEFINI

#include "serveur.hpp"

class ServeurDebogage: public Serveur
{
  Q_OBJECT;
public:
  ServeurDebogage(QObject * parent = 0);
public slots :
  void reagir_connexion(unsigned int);
  void reagir_deconnexion(unsigned int);
  void reagir_message(unsigned int, Message);
};

#endif
