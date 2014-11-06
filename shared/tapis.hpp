/**
   @file shared/tapis.hpp
   @brief Définit l'état d'un tour de jeu.
 */

#ifndef TAPIS_DEFINI

/**
   Empêche les inclusions récursives.
 */
#define TAPIS_DEFINI

/**
   Il y a une relation de composition entre un Tapis et des Carte.

   Pour utiliser directement un Message, il est nécessaire de lier le
   protocole.
   @see Carte
   @see Message
 */
#include "carte.hpp"
#include "protocole.hpp"

/**
   @brief Représente les cartes face visible sur la table.

   La classe Tapis permet de connaître l'état du tour de jeu,
   c'est-à-dire les cartes jouées ce tour-ci et les numéros des
   joueurs (0 à 4) qui jouent ces cartes.

   La méthode Tapis::terminer(unsigned int, unsigned int, bool)
   retourne la liste des cartes gagnées par l' « attaque »,
   c'est-à-dire le joueur qui a pris et le joueur appelé, lorsque le
   pli est Tapis::complet() const.
   
   @see Tapis::terminer(unsigned int, unsigned int, bool)
   @see Tapis::complet() const
 */
class Tapis
{
public:
  
  /**
     Constructeur principal.
  */
  Tapis();

  /**
     Ajoute une carte.
     L'ajout d'une carte au tapis se fait directement à partir d'un
     sous-type de Message.
     @param carte : le message provenant du serveur.
     @see Message
     @see Tapis::set_ouverture(unsigned int)
  */
  void ajouter(const Msg_carte & carte);

  /**
     Lorsqu'on ajoute la première carte du tour, il faut également 
     spécifié le joueur qui joue cette première carte, afin d'en
     déduire tous les autres.
     @param joueur : numéro du joueur
     @see Tapis::ajouter(const Msg_carte &)
   */
  void set_ouverture(unsigned int joueur);

  /**
     Indique si un tour est terminé.
     Lorsque 5 cartes réelles ont été jouées, le tour est terminé.
     @return Vrai ssi le tour est terminé.
     @see Tapis::terminer(unsigned int, unsigned int, bool)
   */
  bool complet() const;

  /**
     Termine le tour.
     Lorsque le tour est terminé, il est nécessaire d'attribuer les
     cartes gagnées par l'attaque. Pour cela, il faut connaître le
     JOUEUR appelé. Cette méthode n'est à appeler que du côté serveur.
     @param attaquant : numéro du joueur qui a pris.
     @param appele : numéro du joueur appelé.
     @param dernier_pli : indique si la vraie excuse peut être prise.
     @return Les cartes gagnées par le camp attaquant.
     @see Tapis::complet() const
   */
  std::vector<Carte> terminer(
			      unsigned int attaquant,
			      unsigned int appele,
			      bool dernier_pli);
private:

  /**
     Numéro du joueur ayant effectué l'ouverture.
     Vaut -1 à l'origine.
     @see Tapis::set_ouverture(unsigned int)
   */
  int joueur_ouverture;

  /**
     Cartes sur le tapis.
     Vidé à chaque tour. Contient au plus 6 cartes.
   */
  std::vector<Carte> m_tapis;
};

#endif
