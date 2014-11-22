/**
   @file client/config.hpp
   @brief Définit les options de compilation du client.
*/


/**
   @brief Énumère les modes de lancement.

   Il y a 2 modes de lancement possibles :
   1. Lancement en mode débogage. L'entité a des réactions à tous les
   types de Message, mais elles ne sont pas pertinentes pour le tarot.
   2. Lancement en mode jeu. L'entité ne tient pas toujours compte de
   tous les types de Message, mais elle est capable de comprendre un
   environnement de jeu.

   @see ServeurDebogage
   @see ServeurJeu
 */
enum {DEBOGAGE, JEU};

/**
   @brief Oui ou non.
 */
enum {YES, NO};

/**
   @brief Se connecte automatiquement sur l'adresse 127.0.0.1:45678.
 */
#define AUTO YES
