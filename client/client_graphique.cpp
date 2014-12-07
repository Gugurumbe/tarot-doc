#include "client_graphique.hpp"
#include "config.hpp"

ClientGraphique::ClientGraphique(QWidget * parent): 
  QWidget(parent), jeu(this)
{
  // Pour l'instant, la connexion est automatique.
  QString addr = "127.0.0.1";
  quint16 port = 45678;
  ui.setupUi(this);
  //Remplissage des SelecteurCarte :
  ui.selecteur_appel->afficher_toutes();
  //L'autre est cartes_jouables
  jeu.connecter(QHostAddress(addr), port);
  connect(&jeu, SIGNAL(connecte()),
	  ui.journal, SLOT(afficher_connexion()));
  connect(&jeu, SIGNAL(deconnecte()),
	  ui.journal, SLOT(afficher_deconnexion()));
  connect(&jeu, SIGNAL(numero_change(unsigned int)), 
	  ui.journal, SLOT(afficher_numero(unsigned int)));
  connect(&jeu, SIGNAL(numero_change(unsigned int)),
	  ui.nom_joueur, SLOT(set_num(unsigned int)));
  connect(&jeu, SIGNAL(jeu_change
		       (std::vector<Carte>, std::vector<Carte>)),
	  ui.journal, SLOT(afficher_changement_jeu
			   (std::vector<Carte>, std::vector<Carte>)));
  connect(&jeu, SIGNAL(jeu_change
		       (std::vector<Carte>, std::vector<Carte>)),
	  ui.mes_cartes, SLOT(gagner
			      (std::vector<Carte>, 
			       std::vector<Carte>)));
  connect(&jeu, SIGNAL(jeu_change
		       (std::vector<Carte>, std::vector<Carte>)),
	  ui.cartes_jouables, SLOT(modifier_cartes
				   (std::vector<Carte>,
				    std::vector<Carte>)));
  connect(&jeu, SIGNAL(doit_priser(Enchere)),
	  ui.journal, SLOT(afficher_doit_priser(Enchere)));
  connect(&jeu, SIGNAL(doit_priser()),
	  ui.journal, SLOT(afficher_doit_priser()));
  connect(&jeu, SIGNAL(enchere_refusee()),
	  ui.journal, SLOT(afficher_contrat_invalide()));
  connect(&jeu, SIGNAL(dernier_contrat(Enchere)),
	  ui.journal, SLOT(afficher_contrat_intermediaire(Enchere)));
  connect(&jeu, SIGNAL(doit_appeler(std::vector<Carte>)),
	  ui.journal, SLOT(afficher_doit_appeler(std::vector<Carte>)));
  connect(&jeu, SIGNAL(tapis_change(const Tapis &)),
	  ui.tapis, SLOT(recalculer(const Tapis &)));
  connect(&jeu, SIGNAL(appel_refuse()),
	  ui.journal, SLOT(afficher_appel_invalide()));
  connect(&jeu, SIGNAL(contrat_final(Enchere)),
	  ui.journal, SLOT(afficher_contrat_final(Enchere)));
  connect(&jeu, SIGNAL(chien(Carte, Carte, Carte)), 
	  this, SLOT(chien(Carte, Carte, Carte)));
}

void ClientGraphique::on_bouton_enchere_clicked()
{
  //Récupération de l'enchère
  Enchere::Prise p;
  if(ui.bouton_passe->isChecked())
    {
      p = Enchere::PASSE;
    }
  else if(ui.bouton_prise->isChecked())
    {
      p = Enchere::PRISE;
    }
  else if(ui.bouton_garde->isChecked())
    {
      p = Enchere::GARDE;
    }
  else if(ui.bouton_garde_sans->isChecked())
    {
      p = Enchere::GARDE_SANS;
    }
  else if(ui.bouton_garde_contre->isChecked())
    {
      p = Enchere::GARDE_CONTRE;
    }
  else p = static_cast<Enchere::Prise>(ui.selection_enchere->value());
  jeu.formuler_prise(p);
}

void ClientGraphique::on_bouton_appel_clicked()
{
  Carte c = ui.selecteur_appel->carte_selectionnee();
  jeu.formuler_appel(c);
}

void ClientGraphique::chien(Carte c1, Carte c2, Carte c3)
{
  std::vector<Carte> cartes;
  cartes.push_back(c1);
  cartes.push_back(c2);
  cartes.push_back(c3);
  ui.journal->afficher_chien_devoile(cartes);
  ui.chien_1->setText(QString::fromUtf8(c1.nom().c_str()));
  ui.chien_2->setText(QString::fromUtf8(c2.nom().c_str()));
  ui.chien_3->setText(QString::fromUtf8(c3.nom().c_str()));
}
