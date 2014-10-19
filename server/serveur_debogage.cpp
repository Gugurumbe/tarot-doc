#include "serveur_debogage.hpp"
#include <iostream>

ServeurDebogage::ServeurDebogage(QObject * parent): Serveur(parent)
{
  QObject::connect(this, SIGNAL(connexion(unsigned int)),
		   this, SLOT(reagir_connexion(unsigned int)));
  QObject::connect(this, SIGNAL(deconnexion(unsigned int)),
		   this, SLOT(reagir_deconnexion(unsigned int)));
  QObject::connect(this, SIGNAL(message(unsigned int, Message)),
		   this, SLOT(reagir_message(unsigned int, Message)));
  //Réactions
}

void ServeurDebogage::reagir_connexion(unsigned int i)
{
  std::cout<<"Connexion de "<<i<<std::endl;
}

void ServeurDebogage::reagir_deconnexion(unsigned int i)
{
  std::cout<<"Déconnexion de "<<i<<std::endl;
}

void ServeurDebogage::reagir_message(unsigned int i, Message m)
{
  // 2 cas : soit j'ai compris...
  if(m.compris)
    {
      std::cout<<"Réception d'un message de "<<i<<" de type "<<m.type<<std::endl;
      envoyer(i, m); //je le renvoie
    }
  // soit non...
  else
    {
      Message erreur;
      erreur.type = ERREUR_PROTOCOLE;
      //j'envoie une erreur de protocole.
      std::cout<<"Erreur : je n'ai pas compris"<<std::endl;
      envoyer(i, erreur);
    }
}
