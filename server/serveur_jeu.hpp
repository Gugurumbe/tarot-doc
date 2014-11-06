/**
   @file server/serveur_debogage.hpp
   @brief Définit un Serveur qui joue au tarot.
 */

#ifndef SERVEUR_JEU_DEFINI

/**
   Empêche les inclusions récursives.
 */
#define SERVEUR_JEU_DEFINI

#include "serveur.hpp"
#include "table.hpp"
#include <vector>

/**
   @brief Classe de Serveur de jeu.
   
   Utilise des Table de 5 joueurs pour répartir tous les clients.
 */
class ServeurJeu : public Serveur
{
  Q_OBJECT;
public:

  /**
     @brief Constructeur par défaut.

     Ce constructeur lance le listage sur un port qu'il affiche dans
     la sortie standard.

     @see Serveur::ouvrir_global()
   */
  ServeurJeu(QObject * parent = 0);
public slots :

  /**
     @brief Réaction personnalisée (connexion).

     Tente de compléter une Table.
     
     @param c : l'identification du client.
   */
  void reagir_connexion(unsigned int c);

  /**
     @brief Ne cherche plus à compléter la Table.

     Utilisé quand une Table contient 5 joueurs.
     
     @param t : la Table pleine.
   */
  void detacher_table(Table * t);

  /**
     @brief Cherche à remplir cette Table.
     
     Utilisé quand une Table pleine perd un joueur.

     @note Dans un premier temps, dans l'implémentation, la Table
     s'autodétruira si un client se déconnecte.

     @param t : la Table incomplète.
   */
  void rattacher_table(Table * t);

  /**
     @brief Oublie une Table détruite.

     @param t : la Table sur le point d'être détruite.
   */
  void oublier_table(QObject * t);
private:

  /**
     @brief Les tables incomplètes.
  */
  std::vector<Table *> incompletes;
};

#endif
