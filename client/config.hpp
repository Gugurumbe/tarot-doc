/**
   @file client/config.hpp
   @brief Définit les options de compilation du client.
*/

/**
   @brief Oui ou non.
 */
enum {YES, NO};

/**
   @brief Se connecte automatiquement sur l'adresse.
   
   
 */
#define AUTO_ADDR QHostAddress("92.144.7.179")

/**
   @brief Se connecte automatiquement sur le port
 */
#define AUTO_PORT 45678

/**
   @brief Définit la localisation de la feuille de style pour le journal.
 */
#define STYLE "style_journal.css"
