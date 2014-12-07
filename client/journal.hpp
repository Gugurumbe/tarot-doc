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
#include "carte.hpp"
#include "enchere.hpp"

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
  void afficher_numero(unsigned int n);
  /**
     @brief Indique au joueur qu'il a gagné / perdu des cartes.
     
     @param gagnees Les nouvelles cartes du joueur.
     @param perdues Les cartes perdues.
   */
  void afficher_changement_jeu(std::vector<Carte> gagnees, 
			       std::vector<Carte> perdues);
  /**
     @brief Indique au joueur qu'il doit priser.
   */
  void afficher_doit_priser();
  /**
     @brief Indique au joueur qu'il doit priser.
     
     @param meilleure La meilleure enchère jusqu'à présent.

     @warning N'est pas émis pour le premier joueur.
   */
  void afficher_doit_priser(Enchere meilleure);
  /**
     @brief Indique au joueur un contrat intermédiaire.
     
     @param contrat Le dernier contrat en date.
   */
  void afficher_contrat_intermediaire(Enchere contrat);
  /**
     @brief Indique au joueur que son contrat n'est pas valide.
   */
  void afficher_contrat_invalide();
  /**
     @brief Indique au joueur qu'il doit appeler une Carte.
     
     @param possibles L'ensemble des cartes qui seront acceptées.
   */
  void afficher_doit_appeler(std::vector<Carte> possibles);
  /**
     @brief Indique au joueur que son appel est invalide.
   */
  void afficher_appel_invalide();
  /**
     @brief Indique au joueur le contrat final.
     
     @param contrat Le contrat final.
   */
  void afficher_contrat_final(Enchere contrat);
  /**
     @brief Indique que le chien est dévoilé.
     
     @param chien Les 3 cartes du chien.
   */
  void afficher_chien_devoile(std::vector<Carte> chien);

private:
  QString header;
  QString footer;
};

#endif
