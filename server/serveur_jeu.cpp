#include "serveur_jeu.hpp"
#include <iostream>

ServeurJeu::ServeurJeu(QObject * parent) : Serveur(parent)
{
  QObject::connect(this, SIGNAL(connexion(unsigned int)),
		   this, SLOT(reagir_connexion(unsigned int)));
  // Les déconnexions et messages seront directement transmis à toutes
  // les tables.n
  std::cout<<"Serveur de jeu prêt."<<std::endl;
}

void ServeurJeu::reagir_connexion(unsigned int i)
{
  if(incompletes.size() > 0)
    {
      incompletes[0]->ajouter(i);
      // Il y a une table incomplète, on lui rajoute ce client.
    }
  else
    {
      // On doit construire une table.
      // La table n'est pas capable de savoir quand un client émet un message
      // ou se déconnecte (un unsigned int n'émet pas de signaux). Donc elle 
      // passe par le serveur, qui doit relayer ces événements.
      // Petit bémol : toutes les Table reçoivent chacun des événements.
      // Il faudra filtrer ceux qui concernent effectivement la Table en
      // question.
      incompletes.push_back(new Table(this));
      QObject::connect(incompletes[0], SIGNAL(complet(Table *)),
		       this, SLOT(detacher_table(Table *)));
      QObject::connect(incompletes[0], SIGNAL(destroyed(QObject *)),
		       this, SLOT(oublier_table(QObject *)));
      QObject::connect(incompletes[0], SIGNAL(incomplet(Table *)),
		       this, SLOT(rattacher_table(Table *)));
      // Gestion de la liste des Table.
      QObject::connect(incompletes[0], 
		       SIGNAL(doit_emettre(unsigned int, Protocole::Message)),
		       this, SLOT(envoyer(unsigned int, Protocole::Message)));
      QObject::connect(incompletes[0], SIGNAL(doit_deconnecter(unsigned int)),
		       this, SLOT(deconnecter(unsigned int)));
      // Si la Table estime qu'il faut envoyer un message à / déconnecter
      // un client, on le fait.
      QObject::connect(this, SIGNAL(deconnexion(unsigned int)),
		       incompletes[0], SLOT(enlever(unsigned int)));
      QObject::connect(this, SIGNAL(message(unsigned int, Protocole::Message)),
		       incompletes[0], 
		       SLOT(comprendre(unsigned int, Protocole::Message)));
      // Si un client réagit, on en informe toutes les Tables.
      reagir_connexion(i);
      //Et on ajoute le client en faisant un appel récursif (on tombe dans
      // le premier cas).
    }
}

void ServeurJeu::detacher_table(Table * t)
{
  //La nappe est tachée, il faut la changer.
  //Euh, non, pardon. Il faut enlever la Table de la liste des Tables 
  //incomplètes.
  unsigned int i = 0 ;
  for(i = 0 ; i < incompletes.size() && incompletes[i] != t ; i++);
  //Recherche
  if(i < incompletes.size())
    {
      incompletes.erase(incompletes.begin() + i);
      std::cout<<"Table complète."<<std::endl;
    }
  //Suppression éventuelle
}

void ServeurJeu::rattacher_table(Table * t)
{
  if(DETRUIRE_INCOMPLETE == 1)
    {
      std::cout<<"Destruction programmée d'une Table."<<std::endl;
      t->deleteLater();
    }
  else
    {
      std::cout<<"Table incomplète."<<std::endl;
      incompletes.push_back(t);
    }
}

void ServeurJeu::oublier_table(QObject * t)
{
  QObject::disconnect(t); //Évite de garder des connexions avec une Table
  //détruite.
  unsigned int i = 0 ;
  for(i = 0 ; i < incompletes.size() && incompletes[i] != t ; i++);
  //Recherche
  if(i < incompletes.size()) incompletes.erase(incompletes.begin() + i);
  //Suppression éventuelle
}
