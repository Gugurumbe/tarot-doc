/**
   @file server/config.hpp
   @brief Définit les options de compilations du serveur.
*/

#ifndef SERVEUR_CONFIGURE

/**
   Empêche les inclusions récursives.
 */
#define SERVEUR_CONFIGURE

/**
   @brief Définit le mode de lancement.

   Il y a 2 modes de lancement possibles :
   1. Lancement en mode débogage. L'entité a des réactions à tous les
   types de Message, mais elles ne sont pas pertinentes pour le tarot.
   2. Lancement en mode jeu. L'entité ne tient pas toujours compte de
   tous les types de Message, mais elle est capable de comprendre un
   environnement de jeu.

   @see ServeurDebogage
   @see ServeurJeu
 */
#define SERVEUR ServeurJeu

/**
   @brief Définit le port de listage.
 */
#define PORT 45678

#endif
