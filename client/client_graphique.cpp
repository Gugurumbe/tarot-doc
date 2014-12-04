#include "client_graphique.hpp"
#include "config.hpp"

ClientGraphique::ClientGraphique(QWidget * parent): 
  QWidget(parent), jeu(this)
{
  // Pour l'instant, la connexion est automatique.
  QString addr = "127.0.0.1";
  quint16 port = 45678;
  ui.setupUi(this);
  jeu.connecter(QHostAddress(addr), port);
  connect(&jeu, SIGNAL(connecte()),
	  ui.journal, SLOT(afficher_connexion()));
  connect(&jeu, SIGNAL(deconnecte()),
	  ui.journal, SLOT(afficher_deconnexion()));
  connect(&jeu, SIGNAL(num(unsigned int)), 
	  ui.journal, SLOT(afficher_numero(unsigned int)));
  connect(&jeu, SIGNAL(num(unsigned int)),
	  ui.nom_joueur, SLOT(set_num(unsigned int)));
}

