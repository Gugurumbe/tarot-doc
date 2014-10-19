#ifndef SERVEUR_DEBOGAGE_DEFINI
#define SERVEUR_DEBOGAGE_DEFINI

#include "serveur.hpp"

//Classe de serveur de débogage, qui renvoie les messages au client.
//Compatible avec le client de débogage.

class ServeurDebogage: public Serveur
{
  Q_OBJECT;
  //C'est un QObject
public:
  ServeurDebogage(QObject * parent = 0);
public slots :
  void reagir_connexion(unsigned int);
  void reagir_deconnexion(unsigned int);
  void reagir_message(unsigned int, Message);
  //Fonctions de réaction personnalisées.
};

#endif
