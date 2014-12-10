/**
   @file client/journal.hpp
   @brief Widget personnalisé.
 */

#ifndef JOURNAL_DEFINI

/**
   @brief Empêche les inclusions récursives.
 */
#define JOURNAL_DEFINI

#include <QTextBrowser>
#include <QTextStream>
#include "carte.hpp"
#include "enchere.hpp"
#include "option.hpp"

/**
   @brief Classe permettant d'afficher les événements du jeu.
 */
class Journal : public QTextBrowser
{
  Q_OBJECT;
public:
  /**
     @brief Constructeur par défaut.
     
     @param parent Le widget parent.
   */
  Journal(QWidget * parent = 0);
public slots :
  /**
     @brief Indique au joueur qu'il est connecté.
   */
  void afficher_connexion();
  /**
     @brief Indique au joueur qu'il est déconnecté.
   */
  void afficher_deconnexion();
  /**
     @brief Indique au joueur qu'il a reçu son numéro.
     @param n Mon numéro.
   */
  void afficher_numero_change(unsigned int n);
  /**
     @brief Indique au joueur qu'il doit priser.
     @param max La meilleure enchère jusqu'à présent, ou rien si vous
     êtes le premier joueur.
   */
  void afficher_doit_priser(Option<Enchere> max);
  /**
     @brief Indique au joueur que son enchère a été acceptée.
     @param e Son enchère.
   */
  void afficher_enchere_acceptee(Enchere e);
  void afficher_enchere_refusee(Enchere e);
  void afficher_contrat_intermediaire(Enchere e);
  void afficher_doit_appeler(std::vector<Carte> possibles);
  void afficher_appel_accepte(Carte c);
  void afficher_appel_refuse(Carte c);
  void afficher_contrat_final(Enchere e);
  void afficher_chien(Carte c1, Carte c2, Carte c3);
  void afficher_doit_ecarter(std::vector<Carte> possible,
			     std::vector<Carte> atouts);
  void afficher_ecart_accepte(std::vector<Carte> ecart);
  void afficher_ecart_refuse(std::vector<Carte> ecart);
  void afficher_atout_au_chien(std::vector<Carte> atouts);
  void afficher_maitre_change(unsigned int maitre);
  void afficher_jeu_change(std::vector<Carte> gagnees, 
			   std::vector<Carte> perdues);
  void afficher_doit_jouer();
  void afficher_requete_acceptee(Carte jouee);
  void afficher_requete_refusee(Carte refusee);
  void afficher_carte_jouee(unsigned int joueur, Carte jouee);
  void afficher_carte_gagnee(Carte carte, unsigned int poseur,
			     unsigned int gagnant);
  void affiher_pli_termine(unsigned int gagnant);
  void afficher_tapis_change(const Tapis & tapis);
  void afficher_partie_terminee(std::vector<int> scores);

private:
  void p(std::string const & utf8);
  QString header;
  QString footer;
};

#endif
