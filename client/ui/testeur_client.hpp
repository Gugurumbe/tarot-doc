/**
   @file client/ui/testeur_client.hpp
 */
#ifndef TESTEUR_CLIENT_DEFINI
#define TESTEUR_CLIENT_DEFINI

#include "partie_client.hpp"
#include "debogueur.hpp"
#include "option.cpp"

class Testeur : public QObject
{
  Q_OBJECT;
public:
  Testeur(PartieClient * partie);
  void run();
signals:
  void faire_assimiler(const Protocole::Message & message);
  void formuler_prise(Enchere::Prise p);
  void appeler(const Carte & carte);
  void ecarter(std::vector<Carte> const & cartes);
  void jouer(const Carte & carte);
public slots:
  void doit_emettre(Protocole::Message m);
  void numero_change(unsigned int num);
  void jeu_change(std::vector<Carte> gagnees,
		  std::vector<Carte> perdues);
  void tapis_change(const Tapis & tapis);
  void doit_priser(Option<Enchere> max);
  void enchere_acceptee(Enchere e);
  void enchere_refusee(Enchere e);
  void contrat_intermediaire(unsigned int joueur, Enchere e);
  void doit_appeler(std::vector<Carte> acceptees);
  void appel_accepte(Carte c);
  void appel_refuse(Carte c);
  void contrat_final(Enchere e);
  void chien_devoile(Carte carte1, Carte carte2, Carte carte3);
  void doit_ecarter(std::vector<Carte> possibles,
		    std::vector<Carte> atouts);
  void ecart_accepte(std::vector<Carte> ecart);
  void ecart_refuse(std::vector<Carte> ecart);
  void atout_au_chien(std::vector<Carte> atouts);
  void doit_jouer();
  void requete_acceptee(Carte posee);
  void requete_refusee(Carte posee);
  void carte_jouee(unsigned int joueur, Carte carte);
  void score(std::vector<int> scores);
  void carte_gagnee(Carte c, unsigned int poseur, 
		    unsigned int gagnant);
  void pli(unsigned int tour);
  void maitre(unsigned int joueur);
};

#endif
