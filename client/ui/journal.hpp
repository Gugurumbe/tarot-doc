/**
   @file client/ui/journal.hpp
   @brief Widget personnalisé.
 */

#ifndef JOURNAL_DEFINI

/**
   @brief Empêche les inclusions récursives.
 */
#define JOURNAL_DEFINI

#include <QTextBrowser>
#include "carte.hpp"
#include "enchere.hpp"
#include "option.hpp"
#include "tapis.hpp"

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
  void connecte();
  /**
     @brief Indique au joueur qu'il est déconnecté.
   */
  void deconnecte();
  /**
     @brief Indique au joueur qu'il a reçu son numéro.
     @param n Mon numéro.
   */
  void numero_change(unsigned int n);
  /**
     @brief Indique au joueur qu'il doit priser.
     @param max La meilleure enchère jusqu'à présent, ou rien si vous
     êtes le premier joueur.
   */
  void doit_priser(Option<Enchere> max);
  /**
     @brief Indique au joueur que son enchère a été acceptée.
     @param e Mon enchère.
   */
  void enchere_acceptee(Enchere e);
  /**
     @brief Indique au joueur que son enchère a été refusée.
     @param e L'enchère que j'aurais voulu faire.
   */
  void enchere_refusee(Enchere e);
  /**
     @brief Indique au joueur qu'un contrat a été formulé.
     @param e L'enchère effectuée.
   */
  void contrat_intermediaire(Enchere e);
  /**
     @brief Indique au joueur qu'il doit appeler une carte.
     @param possibles Les cartes qui seront acceptées (si le serveur
     est respectueux de nos règles...)
   */
  void doit_appeler(std::vector<Carte> possibles);
  /**
     @brief Indique au joueur que son appel a été accepté.
     @param c La carte appelée.
   */
  void appel_accepte(Carte c);
  /**
     @brief Indique au joueur que son appel a été refusé.
     @param c La carte que vous vouliez appeler.
   */
  void appel_refuse(Carte c);
  /**
     @brief Indique au joueur que la phase d'enchères est terminée.
     @param e Le contrat final.
   */
  void contrat_final(Enchere e);
  /**
     @brief Indique au joueur que le chien est dévoilé.
     @param c1 La première carte du chien.
     @param c2 La deuxième carte du chien.
     @param c3 La troisième carte du chien.
   */
  void chien(Carte c1, Carte c2, Carte c3);
  /**
     @brief Indique au joueur qu'il doit faire un écart.
     @param possibles Les cartes que je peux écarter.
     @param atouts Les atouts que je peux écarter en dernier
     recours.
   */
  void doit_ecarter(std::vector<Carte> possible,
			     std::vector<Carte> atouts);
  /**
     @brief Indique au joueur que son écart a été accepté.
     @param ecart L'écart effectué.
   */
  void ecart_accepte(std::vector<Carte> ecart);
  /**
     @brief Indique au joueur que son écart a été refusé.
     @param ecart L'écart souhaité.
   */
  void ecart_refuse(std::vector<Carte> ecart);
  /**
     @brief Indique au joueur que des atouts ont été mis au chien.
     @param atouts Les atouts au chien. Entre 1 et 3 inclus.
   */
  void atout_au_chien(std::vector<Carte> atouts);
  /**
     @brief Indique au joueur que le joueur maître change.
     @param maitre Le joueur maître.
   */
  void maitre_change(unsigned int maitre);
  /**
     @brief Indique au joueur que son jeu change.
     @param gagnees Les cartes qu'il a gagnées.
     @param perdues Les cartes qu'il a perdues.
   */
  void jeu_change(std::vector<Carte> gagnees, 
			   std::vector<Carte> perdues);
  /**
     @brief Indique au joueur qu'il doit jouer.
   */
  void doit_jouer();
  /**
     @brief Indique au joueur que sa requête a abouti.
     @param jouee La carte jouée.
   */
  void requete_acceptee(Carte jouee);
  /**
     @brief Indique au joueur que sa requête a été refusée.
     @param refusee La carte qui a été refusée.
   */
  void requete_refusee(Carte refusee);
  /**
     @brief Indique au joueur qu'une carte a été jouée.
     @param joueur Celui qui a posé la carte.
     @param jouee La carte jouée.
   */
  void carte_jouee(unsigned int joueur, Carte jouee);
  /**
     @brief Indique au joueur qu'une carte a été remportée.
     @param carte La carte en question.
     @param poseur Le joueur qui a posé la carte.
     @param gagnant Le joueur qui a remporté cette carte.
   */
  void carte_gagnee(Carte carte, unsigned int poseur,
			     unsigned int gagnant);
  /**
     @brief Indique au joueur que la levée est terminée.
     @param gagnant Le joueur qui a gagné le pli.
   */
  void pli_termine(unsigned int gagnant);
  /**
     @brief Indique au joueur que le tapis change.
     @param tapis Le tapis.
   */
  void tapis_change(Tapis tapis);
  /**
     @brief Indique au joueur que la partie est terminée.
     @param scores Les scores des joueurs.
   */
  void partie_terminee(std::vector<int> scores);

private:
  void p(std::string const & utf8);
  QString header;
  QString body;
  QString footer;
};

#endif
