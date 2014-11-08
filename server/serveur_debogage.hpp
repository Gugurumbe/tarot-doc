/**
   @file server/serveur_debogage.hpp
   @brief Définit un Serveur qui se contente de répéter les Message
   reçus.
 */

#ifndef SERVEUR_DEBOGAGE_DEFINI

/**
   Empêche les inclusions récursives.
 */
#define SERVEUR_DEBOGAGE_DEFINI

#include "serveur.hpp"

/**
   @brief Classe de Serveur de débogage.
   
   Répète tout ce que dit le client.
   Compatible avec le ClientDebogage.
 */
class ServeurDebogage: public Serveur
{
  Q_OBJECT;
public:
  /**
     @brief Constructeur par défaut.
     
     Ce constructeur lance le listage sur un port qu'il affiche dans
     la sortie standard.

     @see Serveur::ouvrir_global()
   */
  ServeurDebogage(QObject * parent = 0);
public slots :

  /**
     @brief Réaction personnalisée (connexion).
     
     Affiche un message dans la sortie standard.
     
     @param c : l'identification du client.
   */
  void reagir_connexion(unsigned int c);

  /**
     @brief Réaction personnalisée (déconnexion).

     Affiche un message dans la sortie standard.

     @param c : l'identification du client.
   */
  void reagir_deconnexion(unsigned int c);

  /**
     @brief Réaction personnalisée (message).

     Répète le message et affiche un petit texte dans la sortie
     standard. Si le message ne respecte pas le protocole, renvoie
     ERREUR_PROTOCOLE. 
     
     @param c : l'identification du client.
     @param m : le message reçu.
   */
  void reagir_message(unsigned int c, Protocole::Message m);
};

#endif
