#include "serveur_jeu.hpp"
#include <iostream>

ServeurJeu::ServeurJeu(QObject * parent) : Serveur(parent)
{
  QObject::connect(this, SIGNAL(connexion(unsigned int)),
		   this, SLOT(reagir_connexion(unsigned int)));
}

void ServeurJeu::reagir_connexion(unsigned int i)
{
  if(incompletes.size() > 0)
    {
      incompletes[0]->ajouter(i);
    }
  else
    {
      incompletes.push_back(new Table(this));
      QObject::connect(incompletes[0], SIGNAL(complet(Table *)),
		       this, SLOT(detacher_table(Table *)));
      QObject::connect(incompletes[0], SIGNAL(incomplet(Table *)),
		       this, SLOT(rattacher_table(Table *)));
      QObject::connect(incompletes[0], 
		       SIGNAL(doit_emettre(unsigned int, Message)),
		       this, SLOT(envoyer(unsigned int, Message)));
      QObject::connect(incompletes[0], SIGNAL(doit_deconnecter(unsigned int)),
		       this, SLOT(deconnecter(unsigned int)));
      QObject::connect(this, SIGNAL(deconnexion(unsigned int)),
		       incompletes[0], SLOT(enlever(unsigned int)));
      QObject::connect(this, SIGNAL(message(unsigned int, Message)),
		       incompletes[0], 
		       SLOT(comprendre(unsigned int, Message)));
      reagir_connexion(i);
    }
}

void ServeurJeu::detacher_table(Table * t)
{
  for(unsigned int i = 0 ; i < incompletes.size() ; i++)
    {
      if(incompletes[i] == t)
	{
	  std::cout<<"Détachement d'une Table."<<std::endl;
	  incompletes.erase(incompletes.begin() + i);
	  i--;
	}
    }
}

void ServeurJeu::rattacher_table(Table * t)
{
  incompletes.push_back(t);
}
