#include "client_jeu.hpp"
#include <iostream>

#define NOM_CLASSE "ClientJeu"

#include "ne_pas_deboguer.hpp"

ClientJeu::ClientJeu(QObject * parent) : 
  Client(parent), partie(this)					 
{
  ENTER("ClientJeu(QObject * parent)");
  ADD_ARG("parent", parent);
  QObject::connect(this, SIGNAL(connecte()),
		   this, SLOT(traiter_connexion()));
  QObject::connect(this, SIGNAL(deconnecte()),
		   this, SLOT(traiter_deconnexion()));
  QObject::connect(this, SIGNAL(recu(Protocole::Message)),
		   this, SLOT(traiter_message(Protocole::Message)));
  QObject::connect(&partie, SIGNAL(doit_emettre(Protocole::Message)),
		   this, SLOT(envoyer(Protocole::Message)));

  connect(&partie, SIGNAL(numero_change(unsigned int)),
	  this, SIGNAL(numero_change(unsigned int)));
  connect(&partie, SIGNAL(jeu_change(std::vector<Carte>, 
				     std::vector<Carte>)),
	  this, SIGNAL(jeu_change(std::vector<Carte>, 
				  std::vector<Carte>)));
  connect(&partie, SIGNAL(doit_priser(Enchere)),
	  this, SIGNAL(doit_priser(Enchere)));
  connect(&partie, SIGNAL(doit_priser()),
	  this, SIGNAL(doit_priser()));
  connect(&partie, SIGNAL(enchere_refusee()),
	  this, SIGNAL(enchere_refusee()));
  connect(&partie, 
	  SIGNAL(contrat_intermediaire(unsigned int, Enchere)),
	  this, SLOT(contrat_intermediaire(unsigned int, Enchere)));
  connect(&partie, SIGNAL(doit_appeler(std::vector<Carte>)),
	  this, SIGNAL(doit_appeler(std::vector<Carte>)));
  connect(&partie, SIGNAL(appel_refuse()),
	  this, SIGNAL(appel_refuse()));
  connect(&partie, SIGNAL(contrat_final(Enchere)),
	  this, SIGNAL(contrat_final(Enchere)));
  connect(&partie, SIGNAL(chien_devoile(Carte, Carte, Carte)),
	  this, SIGNAL(chien(Carte, Carte, Carte)));
  connect(&partie, SIGNAL(doit_ecarter(std::vector<Carte>,
				       std::vector<Carte>)),
	  this, SIGNAL(doit_ecarter(std::vector<Carte>,
				    std::vector<Carte>)));
  connect(&partie, SIGNAL(ecart_accepte()),
	  this, SLOT(ecart_accepte()));
  connect(&partie, SIGNAL(ecart_refuse()),
	  this, SLOT(ecart_refuse()));
  connect(&partie, SIGNAL(atout_au_chien(std::vector<Carte>)),
	  this, SIGNAL(atout_au_chien(std::vector<Carte>)));
  connect(&partie, SIGNAL(doit_jouer()),
	  this, SIGNAL(doit_jouer()));
  connect(&partie, SIGNAL(requete_refusee()),
	  this, SLOT(requete_refusee()));
  connect(&partie, SIGNAL(carte_jouee(unsigned int, Carte)),
	  this, SIGNAL(carte_jouee(unsigned int, Carte)));
  connect(&partie, SIGNAL(score(std::vector<int>)),
	  this, SIGNAL(partie_terminee(std::vector<int>)));
  connect(&partie, SIGNAL(carte_gagnee(Carte, 
				      unsigned int, 
				      unsigned int)),
	  this, SIGNAL(carte_gagnee(Carte, 
				    unsigned int, unsigned int)));
  connect(&partie, SIGNAL(pli(unsigned int)),
	  this, SIGNAL(pli_termine(unsigned int)));
  connect(&partie, SIGNAL(maitre(unsigned int)),
	  this, SIGNAL(maitre_change(unsigned int)));
  connect(&partie, SIGNAL(tapis_change(const Tapis &)),
	  this, SIGNAL(tapis_change(const Tapis &)));
}

void ClientJeu::traiter_connexion()
{
  ENTER("traiter_connexion()");
}

void ClientJeu::traiter_deconnexion()
{
  ENTER("traiter_deconnexion()");
  reconnecter();
  //C'est critiquable : si le serveur nous déconnecte délibérément,
  //c'est la boucle infinie. Mais bon, le serveur doit savoir résister
  //à ce genre d'attaque.
}

void ClientJeu::presenter_etat()
{/*
  std::cout<<"Vous êtes le numéro "<<partie.mon_numero()
	   <<", on en est à la phase "<<partie.phase()
	   <<", vos cartes sont "<<partie.mon_jeu()
	   <<"."<<std::endl;*/
}

void ClientJeu::contrat_intermediaire(unsigned int, Enchere e)
{
  //On se débarasse du premier paramètre.
  // std::cout<<"Le joueur"<<joueur<<" a fait l'enchère "<<e<<std::endl;
  emit dernier_contrat(e);
}

void ClientJeu::ecart_accepte()
{
  // std::cout<<"Bravo ! Votre écart a été accepté."<<std::endl;
}

void ClientJeu::ecart_refuse()
{
  // std::cout<<"Votre écart a été refusé. Soyez plus vigilant."
  // 	   <<std::endl;
}

void ClientJeu::requete_refusee()
{
  // std::cout<<"Votre requête a été refusée ! Soyez plus vigilant."
  // 	   <<std::endl;
}

void ClientJeu::requete_acceptee()
{
  // std::cout<<"Votre requête a été acceptée."<<std::endl;
}

void ClientJeu::traiter_message(Protocole::Message m)
{
  ENTER("traiter_message(Message m)");
  ADD_ARG("m", m);
  partie.assimiler(m);
}

void ClientJeu::formuler_prise(Enchere::Prise p)
{
  partie.formuler_prise(p);
}

void ClientJeu::formuler_appel(const Carte & c)
{
  partie.appeler(c);
}

void ClientJeu::formuler_ecart(std::vector<Carte> ecart)
{
  partie.ecarter(ecart);
}

void ClientJeu::formuler_requete(Carte requete)
{
  partie.jouer(requete);
}
