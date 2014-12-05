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
  connect(&partie, SIGNAL(jeu_change(std::vector<Carte>, std::vector<Carte>)),
	  this, SIGNAL(jeu_change(std::vector<Carte>, std::vector<Carte>)));
  connect(&partie, SIGNAL(doit_priser(Enchere)),
	  this, SIGNAL(doit_priser(Enchere)));
  connect(&partie, SIGNAL(doit_priser()),
	  this, SIGNAL(doit_priser()));
  connect(&partie, SIGNAL(enchere_refusee()),
	  this, SIGNAL(enchere_refusee()));
  connect(&partie, 
	  SIGNAL(contrat_intermediaire(unsigned int, Enchere)),
	  this, SLOT(contrat_intermediaire(unsigned int, Enchere)));
  connect(&partie, SIGNAL(doit_appeler()),
	  this, SLOT(doit_appeler()));
  connect(&partie, SIGNAL(appel_refuse()),
	  this, SLOT(appel_refuse()));
  connect(&partie, SIGNAL(contrat_final(Enchere)),
	  this, SLOT(contrat_final(Enchere)));
  connect(&partie, SIGNAL(chien_devoile(Carte, Carte, Carte)),
	  this, SLOT(chien_devoile(Carte, Carte, Carte)));
  connect(&partie, SIGNAL(doit_ecarter()),
	  this, SLOT(doit_ecarter()));
  connect(&partie, SIGNAL(ecart_accepte()),
	  this, SLOT(ecart_accepte()));
  connect(&partie, SIGNAL(ecart_refuse()),
	  this, SLOT(ecart_refuse()));
  connect(&partie, SIGNAL(atout_au_chien(std::vector<Carte>)),
	  this, SLOT(atout_au_chien(std::vector<Carte>)));
  connect(&partie, SIGNAL(doit_jouer()),
	  this, SLOT(doit_jouer()));
  connect(&partie, SIGNAL(requete_refusee()),
	  this, SLOT(requete_refusee()));
  connect(&partie, SIGNAL(carte_jouee(unsigned int, Carte)),
	  this, SLOT(carte_jouee(unsigned int, Carte)));
  connect(&partie, SIGNAL(score(std::vector<int>)),
	  this, SLOT(score(std::vector<int>)));
  connect(&partie, SIGNAL(carte_gagnee(Carte, 
				      unsigned int, 
				      unsigned int)),
	  this, SLOT(carte_gagnee(Carte, unsigned int, unsigned int)));
  connect(&partie, SIGNAL(pli(unsigned int)),
	  this, SLOT(pli(unsigned int)));
  connect(&partie, SIGNAL(maitre(unsigned int)),
	  this, SLOT(maitre(unsigned int)));
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
  // std::cout<<"Le joueur"<<joueur<<" a fait l'enchère "<<e<<std::endl;
  emit dernier_contrat(e);
}

void ClientJeu::doit_appeler()
{
  // presenter_etat();
  // std::cout<<"Vous devez appeler une Carte. Vous pouvez appeler : "
  // 	   <<std::endl;
  // for(unsigned int i = 0 ; i < 78 ; i++)
  //   {
  //     if(partie.mon_jeu().peut_appeler(Carte(i)))
  // 	{
  // 	  std::cout<<"("<<i<<") : "<<Carte(i)<<std::endl;
  // 	}
  //   }
  // std::cout<<"Bien entendu, vous tester une autre carte..."
  // 	   <<std::endl
  // 	   <<"Entrez un numéro : "<<std::endl;
  // Protocole::Message appeler;
  // appeler.type = Protocole::APPELER;
  // std::cin>>appeler.m.appeler.carte;
  // envoyer(appeler);
}

void ClientJeu::appel_refuse()
{
  // std::cout<<"Votre appel a été refusé ! Soyez plus avisé..."
  // 	   <<std::endl;
}

void ClientJeu::contrat_final(Enchere)
{
  // std::cout<<"Le contrat final est "<<e<<std::endl;
}

void ClientJeu::chien_devoile(Carte, Carte, Carte)
{
  // std::cout<<"Le chien contient "<<c1<<", "<<c2<<", "<<c3<<"."
  // 	   <<std::endl;
}

void ClientJeu::doit_ecarter()
{
  // presenter_etat();
  // std::cout<<"Vous devez faire un écart. Vous pouvez tenter d'écarter :"
  // 	   <<std::endl;
  // for(unsigned int i = 0 ; i < 78 ; i++)
  //   {
  //     if(partie.mon_jeu().possede(Carte(i)))
  // 	{
  // 	  switch(Carte(i).ecartable())
  // 	    {
  // 	    case Carte::ECARTABLE:
  // 	      std::cout<<"("<<std::setw(2)<<i<<") : "
  // 		       <<std::setw(25)<<(Carte(i))<<std::endl;
  // 	      break;
  // 	    case Carte::MONTRER_CARTE:
  // 	      std::cout<<"("<<std::setw(2)<<i<<") : "
  // 		       <<std::setw(25)<<(Carte(i))<<"[sous conditions]"
  // 		       <<std::endl;
  // 	    default:
  // 	      break;
  // 	    }
  // 	}
  //   }
  // Protocole::Message ecart;
  // ecart.type = Protocole::ECART;
  // for(unsigned int i = 0 ; i < 3 ; i++)
  //   {
  //     std::cout<<"Carte "<<i<<" : ";
  //     std::cin>>ecart.m.ecart.ecart[i];
  //     std::cout<<"Merci. ";
  //   }
  // std::cout<<std::endl;
  // envoyer(ecart);
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

void ClientJeu::atout_au_chien(std::vector<Carte>)
{
  // std::cout<<"Un ou des atouts ont été mis dans le chien : "<<atouts
  // 	   <<std::endl;
}

void ClientJeu::doit_jouer()
{
  // presenter_etat();
  // std::cout<<"Vous devez jouer une carte. "
  // 	   <<"Voici les numéros de votre jeu : "
  // 	   <<std::endl;
  // for(unsigned int i = 0 ; i < 78 ; i++)
  //   {
  //     if(partie.mon_jeu().possede(Carte(i)))
  // 	{
  // 	  std::cout<<"("<<std::setw(2)<<i<<") : "
  // 		   <<(Carte(i))<<std::endl;
  // 	}
  //   }
  // std::cout<<"Que voulez-vous jouer ?"<<std::endl;
  // Protocole::Message requete;
  // requete.type = Protocole::REQUETE;
  // std::cin>>requete.m.carte.carte;
  // envoyer(requete);
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

void ClientJeu::carte_jouee(unsigned int, Carte)
{
  // std::cout<<joueur<<" a joué la carte "<<carte
  // 	   <<", le tapis est donc "<<partie.tapis()
  // 	   <<std::endl;
  emit tapis_change(partie.tapis());
}

void ClientJeu::score(std::vector<int>)
{
  // std::cout<<"Voici les scores : "<<scores<<std::endl;
}

void ClientJeu::carte_gagnee(Carte, 
			     unsigned int, 
			     unsigned int)
{
  // std::cout<<gagnant<<" remporte la carte "<<c<<" posée par "
  // 	   <<poseur<<std::endl;
}

void ClientJeu::pli(unsigned int)
{
  // std::cout<<tour<<" remporte le pli."<<std::endl;
}

void ClientJeu::maitre(unsigned int joueur)
{
  // std::cout<<"Le joueur "<<joueur<<" passe maître."<<std::endl;
  emit maitre_change(joueur);
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
